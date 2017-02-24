/************************************************************************************
*   Programme exemple mise en oeuvre du bme280
*   sujet : envoie des valeurs du capteur BME280 au format JSON
*           Les différentes valeures sont envoyées sur la sortie standard
*   Auteur : Philippe SIMIER (SNIR Touchard le Mans)
*   Date   : 6 Février 2017
*   Compilation : g++ bme280Json.cpp bm280.cpp i2c.cpp -o bme280Json
*                 chmod +s bme280Json
*                 mv bme280Json /usr/lib/cgi-bin/bme280Json
************************************************************************************/
#include <iostream>
#include "bm280.h"

using namespace std;

int main()
{
    bm280 capteur;
    float altitude = 74.0; // altitude ou se situe le capteur chez moi)
    capteur.donnerAltitude(altitude);

    cout << "Content-type: application/json" << endl << endl;
    cout << "{" << endl;
    cout << "\"altitude\":\"" << altitude << " m\"," << endl;
    cout << "\"TemperatureC\":\"" << fixed << setprecision (1) << capteur.obtenirTemperatureEnC() << " °C\"," << endl;
    cout << "\"TemperatureF\":\"" << fixed << setprecision (1) << capteur.obtenirTemperatureEnF() << " F\"," << endl;
    cout << "\"Pression\":\"" << fixed << setprecision (1) << capteur.obtenirPression0() << " hPa\","<< endl;
    cout << "\"Humidite\":\"" << fixed << setprecision (1) << capteur.obtenirHumidite() << " %\","<< endl;
    cout << "\"PointRosee\":\"" << fixed << setprecision (1) << capteur.obtenirPointDeRosee() << " °C\""<< endl;
    cout << "}" << endl;
    return 0;
}
