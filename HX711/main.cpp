/**
 *  @file     main.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     15 avril 2018
 *  @brief    programme balance
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

    ifstream fichier("balance.ini"); //Creation du flux en lecture sur le fichier de configuration

    if (fichier.fail())
        cerr << "Erreur lors de l'ouverture du fichier de configuration" << endl;
    else
    {
	fichier >> scale >> offset;
	cout << " scale : " << scale;
        cout << " offset : " << offset;
	balance.fixerEchelle(scale);
        balance.fixerOffset(offset);
    }

    while(1)
    {
	xn = balance.obtenirPoids();
	// Filtrage passe bas du premier ordre constante de temps 2.Te  (20ms)
        // Filtre passe bas du premier ordre constante de temps 10.Te (100ms)
        // yn = 0,091.xn + 0,91.yn-1;
	yn = 0.33 * xn + 0.66 * yn_1;

	// calcul de la dérivée
	if ((yn_1 - yn) < 0.1 && (yn_1 - yn) > - 0.1)
            stable = '*';
        else stable = ' ';
        yn_1 = yn;

        cout << stable << " " << yn << fixed << setprecision (2) << " kg" << endl;
        usleep(100000);
        system("clear");
    }
}
