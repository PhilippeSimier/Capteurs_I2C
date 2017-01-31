/*************************************************************************
  Sujet	: Programme pour enregistrer la valeur de la temperature
          dans la table temperature de la base de données MySQL Valeurs
  langage   : C++
  Auteur 	: SIMIER Philippe
  Date   	: Juin 2016
  Prérequis : sudo apt-get install libmysqlcppconn-dev
  Compilation :
      g++ saveTemp2.cpp Ds1631.cpp -o saveTemp -lmysqlcppconn -lwiringPi
  Execution : Pour executer pÃ©riodiquement toutes les 10 minutes
              Ajouter avec crontab
*************************************************************************/
  //  */10 * * * * /home/pi/cplus/saveTemp

#include <iostream>
#include <sstream>
#include <iomanip>
#include "cppconn/driver.h"
#include "cppconn/connection.h"
#include <cppconn/statement.h>
#include "Ds1631.h"

using namespace std;
using namespace sql;

int main(int argc, char* argv[]) {
    Driver* driver;
    Connection* connection;
    Statement *stmt;
    Ds1631 capteur1(0x4F);

    driver = get_driver_instance();
    connection = driver -> connect("localhost", "root", "jelbroet");

    stmt = connection->createStatement();

    // creation de la base 'Valeurs' si elle n'existe pas
    stmt->execute("CREATE DATABASE IF NOT EXISTS Valeurs");

    // selectionne la base Valeurs
    stmt->execute("USE Valeurs");

    //creation de la table temperature si elle n'existe pas
    stmt->execute("CREATE TABLE IF NOT EXISTS temperature ( id int(11) NOT NULL AUTO_INCREMENT, valeur float NOT NULL, date datetime NOT NULL, PRIMARY KEY (id))");

    // insertion d'une valeur dans la table temperature
    ostringstream sql;
    sql << "INSERT INTO temperature(date, valeur) VALUES (CURRENT_TIMESTAMP," << fixed << setprecision (2) << capteur1.getTemperature() << ")";
    stmt->execute(sql.str());

    delete stmt;

    connection -> close();
    delete connection;
    cout << "Done bye" << endl;
    return 0;
}
