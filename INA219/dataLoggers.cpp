/*******************************************************************************************
* Sujet	: Programme pour enregistrer les valeurs tension courant puissance batterie
*         dans la table batterie de la base de données MySQL Valeurs
*  langage   : C++
*  Auteur 	: SIMIER Philippe
*  Date   	: Mai 2017
*  Prérequis : sudo apt-get install libmysqlcppconn-dev
*
*  Compilation :  g++ dataLoggers.cpp -std=c++11 i2c.cpp  ina219.cpp -lmysqlcppconn -o dataLoggers
*  Execution : Pour executer périodiquement toutes les 10 minutes
              Ajouter avec crontab
		en tant que super utilisateur (sudo crontab -e)
********************************************************************************************/
  //  */10 * * * * /home/pi/Capteurs_I2C/INA219/dataLoggers
/*******************************************************************************************/

#include <iostream>
#include <string>     // std::string, std::stof
#include <sstream>
#include <iomanip>
#include "cppconn/driver.h"
#include "cppconn/connection.h"
#include <cppconn/statement.h>
#include "ina219.h"

using namespace std;
using namespace sql;

int main(int argc, char* argv[]) {
    Driver* driver;
    Connection* connection;
    Statement *stmt;
    ResultSet *res;
    PreparedStatement *pstmt;
    float energie;
    float u,i,p;
    float t = 600.0;    // la période d'échantillonage 10 min soit 600s

    ina219 capteur;   // déclaration d'un ina219 à l'adresse par défaut 0x40
    u = capteur.obtenirTension_V();
    i = capteur.obtenirCourant_A();
    p = u*i;

    driver = get_driver_instance();
    connection = driver -> connect("localhost", "root", "liberte");

    stmt = connection->createStatement();

    // creation de la base 'Valeurs' si elle n'existe pas
    stmt->execute("CREATE DATABASE IF NOT EXISTS Valeurs");

    // selectionne la base Valeurs
    stmt->execute("USE Valeurs");

    //creation de la table batterie si elle n'existe pas
    stmt->execute("CREATE TABLE IF NOT EXISTS batterie ( id int(11) NOT NULL AUTO_INCREMENT, courantBus float NOT NULL, tensionBus float NOT NULL, puissanceBus float NOT NULL, energie float NOT NULL, date datetime NOT NULL, PRIMARY KEY (id))");

    // Lecture de la dernière valeur de l'énergie enregistrée
    res = stmt->executeQuery("SELECT energie FROM batterie ORDER BY id DESC LIMIT 1");
    if (res->next()){
    	energie = std::stof(res->getString("energie"));
    }
    energie += p * t / 3.6;   // L'énergie en mWh  3600J = 1Wh  donc 3.6J = 1mWh

    // insertion d'une mesure de tensionBus, courantBus , PuissanceBus dans la table batterie
    ostringstream sql;
    sql << "INSERT INTO batterie(date, tensionBus, courantBus, PuissanceBus, energie) VALUES (CURRENT_TIMESTAMP," << fixed << setprecision (3) << u << "," <<  fixed << setprecision (3) << i << "," <<  fixed << setprecision (3) << p << "," << fixed << setprecision (3) << energie << ")";
    stmt->execute(sql.str());

    delete stmt;
    delete res;
    connection -> close();
    delete connection;
    cout << "Done bye" << endl;
    return 0;
}
