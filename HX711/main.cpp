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
    float yn   = 0.0;
    float yn_1 = 0.0;
    char  stable;
    int   scale;
    int   offset;
    int   gain;
    string unite;

    ifstream fichier("balance.ini"); //Creation du flux en lecture sur le fichier de configuration

    if (fichier.fail())
    {
        cerr << "Erreur lors de l'ouverture du fichier de configuration" << endl;
    	balance.fixerEchelle(1);
        balance.fixerOffset(0);
        balance.configurerGain(128);
    }
    else
    {
	fichier >> scale >> offset >> gain >> unite;
	balance.fixerEchelle(scale);
        balance.fixerOffset(offset);
        balance.configurerGain(gain);
    }

    while(1)
    {
	xn = balance.obtenirPoids();
	// Filtrage passe bas du premier ordre constante de temps 2.Te  (20ms)
        // Filtre passe bas du premier ordre constante de temps 10.Te (100ms)
        // yn = 0.091 * xn + 0.91 * yn_1;
	 yn = 0.3333 * xn + 0.6666 * yn_1;

	// calcul de la dérivée
	if ((yn_1 - yn) < 0.1 && (yn_1 - yn) > - 0.002)
            stable = '*';
        else stable = ' ';
        yn_1 = yn;

        cout << stable << " " << yn << fixed << setprecision (1) << " " << unite << endl;
        usleep(100000);
        system("clear");
    }
}
