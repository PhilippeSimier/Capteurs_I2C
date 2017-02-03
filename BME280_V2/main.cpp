#include <iostream>
#include "bm280.h"

using namespace std;

int main()
{
    bm280 capteur;


    cout << "Capteur BME 280" << endl;

    cout << " Température (C)  : " << fixed << setprecision (1) << capteur.obtenirTemperatureEnC() << " °C"<< endl;
    cout << " Température (F)  : " << fixed << setprecision (1) << capteur.obtenirTemperatureEnF() << " °F"<< endl;
    cout << " Pression         : " << fixed << setprecision (1) << capteur.obtenirPression() << " hPa"<< endl;
    cout << " Humidité         : " << fixed << setprecision (1) << capteur.obtenirHumidite() << " %"<< endl;
    cout << " Altitude (metre) : " << capteur.obtenirAltitudeEnMetres() << " m"<< endl;
    cout << " Altitude (feet)  : " << capteur.obtenirAltitudeEnPieds() << "\"" << endl;
    capteur.version();
    return 0;
}
