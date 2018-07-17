/*!
    \file     balanceJson.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \date   : 11 Juin 2018
    \brief   Programme pour l'envoi du poids au format JSON
    \details Renvoie la valeur mesurée au format JSON
    Compilation : g++ balanceJson.cpp hx711.cpp SimpleIni.cpp  spi.c -o balanceJson
    Installation: sudo chown root balanceJson
                  sudo chmod +s balanceJson
                  sudo cp balanceJson /usr/lib/cgi-bin/balanceJson
                  sudo cp configuration.ini /usr/lib/cgi-bin/configuration.ini

    \version	v1.0 - First release
*/

#include <iostream>
#include <fstream>
#include <iomanip>

#include "hx711.h"
#include "SimpleIni.h"

using namespace std;

int main()
{

    hx711   balance;
    SimpleIni ini;

    string  unite;
    int     precision;

    cout << "Content-type: application/json" << endl << endl;
    cout << "{" << endl;

    // Lecture du fichier de configuration
    if(!ini.Load("/home/pi/Capteurs_I2C/HX711/configuration.ini"))
    {
        cout << "\"success\": false, " << endl;
        cout << "\"error\":\"Impossible d'ouvrir le fichier configuration.ini\"" << endl;
	cout << "}" << endl;
        return -1;
    }

    precision = ini.GetValue<int>("balance", "precision", 1);

    // Configuration de la balance
    balance.fixerEchelle( ini.GetValue<float>("balance", "scale", 1.0 ));
    balance.fixerOffset( ini.GetValue<int>("balance", "offset", 0));
    balance.configurerGain( ini.GetValue<int>("balance", "gain", 128));

    cout << "\"success\": true ," << endl;
    cout << "\"Weight\": \"" << fixed << setprecision (precision) <<  balance.obtenirPoids() << "\","<< endl;
    cout <<  "\"unite\": " << "\"" << ini.GetValue<string>("balance", "unite", "Kg") << "\"" << endl;
    cout << "}" << endl;
}
