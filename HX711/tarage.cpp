/**
 *  @file     tarage.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     29 juin 2018
 *  @brief    programme pour effectuer le tarage de la balance
 *            ce programme détermine la constante offset et
 *            l'enregistre dans le fichier configuration.ini
 *            compilation: g++ tarage.cpp hx711.cpp SimpleIni.cpp  spi.c -o tarage
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
    int gain;

    if(!ini.Load("/home/pi/Capteurs_I2C/HX711/configuration.ini"))
    {
        cout << "Impossible d'ouvrir le fichier configuration.ini !!" << endl;
        return -1;
    }

    gain   = ini.GetValue<int>("balance", "gain", 128);
    balance.configurerGain(gain);

    /** début de la procédure de tarage
	10 mesures du poids sont effectuées
        Les plus grande et plus petite valeurs sont retirées
        puis la moyenne est calculée avec les 8 mesures restantes
    */
    int x1, max, min, som, offset;
    som = balance.obtenirValeur();
    cout << som << endl;
    min = som;
    max = som;
    for(int i=1 ; i<10 ; i++)
    {
        x1 = balance.obtenirValeur();
        cout << x1 << endl;
        som += x1;
        if (x1 > max) max = x1;
        if (x1 < min) min = x1;
    }
    offset = (som - max - min)/ 8;
    cout << "offset : " << offset << endl;
    ini.SetValue<int>("balance", "offset", offset);

    if(!ini.Save())
    {
        cout << "Impossible d'écrire dans configuration.ini." << endl;
        return -1;
    }

    cout << "La valeur de l'offset a été enregistrée dans le fichier configuration.ini" << endl;

    return 0;

}
