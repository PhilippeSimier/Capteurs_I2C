/*******************************************************************************************
* Sujet	: Programme pour enregistrer les valeurs tension courant puissance batterie
*         dans la table batterie de la base de données MySQL Valeurs
*  langage   : C++
*  Auteur 	: SIMIER Philippe
*  Date   	: Mai 2017
*  Prérequis : sudo apt-get install libmysqlcppconn-dev
*
*  Compilation :  g++ dataloggers.cpp i2c.cpp  ina219.cpp -lmysqlcppconn -o dataLoggers
*  Execution : Pour executer périodiquement toutes les 10 minutes
              Ajouter avec crontab
********************************************************************************************/
  //  */10 * * * * /home/pi/Capteur_I2C/ina219/dataLoggers
/*******************************************************************************************/

#include <iostream>
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
    ina219 capteur;   // déclaration d'un ina219 à l'adresse par défaut 0x40


    driver = get_driver_instance();
    connection = driver -> connect("localhost", "root", "toto");

    stmt = connection->createStatement();

    // creation de la base 'Valeurs' si elle n'existe pas
    stmt->execute("CREATE DATABASE IF NOT EXISTS Valeurs");

    // selectionne la base Valeurs
    stmt->execute("USE Valeurs");

    //creation de la table batterie si elle n'existe pas
    stmt->execute("CREATE TABLE IF NOT EXISTS batterie ( id int(11) NOT NULL AUTO_INCREMENT, courantBus float NOT NULL, tensionBus float NOT NULL, puissanceBus float NOT NULL, date datetime NOT NULL, PRIMARY KEY (id))");

    // insertion d'une mesure de tensionBus, courantBus , PuissanceBus dans la table batterie
    ostringstream sql;
    sql << "INSERT INTO batterie(date, tensionBus, courantBus, PuissanceBus) VALUES (CURRENT_TIMESTAMP," << fixed << setprecision (2) << capteur.obtenirTension_V()<< "," <<  fixed << setprecision (2) << capteur.obtenirCourant_A() << "," <<  fixed << setprecision (2) << capteur.obtenirPuissance_W() << ")";
    stmt->execute(sql.str());

    delete stmt;

    connection -> close();
    delete connection;
    cout << "Done bye" << endl;
    return 0;
}
