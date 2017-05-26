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
	float u,us,i,p;
        float en = 0.0; // l'energie en J (Ws)
        int t = 1;  // période d'échantillonage (1s)

    	cout << "Capteur INA219" << endl;
       while(1){
	u = capteur.obtenirTension_V();
	us = capteur.obtenirTensionShunt_mV();
        i = us/100.0;  // I = U/R   avec R = 100 mOhms
        p = u*i;
	en += p*t;

        cout << " Tension bus   : " << fixed << setprecision (3) << u  << " V" << endl;
        cout << " Tension shunt : " << fixed << setprecision (3) << us << " mV" << endl;
        cout << " Courant bus   : " << fixed << setprecision (3) << i << " A" << endl;
        cout << " Puissance bus : " << fixed << setprecision (3) << p << " W" << endl;
	cout << " Energie       : " << fixed << setprecision (3) << en / 3.6 << " mWh" << endl;
	sleep(1);
        system("clear");
       }


capteur.version();
    return 0;
}


