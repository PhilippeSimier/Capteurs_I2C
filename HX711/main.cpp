/**
 *  @file     main.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     15 avril 2018
 *  @brief    programme exemple balance
 *            compilation: g++ main.cpp hx711.cpp  spi.c -o main
*/

#include <iostream>
#include <fstream>
#include <iomanip>

#include "hx711.h"


using namespace std;

int main()
{

    hx711 balance;
    float xn;
    float xn_1 = 0.0;
    char  stable;
    float scale;
    int   offset;
    int   gain;
    string unite;
    int   precision = 1;

    ifstream fichier("balance.ini"); //Creation du flux en lecture sur le fichier de configuration

    if (fichier.fail())
    {
        cerr << "Erreur lors de l'ouverture du fichier de configuration" << endl;
    	balance.fixerEchelle(1.0);
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
