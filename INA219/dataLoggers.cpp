/*******************************************************************************************
*  Sujet	: Programme pour enregistrer les valeurs tension courant puissance batterie
*         	  dans la table batterie de la base de données MySQL Valeurs
*  langage      : C++
*  Auteur 	: SIMIER Philippe
*  Date   	: Mai 2017
*  Prérequis    : sudo apt-get install libmysqlcppconn-dev
*
*  Compilation  :  g++ dataLoggers.cpp -std=c++11 i2c.cpp  ina219.cpp -lmysqlcppconn -o dataLoggers
*  Execution    : Pour executer périodiquement toutes les 10 minutes
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
#include <time.h>

#include "ina219.h"

using namespace std;
using namespace sql;

/* fonction pour convertir une chaîne date en timeStamp */
time_t dateToTimeStamp(std::string dateString){

    struct tm tm;
    memset(&tm, 0, sizeof(tm));

    strptime(dateString.c_str(), "%Y-%m-%d %T", &tm);
    return mktime(&tm);
}

int main(int argc, char* argv[]) {
    Driver* driver;
    Connection* connection;
    Statement *stmt;
    ResultSet *res;
    PreparedStatement *pstmt;
    ina219 *capteur;

    float energie = 0.0;
    float u,i,p;
    time_t date, now;
    double t;

    capteur = new ina219();   // déclaration d'un capteur de type ina219 à l'adresse par défaut 0x40
    u = capteur->obtenirTension_V();
    i = capteur->obtenirCourant_A();
    p = u*i;

    driver = get_driver_instance();
    connection = driver -> connect("localhost", "root", "liberte");

    stmt = connection->createStatement();

    // creation de la base 'Valeurs' si elle n'existe pas
    stmt->execute("CREATE DATABASE IF NOT EXISTS Valeurs");

    // selectionne la base Valeurs
    stmt->execute("USE Valeurs");

    //creation de la table batterie si elle n'existe pas
    stmt->execute("CREATE TABLE IF NOT EXISTS batterie ( id int(11) NOT NULL AUTO_INCREMENT, courantBus float NOT NULL, tensionBus float NOT NULL, puissanceBus float NOT NULL, energie float NOT NULL, date timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP, PRIMARY KEY (id))");

    // Lecture de la dernière valeur de l'énergie enregistrée
    res = stmt->executeQuery("SELECT energie , date FROM batterie ORDER BY id DESC LIMIT 1");
    if (res->next()){
	date = dateToTimeStamp(res->getString("date"));
    	energie = std::stof(res->getString("energie"));
	time(&now);  // obtenir le  current time
	t = difftime(now,date) + 3600; // la différence entre maintenant et la date de la dernière mesure
	energie += p * (float)t / 3.6;   // L'énergie en mWh  3600J = 1Wh  donc 3.6J = 1mWh
    }


    // insertion des mesures de tensionBus, courantBus , PuissanceBus , energie dans la table batterie
    ostringstream sql;
    sql << "INSERT INTO batterie(tensionBus, courantBus, PuissanceBus, energie) VALUES (" << u << "," << i << "," << p << "," << energie << ")";
    stmt->execute(sql.str());

    delete stmt;
    delete res;
    connection -> close();
    delete connection;
    delete capteur;
    cout << "Done bye" << endl;
    return 0;
}
