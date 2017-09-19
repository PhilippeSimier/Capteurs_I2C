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

	compilation : g++ passebas.cpp  hx711.cpp -lwiringPi -o passebas

    \version V1.0 First release
*/

#include <iostream>
#include <iomanip>
#include <unistd.h>  // pour la fct usleep
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
                // Filtre passe bas du premier ordre constante de temps 2.Te  (20ms)
		//poids = 0.33 * capteur.obtenirPoids(3) + 0.66 * poids;  // yn = 0,33.xn + 0,66.yn-1
		// Filtre passe bas du premier ordre constante de temps 10.Te (100ms)
		poids = 0.091 * capteur.obtenirPoids(3) + 0.91 * poids;  // yn = 0,091.xn + 0,91.yn-1
		system("clear");
		cout << "Poids : " << fixed << setprecision (0) << poids << " g " << endl;
		//usleep(1000);  // 1ms
        }
    }
    else{
	cout << "Probleme de connexion avec le capteur!!!" << endl;
    };


    return 0;
}
