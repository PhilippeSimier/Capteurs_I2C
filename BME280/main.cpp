#include <iostream>
#include "bm280.h"

using namespace std;

int main()
{
    bm280 capteur;


    cout << "Capteur BME 280" << endl;

    cout << " Température (C)  : " << capteur.obtenirTemperatureEnC() << " °C"<< endl;
    cout << " Température (F)  : " << capteur.obtenirTemperatureEnF() << " °F"<< endl;
    cout << " Pression         : " << capteur.obtenirPression() << " hPa"<< endl;
    cout << " Humidité         : " << capteur.obtenirHumidite() << " %"<< endl;
    cout << " Altitude (metre) : " << capteur.obtenirAltitudeEnMetres() << " m"<< endl;
    cout << " Altitude (feet)  : " << capteur.obtenirAltitudeEnPieds() << "\"" << endl;
    return 0;
}
