/**
 *  @file     main.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     15 avril 2018
 *  @brief    programme exemple balance
 *            compilation: g++ main.cpp hx711.cpp SimpleIni.cpp spi.c -o main
*/

#include <iostream>
#include <fstream>
#include <iomanip>

#include "hx711.h"
#include "SimpleIni.h"

using namespace std;

int main()
{

    hx711 balance;
    SimpleIni ini;
    float xn;
    float xn_1 = 0.0;
    char  stable;
    float scale;
    int   offset;
    int   gain;
    string unite;
    int   precision = 1;

    // Lecture du fichier de configuration
    ini.Load("configuration.ini");
    scale  = ini.GetValue<float>("balance", "scale", 1.0 );
    offset = ini.GetValue<int>("balance", "offset", 0);
    gain   = ini.GetValue<int>("balance", "gain", 128);
    unite  = ini.GetValue<string>("balance", "unite", "Kg");
    precision = ini.GetValue<int>("balance", "precision", 1);

    // Configuration de la balance
    balance.fixerEchelle(scale);
    balance.fixerOffset(offset);
    balance.configurerGain(gain);

    while(1)
    {
	xn = balance.obtenirPoids();
        system("clear");

	// calcul de la dérivée
	if ((xn_1 - xn) < 0.1 && (xn_1 - xn) > - 0.1)
            stable = '*';
        else stable = ' ';
        xn_1 = xn;

        cout << stable << " " << xn << fixed << setprecision (precision) << " " << unite << endl;
    }
}
