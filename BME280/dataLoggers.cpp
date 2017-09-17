/*******************************************************************************************
/*!
    \file     dataLoggers.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)

    \brief    Programme pour enregistrer les valeurs tension courant puissance batterie
	      dans la table batterie de la base de données MySQL Valeurs


   \date      Mai 2017

   \version v1.0 - First release
   \detail    Prérequis    : sudo apt-get install libmysqlcppconn-dev
              Compilation  : g++ dataLoggers.cpp i2c.cpp  bme280.cpp -lmysqlcppconn -o dataLoggers
              Execution    : Pour executer périodiquement toutes les 10 minutes
                             Ajouter avec crontab
		             en tant que super utilisateur (sudo crontab -e)

*/
/*******************************************************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>
#include "cppconn/driver.h"
#include "cppconn/connection.h"
#include <cppconn/statement.h>
#include "bme280.h"

using namespace std;
using namespace sql;

int main(int argc, char* argv[]) {
    Driver* driver;
    Connection* connection;
    Statement *stmt;
    bme280 capteur(0x77);   // déclaration d'un bme280 à l'adresse 0x77 (par défaut 0x77)

    capteur.donnerAltitude(62.0);   // initialisation de l'altitude du capteur
    driver = get_driver_instance();
    connection = driver -> connect("localhost", "root", "liberte");

    stmt = connection->createStatement();

    // creation de la base 'Valeurs' si elle n'existe pas
    stmt->execute("CREATE DATABASE IF NOT EXISTS Valeurs");

    // selectionne la base Valeurs
    stmt->execute("USE Valeurs");

    //creation de la table dataBme280 si elle n'existe pas
    stmt->execute("CREATE TABLE IF NOT EXISTS dataBme280 ( id int(11) NOT NULL AUTO_INCREMENT, temperature float NOT NULL, pression float NOT NULL, humidite float NOT NULL, pointDeRosee float NOT NULL, date datetime NOT NULL, PRIMARY KEY (id))");

    // insertion d'une mesure de température, pression ,humidité et point de rosée dans la table dataBme280
    ostringstream sql;
    sql << "INSERT INTO dataBme280(date, temperature, pression, humidite, pointDeRosee) VALUES (CURRENT_TIMESTAMP," << fixed << setprecision (2) << capteur.obtenirTemperatureEnC()<< "," <<  fixed << setprecision (2) << capteur.obtenirPression0() << "," <<  fixed << setprecision (2) << capteur.obtenirHumidite()  <<  "," <<  fixed << setprecision (2) << capteur.obtenirPointDeRosee()  << ")";
    stmt->execute(sql.str());

    delete stmt;

    connection -> close();
    delete connection;
    cout << "Done bye" << endl;
    return 0;
}
