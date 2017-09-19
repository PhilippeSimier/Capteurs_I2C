/*!
    \file     main.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \date     17 septembe 2017
    \brief    Programme exemple mise en oeuvre du circuit HX711
    \details
	Le circuit HX711 doit être connecté de la manière suivante
	clock -> GPIO23 -> WiringPin 4
        data  -> GPIO24 -> WiringPin 5
        Vcc   -> 5V
        Gnd   -> Gnd

	compilation : g++ main.cpp  hx711.cpp -lwiringPi -o main

    \version V1.0 First release
*/

#include <iostream>
#include <iomanip>
#include <unistd.h>  // pour la fct sleep
#include <stdlib.h>  // pour la fct system
#include <math.h>
#include "hx711.h"

using namespace std;

int main()
{
    float poids;
    system("clear");
    HX711 capteur(4, 5);  // clock data

    cout << "Capteur de pesage 5000g" << endl;

    if (capteur.isReady()){
    	cout << "Capteur de pesage connecté" << endl;
        capteur.fixerGain(128);
	capteur.tarer(5);
        cout << "tare : " << capteur.obtenirOffset() << endl;
        sleep(2);
	capteur.fixerEchelle(-426.5);   // Valeur négative car le capteur est montée en traction
	while(true){
                poids = round (capteur.obtenirPoids(5) / 5) * 5;
		system("clear");
		cout << "Poids : " << fixed << setprecision (0) << poids << " g " << endl;
		sleep(1);
        }
    }
    else{
	cout << "Probleme de connexion avec le capteur!!!" << endl;
    };


    return 0;
}
