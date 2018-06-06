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

    do
    {
        cout << "Donnez le gain souhaité : 128 ou 64 ? " << endl;
        cin >> gain;
    }
    while (gain !=128 && gain !=64);

    balance.configurerGain(gain);

    int som = 0;
    for(int i=0 ; i<100 ; i++)
    {
	x1 = balance.obtenirValeur();
        cout << x1 << endl;
        usleep(100000);
        som += x1;
    }
    offset = som / 100;
    cout << "offset : " << offset << endl;

    cout << "Posez un poids étalon sur le plateau et donnez sa valeur en kg : " << endl;
    cin >> poids;
    cout << "Vous avez posé un poids de " << poids << " kg" << endl;

    som = 0;
    for(int i=0 ; i<100 ; i++)
    {
        x2 = balance.obtenirValeur();
        cout << x2 << endl;
        usleep(100000);
        som += x2;
    }
    x2 = som / 100;
    scale = (x2 - offset)/poids;
    cout << "scale : " << scale  << endl;
    cout << endl << scale << " " << offset << " " << gain << endl;
    // ecriture du fichier de configuration de la balance
    ofstream output("balance.ini");
    output << scale << " " << offset << " " << gain << endl;

}
