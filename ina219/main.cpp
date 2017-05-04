/*******************************************************************************************
*   Sujet         :  Programme pour test unitaire de la classe ina219
*   Auteur        :  Philippe SIMIER  Touchard Le Mans
*   Compilation   :  g++ main.cpp i2c.cpp  ina219.cpp -o test1
*   Documentation :  https://philippes.ddns.net/documentation/Raspberry_pi/50%20Raspberry%20alim%20solaire.pdf
*******************************************************************************************/

#include <iostream>
#include "ina219.h"

using namespace std;

int main()
{
	system("clear");
    	ina219 capteur;
	float U,Us,I;

    	cout << "Capteur INA219" << endl;

	U = capteur.obtenirTension_V();
	Us = capteur.obtenirTensionShunt_mV();
        I = Us/100.0;  // I = U/R   avec R = 100 mOhms
        cout << " Tension bus   : " << fixed << setprecision (3) << U  << " V"<< endl;
        cout << " Tension shunt : " << fixed << setprecision (3) << Us << " mV"<< endl;
        cout << " Courant bus   : " << fixed << setprecision (3) << I << " A"<< endl;
        cout << " Puissance bus : " << fixed << setprecision (3) << U*I << " W"<< endl;


capteur.version();
    return 0;
}


