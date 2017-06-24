/************************************************************************************
/*!
    \file     ina219Json.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \date   : 25 Mai 2017


    \brief    Programme exemple mise en oeuvre du ina219
    \details  Renvoie les valeurs mesurées par le capteur ina219 au format JSON
              Les différentes valeures sont envoyées sur la sortie standard
	      avec une précison de deux chiffres après la virgule.


    Compilation  : g++ ina219Json.cpp ina219.cpp i2c.cpp -o ina219Json
    Installation : sudo chown root ina219Json
                   sudo chmod +s ina219Json
                   sudo mv ina219Json /usr/lib/cgi-bin/ina219Json

    \version  v1.0 - First release
*/
/*********************************************************************************/
#include <iostream>
#include "ina219.h"

using namespace std;

int main()
{
    ina219 *capteur;

    capteur = new ina219();   // déclaration d'un capteur de type ina219 à l'adresse par défaut 0x40
    float u = capteur->obtenirTension_V();
    float i = capteur->obtenirCourant_A();
    float p = u*i;

    cout << "Content-type: application/json" << endl << endl;

    cout << "{" << endl;
    cout << "\"u\": " << fixed << setprecision (2) << u << "," << endl;
    cout << "\"uniteU\" : \"V\"," << endl;

    if (i < -1 || i > 1){
    	cout << "\"i\":" << fixed << setprecision (2) << i << "," << endl;
        cout << "\"uniteI\" : \"A\"," << endl;
    }
    else{
	cout << "\"i\":" << fixed << setprecision (2) << i * 1000 << "," << endl;
        cout << "\"uniteI\" : \"mA\"," << endl;
    }

    if (p < -1 || p > 1){
    	cout << "\"p\":" << fixed << setprecision (2) << p << "," << endl;
    	cout << "\"uniteP\" : \"W\"" << endl;
    }
    else{
        cout << "\"p\":" << fixed << setprecision (2) << p * 1000 << "," << endl;
        cout << "\"uniteP\" : \"mW\"" << endl;

    }
    cout << "}" << endl;

    delete capteur;
    return 0;
}
