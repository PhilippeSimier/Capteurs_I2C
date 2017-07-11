/************************************************************************************
/*!
    \file     bh1750Json.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \date   : mardi 27 Juin 2017

    \brief    Programme exemple mise en oeuvre du bh1750
    \details  Renvoie la valeur de l'éclairement  mesurée par
              le capteur bh1750 au format JSON
              Les différentes valeures sont envoyées sur la sortie standard.
    Compilation  : g++ bh1750Json.cpp bh1750.cpp i2c.cpp -o bh1750Json
    Installation : sudo chown root bh1750Json
                   sudo chmod +s bh1750Json
                   sudo mv bh1750Json /usr/lib/cgi-bin/bh1750Json

    \version  v1.0 - First release
*/
/*******************************************************************************/
#include <iostream>
#include <iomanip>      // std::setprecision
#include "bh1750.h"

using namespace std;

int main()
{
    bh1750 *capteur;

    capteur = new bh1750();   // déclaration d'un capteur de type bh1750 à l'adresse par défaut 0x23
    capteur->configurer(BH1750_ONE_TIME_HIGH_RES_MODE_2);
    float level = capteur->obtenirLuminosite_Lux();

    cout << "Content-type: application/json" << endl << endl;

    cout << "{" << endl;
    cout << "\"Eclairement\": " << fixed << setprecision (0) << level << "," << endl;
    cout << "\"unite\" : \"lx\"" << endl;
    cout << "}" << endl;

    delete capteur;
    return 0;
}
