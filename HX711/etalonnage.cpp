/**
 *  @file     main.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     6 juin 2018
 *  @brief    programme étalonnage de la balance
 *            ce programme détermine les constantes offset scale et gain et
 *            les enregistre dans le fichier balance.ini
 *            compilation: g++ etalonnage.cpp hx711.cpp  spi.c -o etalonnage
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "hx711.h"


using namespace std;

int main()
{

    hx711 balance;
    int x1,x2;
    int offset;
    int scale;
    int gain;
    float poids;
    string unite;

    cout << "Quelle est l'unité de mesure ? (g kg lb)" << endl;
    cin >> unite;

    do
    {
        cout << "Donnez le gain souhaité : 128 ou 64 ? " << endl;
        cin >> gain;
    }
    while (gain !=128 && gain !=64);

    balance.configurerGain(gain);

    int max,min,som;
    som = balance.obtenirValeur();
    min = som;
    max = som;
    for(int i=1 ; i<100 ; i++)
    {
        usleep(100000);
	x1 = balance.obtenirValeur();
        cout << x1 << endl;
        som += x1;
	if (x1 > max) max = x1;
	if (x1 < min) min = x1;
    }
    offset = (som - max - min)/ 98;
    cout << "offset : " << offset << endl;
    cout << "Posez un poids étalon sur le plateau et donnez sa valeur en " << unite << " : " << endl;
    cin >> poids;
    cout << "Vous avez posé un poids de " << poids << " kg" << endl;

    som = balance.obtenirValeur();
    max = som;
    min = som;
    for(int i=1 ; i<100 ; i++)
    {
        usleep(100000);
        x2 = balance.obtenirValeur();
        cout << x2 << endl;
        som += x2;
        if (x2 > max) max = x2;
        if (x2 < min) min = x2;

    }
    x2 = (som - max - min)/98 ;
    scale = (x2 - offset)/poids;
    cout << "scale : " << scale  << endl;
    cout << endl << scale << " " << offset << " " << gain << endl;
    // ecriture du fichier de configuration de la balance
    ofstream output("balance.ini");
    output << scale << " " << offset << " " << gain << " " << unite << endl;

}
