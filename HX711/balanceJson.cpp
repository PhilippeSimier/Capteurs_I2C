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

    float   scale;
    int     offset;
    int     gain;
    string  unite;
    int     precision = 1;
    float   weight;

    // Lecture du fichier de configuration
    ini.Load("/home/pi/Capteurs_I2C/HX711/configuration.ini");
    scale  = ini.GetValue<float>("balance", "scale", 1.0 );
    offset = ini.GetValue<int>("balance", "offset", 0);
    gain   = ini.GetValue<int>("balance", "gain", 128);
    unite  = ini.GetValue<string>("balance", "unite", "Kg");
    precision = ini.GetValue<int>("balance", "precision", 1);

    // Configuration de la balance
    balance.fixerEchelle(scale);
    balance.fixerOffset(offset);
    balance.configurerGain(gain);

    // Mesure du poids
    weight = balance.obtenirPoids();

    cout << "Content-type: application/json" << endl << endl;
    cout << "{" << endl;
    cout << "\"Weight\":\"" << fixed << setprecision (precision) << weight << " " << unite << "\""<< endl;
    cout << "}" << endl;
}
