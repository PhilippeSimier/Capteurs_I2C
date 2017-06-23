/*******************************************************************************************
*   Sujet         :  Programme pour test unitaire de la classe ina219
*   Auteur        :  Philippe SIMIER  Touchard Le Mans
*   Compilation   :  g++ main.cpp i2c.cpp  ina219.cpp -o main
*   Documentation :  https://philippes.ddns.net/documentation/Raspberry_pi/50%20Raspberry%20alim%20solaire.pdf
*******************************************************************************************/

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

    cout << "Capteur INA219" << endl;
    while(1){

        cout << " Tension bus   : " << fixed << setprecision (3) << capteur.obtenirTension_V()  << " V" << endl;
        cout << " Tension shunt : " << fixed << setprecision (3) << capteur.obtenirTensionShunt_mV() << " mV" << endl;
        cout << " Courant bus   : " << fixed << setprecision (3) << capteur.obtenirCourant_A() << " A" << endl;
        cout << " Puissance bus : " << fixed << setprecision (3) << capteur.obtenirPuissance_W() << " W" << endl;
	en += capteur.obtenirPuissance_W() * t;
	cout << " Energie       : " << fixed << setprecision (3) << en / 3.6 << " mWh" << endl;
	sleep(t);
        system("clear");
       }


    capteur.version();
    return 0;
}


