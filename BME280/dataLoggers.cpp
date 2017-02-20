/*******************************************************************************************
*   Compilation :  g++ dataLoggers.cpp i2c.cpp  bm280.cpp -lmysqlcppconn -o dataLoggers
*******************************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include "cppconn/driver.h"
#include "cppconn/connection.h"
#include <cppconn/statement.h>
#include "bm280.h"

using namespace std;
using namespace sql;

int main(int argc, char* argv[]) {
    Driver* driver;
    Connection* connection;
    Statement *stmt;
    bm280 capteur;   // déclaration d'un bme280 à l'adresse par défaut 0x77

    capteur.donnerAltitude(74.0);   // initialisation de l'altitude du capteur
    driver = get_driver_instance();
    connection = driver -> connect("localhost", "root", "jelbroet");

    stmt = connection->createStatement();

    // creation de la base 'Valeurs' si elle n'existe pas
    stmt->execute("CREATE DATABASE IF NOT EXISTS Valeurs");

    // selectionne la base Valeurs
    stmt->execute("USE Valeurs");

    //creation de la table dataBme280 si elle n'existe pas
    stmt->execute("CREATE TABLE IF NOT EXISTS dataBme280 ( id int(11) NOT NULL AUTO_INCREMENT, temperature float NOT NULL, pression float NOT NULL, humidite float NOT NULL, date datetime NOT NULL, PRIMARY KEY (id))");

    // insertion d'une mesure de température, pression & humidité dans la table dataBme280
    ostringstream sql;
    sql << "INSERT INTO dataBme280(date, temperature, pression, humidite) VALUES (CURRENT_TIMESTAMP," << fixed << setprecision (2) << capteur.obtenirTemperatureEnC()<< "," <<  fixed << setprecision (2) << capteur.obtenirPression0() << "," <<  fixed << setprecision (2) << capteur.obtenirHumidite()  << ")";
    stmt->execute(sql.str());

    delete stmt;

    connection -> close();
    delete connection;
    cout << "Done bye" << endl;
    return 0;
}
