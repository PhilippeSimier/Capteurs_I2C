/**
 *  @file     main.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     6 juin 2018
 *  @brief    programme étalonnage de la balance
 *            ce programme détermine les constantes offset scale et gain et
 *            les enregistre dans le fichier configuration.ini
 *            compilation: g++ etalonnage.cpp hx711.cpp SimpleIni.cpp  spi.c -o etalonnage
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

    int x1,x2;
    int offset;
    float scale;
    int gain;
    float poids;
    string unite;
    int precision;

    if(!ini.Load("configuration.ini"))
    {
        cout << "Impossible d'ouvrir le fichier configuration.ini !!" << endl;
        return -1;
    }

    cout << "Quelle est l'unité de mesure ? (g kg lb)" << endl;
    cin >> unite;
    ini.SetValue<string>("balance", "unite", unite);

    do
    {
        cout << "Quelle est la précision d'affichage : 1 ou 2 chiffres après la virgule" << endl;
        cin >> precision;
    }
    while (precision !=1 && precision !=2);
    ini.SetValue<int>("balance", "precision", precision);

    do
    {
        cout << "Donnez le gain souhaité : 128 ou 64 ? " << endl;
        cin >> gain;
    }
    while (gain !=128 && gain !=64);
    ini.SetValue<int>("balance", "gain", gain);

    balance.configurerGain(gain);
    int max,min,som;
    som = balance.obtenirValeur();
    min = som;
    max = som;
    for(int i=1 ; i<100 ; i++)
    {
        x1 = balance.obtenirValeur();
        cout << x1 << endl;
        som += x1;
        if (x1 > max) max = x1;
        if (x1 < min) min = x1;
    }
    offset = (som - max - min)/ 98;
    cout << "offset : " << offset << endl;
    ini.SetValue<int>("balance", "offset", offset);

    cout << "Posez un poids étalon sur le plateau et donnez sa valeur en " << unite << " : " << endl;
    cin >> poids;
    cout << "Vous avez posé un poids de " << poids << " " << unite << endl;

    som = balance.obtenirValeur();
    max = som;
    min = som;
    for(int i=1 ; i<100 ; i++)
    {
        x2 = balance.obtenirValeur();
        cout << x2 << endl;
        som += x2;
        if (x2 > max) max = x2;
        if (x2 < min) min = x2;

    }
    x2 = (som - max - min)/98 ;
    scale = (float)(x2 - offset)/poids;
    cout << "scale : " << scale  << endl;
    ini.SetValue<float>("balance", "scale", scale);


    if(!ini.SaveAs("configuration.ini"))
    {
        cout << "Impossible d'écrire dans configuration.ini." << endl;
        return -1;
    }

    cout << "Le fichier de configuration : configuration.ini a été enregistré." << endl;

    return 0;

}


