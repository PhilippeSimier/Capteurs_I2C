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
    char adresse = 0x40;
    ina219 capteur(adresse);

if (!capteur.obtenirErreur()){

    float en = 0.0; // l'energie en J (Ws)
    int t = 10;  // période d'échantillonage (10s)
    float courant = 0;
    float tension = 0;

    capteur.fixerCalibration_16V();

    while(1){

        cout << " Tension bus   : " << fixed << setprecision (2) << tension  << " V" << endl;
        cout << " Tension shunt : " << fixed << setprecision (2) << capteur.obtenirTensionShunt_mV() << " mV" << endl;
        if (courant > 1.0)
            cout << " Courant bus   : " << fixed << setprecision (2) << courant << " A" << endl;
        else
	    cout << " Courant bus   : " << fixed << setprecision (2) << courant * 1000  << " mA" << endl;
        cout << " Puissance bus : " << fixed << setprecision (2) << courant * tension << " W" << endl;
        cout << " Batterie SOC  : " << fixed << setprecision (0) << capteur.obtenirBatterieSOC() << " %" << endl;
	cout << " Energie       : " << fixed << setprecision (2) << en / 3.6 << " mWh" << endl;
	courant = capteur.obtenirCourantMoyen_A(t * 100); // 1000 * 1/100s
        tension = capteur.obtenirTension_V();
        en += courant * tension * t; // energie en Joule (Ws)
        system("clear");
    }
}
else{
	cout << " Le capteur INA219 n'est pas présent à l'adresse : 0x" << hex << (int)adresse << endl;
	capteur.version();
    }
    return 0;
}


