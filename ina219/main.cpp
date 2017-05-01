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
    ina219 capteur;

    cout << "Capteur INA219" << endl;
    cout << " Tension bus   : " << fixed << setprecision (3) << capteur.obtenirTension_V() << " V"<< endl;
    cout << " Tension shunt : " << fixed << setprecision (3) << capteur.obtenirTensionShunt_mV() << " mV"<< endl;
    cout << " Courant bus   : " << fixed << setprecision (3) << capteur.obtenirCourant_A() << " A"<< endl;
    cout << " Puissance bus : " << fixed << setprecision (3) << capteur.obtenirPuissance_W() << " W"<< endl;
    capteur.version();
    return 0;
}


