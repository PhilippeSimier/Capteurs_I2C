/************************************************************************************
/*!
    \file     main.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \date     25 Mai 2017
    \brief    Programme exemple mise en oeuvre du ina219

    \details  Renvoie les valeurs mesurées par le capteur ina219 au format text
              sur la sortie standard
	      avec une précison de deux chiffres après la virgule.
    Compilation  : g++ main.cpp i2c.cpp  ina219.cpp -o main
    Exécution : ./main
    Documentation :  https://philippes.ddns.net/documentation/Raspberry_pi/50%20Raspberry%20alim%20solaire.pdfDocumentation :  https://philippes.ddns.net/documentation/Raspberry_pi/50%20Raspberry%20alim%20solaire.pdf
    \version  v1.0 - First release
*/
/*********************************************************************************/


#include <iostream>
#include <unistd.h>
#include "ina219.h"

using namespace std;

int main()
{
    system("clear");
    ina219 capteur;

    float en = 0.0; // l'energie en J (Ws)
    int t = 2;  // période d'échantillonage (2s)

    capteur.fixerCalibration_16V();

    cout << "Capteur INA219" << endl;
    while(1){

        cout << " Tension bus   : " << fixed << setprecision (3) << capteur.obtenirTension_V()  << " V" << endl;
        cout << " Tension shunt : " << fixed << setprecision (3) << capteur.obtenirTensionShunt_mV() << " mV" << endl;
        cout << " Courant bus   : " << fixed << setprecision (3) << capteur.obtenirCourant_A() << " A" << endl;
        cout << " Puissance bus : " << fixed << setprecision (3) << capteur.obtenirPuissance_W() << " W" << endl;
        cout << " Batterie SOC  : " << fixed << setprecision (0) << capteur.obtenirBatterieSOC() << " %" << endl;
	en += capteur.obtenirPuissance_W() * t;
	cout << " Energie       : " << fixed << setprecision (3) << en / 3.6 << " mWh" << endl;
	sleep(t);
        system("clear");
    }


    capteur.version();
    return 0;
}


