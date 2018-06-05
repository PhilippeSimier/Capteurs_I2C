/**
 *  @file     main.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     15 avril 2018
 *  @brief    programme étalonnage capteur
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
    float poids;

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

    int som = 0;
    for(int i=0 ; i<100 ; i++)
    {
	x1 = balance.obtenirValeur();
        cout << x1 << endl;
        usleep(100000);
        som += x1;
    }
    x1 = som / 100;
    cout << "offset : " << x1 << endl;

    cout << "Poser le poids étalon : " << endl;
    cin >> poids;
    cout << "Vous avez entré " << poids << endl;

    som = 0;
    for(int i=0 ; i<100 ; i++)
    {
        x2 = balance.obtenirValeur();
        cout << x2 << endl;
        usleep(100000);
        som += x2;
    }
    x2 = som / 100;
    cout << "valeur2 : " << (x2 - x1)/poids  << endl;




}
