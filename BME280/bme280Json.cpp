/************************************************************************************
/*!
    \file     bme280Json.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \date   : 10 Aout 2017


    \brief   Programme exemple mise en oeuvre du bme280
    \details Renvoie les valeurs mesurées par le capteur BME280 au format JSON


    Compilation : g++ bme280Json.cpp bme280.cpp i2c.cpp -o bme280Json
    Installation: sudo chown root bme280Json
                  sudo chmod +s bme280Json
                  sudo mv bme280Json /usr/lib/cgi-bin/bme280Json

    \version	v2.0 - Second release
*/

#include <iostream>
#include "bme280.h"

using namespace std;

int main()
{
    bme280 capteur(0x77);
    float altitude = 62.0; // altitude en métre ou se situe le capteur très important pour calculer la pression au niveau de la mer
    capteur.donnerAltitude(altitude);

    if (!capteur.obtenirErreur()){
    	cout << "Content-type: application/json" << endl << endl;
    	cout << "{" << endl;
        cout << "\"OK\" : true," << endl;
    	cout << "\"altitude\":\"" << altitude << " m\"," << endl;
    	cout << "\"TemperatureC\":\"" << fixed << setprecision (1) << capteur.obtenirTemperatureEnC() << " °C\"," << endl;
    	cout << "\"TemperatureF\":\"" << fixed << setprecision (1) << capteur.obtenirTemperatureEnF() << " F\"," << endl;
    	cout << "\"Pression\":\"" << fixed << setprecision (1) << capteur.obtenirPression0() << " hPa\","<< endl;
    	cout << "\"Humidite\":\"" << fixed << setprecision (1) << capteur.obtenirHumidite() << " %\","<< endl;
    	cout << "\"PointRosee\":\"" << fixed << setprecision (1) << capteur.obtenirPointDeRosee() << " °C\""<< endl;
    	cout << "}" << endl;
    } else {
     	cout << "Content-type: application/json" << endl << endl;
        cout << "{" << endl;
        cout << "\"OK\" : false" << endl;
        cout << "}" << endl;
    }

    return 0;

}
