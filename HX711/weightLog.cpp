/*!
    @file     weightLog.cpp
    @author   Philippe SIMIER (Touchard Wahington le Mans)
    @license  BSD (see license.txt)
    @brief    Programme pour loger les valeurs de poids dans la base de données
    @date     Juillet 2018
    @version  v1.0 - First release
    @detail    Prérequis    : sudo apt-get install libmysqlcppconn-dev
               Compilation  : g++  weightLog.cpp -lmysqlcppconn SimpleIni.cpp hx711.cpp spi.c -o weightLog
               Execution    : ./weightLog
*/


#include <iostream>
#include <fstream>
#include <iomanip>

#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "hx711.h"
#include "SimpleIni.h"

using namespace std;
using namespace sql;

int main() {

    SimpleIni ini;
    sql::ConnectOptionsMap connexion_locale, connexion_distante;
    sql::Driver     *driver;
    sql::Connection *con;
    sql::PreparedStatement *pstmt;
    hx711 balance;

// Lecture du fichier de configuration

    ini.Load("configuration.ini");

    connexion_locale["hostName"] = (sql::SQLString)ini.GetValue<string>("BDlocale", "host", "127.0.0.1");
    connexion_locale["userName"] = (sql::SQLString)ini.GetValue<string>("BDlocale", "user", "ruche");
    connexion_locale["password"] = (sql::SQLString)ini.GetValue<string>("BDlocale", "passwd", "toto");
    connexion_locale["schema"]   = (sql::SQLString)ini.GetValue<string>("BDlocale", "bdd", "ruche");
    connexion_locale["port"] = 3306;
    connexion_locale["OPT_RECONNECT"] = false;

    connexion_distante["hostName"] = (sql::SQLString)ini.GetValue<string>("BDdistante", "host", "127.0.0.1");
    connexion_distante["userName"] = (sql::SQLString)ini.GetValue<string>("BDdistante", "user", "ruche");
    connexion_distante["password"] = (sql::SQLString)ini.GetValue<string>("BDdistante", "passwd", "toto");
    connexion_distante["schema"]   = (sql::SQLString)ini.GetValue<string>("BDdistante", "bdd", "ruche");
    connexion_distante["port"] = 3306;
    connexion_distante["OPT_RECONNECT"] = false;

    // Configuration de la balance
    balance.fixerEchelle( ini.GetValue<float>("balance", "scale", 1.0 ));
    balance.fixerOffset( ini.GetValue<int>("balance", "offset", 0));
    balance.configurerGain(  ini.GetValue<int>("balance", "gain", 128));

    try {
	driver = get_driver_instance();
        con = driver->connect(connexion_distante);
        // Check de la connexion
        if(con->isValid()){
            cout << "connexion établie avec le serveur Mysql distant" << endl;
	}
    }
    catch (sql::SQLException &e)
    {
        try {
            driver = get_driver_instance();
            con = driver->connect(connexion_locale);
            // Check de la connexion
            if(con->isValid()){
               cout << "connexion établie avec le serveur Mysql local" << endl;
            }

        }
        catch (sql::SQLException &e)
        {
            // Gestion des exceptions pour afficher les erreurs

            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (code erreur MySQL: " << e.getErrorCode();
            cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
            return 1;
        }
    }


        // traitement
        string sql("INSERT INTO mesures(poids,id_ruche) VALUES(?,?)");
        pstmt = con->prepareStatement(sql);
        pstmt->setDouble( 1, balance.obtenirPoids() );
        pstmt->setInt( 2, ini.GetValue<int>("ruche", "id", 0));
        pstmt->executeUpdate();

        delete pstmt;
        delete con;




    cout << endl;
    return EXIT_SUCCESS;
}

