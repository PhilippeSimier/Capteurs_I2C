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


int main(int argc, char* argv[]) {
    Driver* driver;
    Connection* connection;
    Statement *stmt;
    ResultSet *res;
    PreparedStatement *pstmt;
    ina219 *capteur;

    float charge = 0.0;
    float u,i,p;
    time_t date, now;
    time_t t;

    capteur = new ina219(0x42);   // déclaration d'un capteur de type ina219 à l'adresse  0x42
    u = capteur->obtenirTension_V();
    i = capteur->obtenirCourantMoyen_A(10);
    p = u*i;

    driver = get_driver_instance();
    connection = driver -> connect("localhost", "root", "liberte");

    stmt = connection->createStatement();

    // creation de la base 'Valeurs' si elle n'existe pas
    stmt->execute("CREATE DATABASE IF NOT EXISTS Valeurs");

    // selectionne la base Valeurs
    stmt->execute("USE Valeurs");

    //creation de la table batterie si elle n'existe pas
    stmt->execute("CREATE TABLE IF NOT EXISTS batterie ( id int(11) NOT NULL AUTO_INCREMENT, courantBus float NOT NULL, tensionBus float NOT NULL, puissanceBus float NOT NULL, charge float NOT NULL, date timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP, PRIMARY KEY (id))");

    // Lecture de la dernière valeur de la charge enregistrée
    res = stmt->executeQuery("SELECT charge ,UNIX_TIMESTAMP(date) as date FROM batterie ORDER BY id DESC LIMIT 1");
    if (res->next()){
    	charge = std::stof(res->getString("charge"));

	t = time(NULL) - res->getInt("date"); // la différence entre maintenant et la date de la dernière mesure
	printf("temps écoulé : %d\n", t);
	charge += i * (float)t / 3.6;   // La charge en Ah  1 mAh = 3.6 C
        printf("charge : %f mAh\n", charge);
    }


    // insertion des mesures de tensionBus, courantBus , PuissanceBus , energie dans la table batterie
    ostringstream sql;
    sql << "INSERT INTO batterie(tensionBus, courantBus, PuissanceBus, charge) VALUES (" << u << "," << i << "," << p << "," << charge << ")";
    stmt->execute(sql.str());

    delete stmt;
    delete res;
    connection -> close();
    delete connection;
    delete capteur;
    cout << "Done bye" << endl;
    return 0;
}
