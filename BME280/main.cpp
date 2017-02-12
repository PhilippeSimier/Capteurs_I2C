/*******************************************************************************************
*   Compilation :  g++ main.cpp i2c.cpp  bm280.cpp -o bm280
*******************************************************************************************/

#include <iostream>
#include "bm280.h"

using namespace std;

int main()
{
    bm280 capteur;
    float h;

    cout << "Capteur BME 280" << endl;
    cout << "Donner l'altidude du capteur :";
    cin >> h;
    capteur.donnerAltitude(h);
    cout << " Température (C)  : " << fixed << setprecision (1) << capteur.obtenirTemperatureEnC() << " °C"<< endl;
    cout << " Température (F)  : " << fixed << setprecision (1) << capteur.obtenirTemperatureEnF() << " °F"<< endl;
    cout << " Pression         : " << fixed << setprecision (1) << capteur.obtenirPression() << " hPa"<< endl;
    cout << " Humidité         : " << fixed << setprecision (1) << capteur.obtenirHumidite() << " %"<< endl;
    cout << " Pression P0      : " << fixed << setprecision (1) << capteur.obtenirPression0() << " hPa"<< endl;
    capteur.version();
    return 0;
}
