/*************************************************************************
  Sujet	: Programme pour afficher les valeurs de  temperature
          enregistrees dans  la table temperature de la base  Valeurs
  langage   	: C++
  Auteur 	: SIMIER Philippe
  Date   	: Juin 2016
  Prerequis 	: sudo apt-get install libmysqlcppconn-dev
  Compilation 	:
      g++ lireData.cpp -o lireData -lmysqlcppconn
  Execution : ./lireData
*************************************************************************/


#include <iostream>

#include "cppconn/driver.h"
#include "cppconn/connection.h"
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

using namespace std;
using namespace sql;

int main(int argc, char* argv[]) {
    Driver* driver;
    Connection* connection;
    Statement *stmt;
    ResultSet *res;

    driver = get_driver_instance();
    connection = driver -> connect("localhost", "root", "toto");

    stmt = connection->createStatement();

    // selectionne la base Valeurs
    stmt->execute("USE Valeurs");

    // lecture des  30 dernières valeurs dans la table temperature
    res = stmt->executeQuery("SELECT * FROM temperature ORDER BY id  DESC LIMIT 0, 30 ");

    while (res->next()) {
       /* Acces aux colonnes par leur nom */
       cout << "|" << res->getString("id");
       cout << "\t|" << res->getString("date");
       /* Acces aux colonnes par leur indice , 1 est la première */
       cout << "\t|" << res->getString(2) << "|" << endl;
  }

    delete res;
    delete stmt;

    connection -> close();
    delete connection;
    cout << "Done bye" << endl;
    return 0;
}
