/************************************************************************************
*   Programme exemple mise en oeuvre du bme280
*   sujet : envoie des valeurs du capteur BME280 au format JSON
*           Les différentes valeures sont envoyées sur la sortie standard
*   Auteur : Philippe SIMIER (SNIR Touchard le Mans)
*   Date   : 31 Janvier 2017
*   Compilation : g++ bme280Json.cpp bm280.cpp -l wiringPi -o bme280Json
*                 chmod +s bme280Json
*                 mv bme280Json /usr/lib/cgi-bin/bme280Json
************************************************************************************/
#include <iostream>
#include "bm280.h"

using namespace std;

int main()
{
    bm280 capteur;
    cout << "Content-type: application/json" << endl << endl;
    cout << "{" << endl;

    cout << "\"TemperatureC\":\"" << capteur.obtenirTemperatureEnC() << "\"," << endl;
    cout << "\"TemperatureF\":\"" << capteur.obtenirTemperatureEnF() << "\"," << endl;
    cout << "\"Pression\":\"" << capteur.obtenirPression() << "\","<< endl;
    cout << "\"Humidite\":\"" << capteur.obtenirHumidite() << "\","<< endl;
    cout << "\"AltitudeM\":\"" << capteur.obtenirAltitudeEnMetres() << "\","<< endl;
    cout << "\"AltitudeF\":\"" << capteur.obtenirAltitudeEnPieds() << "\"" << endl;

    cout << "}" << endl;
    return 0;
}
