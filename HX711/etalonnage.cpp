/**
 *  @file     main.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     15 avril 2018
 *  @brief    programme étalonnage la balance
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

    ifstream fichier("balance.ini"); //Creation du flux en lecture sur le fichier de configuration

    if (fichier.fail())
        cerr << "Erreur lors de l'ouverture du fichier de configuration" << endl;
    else
    {
	fichier >> scale >> offset >> gain;
	cout << " scale : " << scale;
        cout << " offset : " << offset;
	balance.fixerEchelle(scale);
        balance.fixerOffset(offset);
        balance.configurerGain(gain);
    }

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

    cout << "donner la valeur du poids étalon posé sur le plateau en kg: " << endl;
    cin >> poids;
    cout << "Vous avez posé un poids de " << poids << endl;

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
