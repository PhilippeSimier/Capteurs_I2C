/*!
    \file     dataLoggers.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \brief    dataLoggers pour le composant i2c  bh1750
    \detail   Ce programme enregistre une valeur de luminosité à chaque exécution
   	      Compilation :  g++ dataLoggers.cpp i2c.cpp  bh1750.cpp -lmysqlcppconn -o dataLoggers

    \version    1.0 - First release

*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include "cppconn/driver.h"
#include "cppconn/connection.h"
#include <cppconn/statement.h>
#include "bh1750.h"

using namespace std;
using namespace sql;

int main(int argc, char* argv[]) {
    Driver* driver;
    Connection* connection;
    Statement *stmt;
    bh1750 *capteur;
    capteur = new bh1750();   // déclaration d'un bh1750 à l'adresse par défaut 0x23
    capteur->configurer(BH1750_ONE_TIME_HIGH_RES_MODE_2);


    driver = get_driver_instance();
    connection = driver -> connect("localhost", "root", "liberte");

    stmt = connection->createStatement();

    // creation de la base 'Valeurs' si elle n'existe pas
    stmt->execute("CREATE DATABASE IF NOT EXISTS Valeurs");

    // selectionne la base Valeurs
    stmt->execute("USE Valeurs");

    //creation de la table dataBh1750 si elle n'existe pas
    stmt->execute("CREATE TABLE IF NOT EXISTS dataBh1750 ( id int(11) NOT NULL AUTO_INCREMENT, luminosite float NOT NULL, date datetime NOT NULL, PRIMARY KEY (id))");

    // insertion d'une mesure de luminosité dans la table dataBh1750
    ostringstream sql;
    sql << "INSERT INTO dataBh1750(date, luminosite) VALUES (CURRENT_TIMESTAMP," << fixed << setprecision (0) << capteur->obtenirLuminosite_Lux()<< ")";
    stmt->execute(sql.str());

    delete stmt;

    connection -> close();
    delete connection;
    delete capteur;
    cout << "Done bye" << endl;
    return 0;
}
