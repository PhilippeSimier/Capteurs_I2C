/*!
    \file     balanceJson.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \date   : 11 Juin 2018
    \brief   Programme pour l'envoi du poids au format JSON
    \details Renvoie la valeur mesurée au format JSON
    Compilation : g++ balanceJson.cpp hx711.cpp  spi.c -o balanceJson
    Installation: sudo chown root balanceJson
                  sudo chmod +s balanceJson
                  sudo mv balanceJson /usr/lib/cgi-bin/balanceJson
    \version	v1.0 - First release
*/

#include <iostream>
#include <fstream>
#include <iomanip>

#include "hx711.h"


using namespace std;

int main()
{

    hx711   balance;
    float   scale;
    int     offset;
    int     gain;
    string  unite;
    int     precision = 1;

    // Lecture du fichier de configuration
    ifstream fichier("/home/pi/Capteurs_I2C/HX711/balance.ini");

    if (fichier.fail())
    {
        cout << "Erreur lors de l'ouverture du fichier de configuration" << endl;
    	balance.fixerEchelle(1);
        balance.fixerOffset(0);
        balance.configurerGain(128);
    }
    else
    {
	fichier >> scale >> offset >> gain >> unite >> precision;
	balance.fixerEchelle(scale);
        balance.fixerOffset(offset);
        balance.configurerGain(gain);
    }

    cout << "Content-type: application/json" << endl << endl;
    cout << "{" << endl;
    cout << "\"Weight\":\"" << fixed << setprecision (precision) << balance.obtenirPoids() << " " << unite << "\""<< endl;
    cout << "}" << endl;
}
