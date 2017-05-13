/*******************************************************************************************
*   Compilation :  g++ main.cpp i2c.cpp  bm280.cpp -o bm280
*******************************************************************************************/

#include <iostream>
#include "bm280.h"
#include <unistd.h>

using namespace std;

int main()
{
    bm280 capteur;

    cout << "Capteur BME 280" << endl;

    while(1){
	bm280 capteur;
	capteur.donnerAltitude(74);
    	cout << " Température (C)  : " << fixed << setprecision (1) << capteur.obtenirTemperatureEnC() << " °C"<< endl;
    	cout << " Température (F)  : " << fixed << setprecision (1) << capteur.obtenirTemperatureEnF() << " °F"<< endl;
    	cout << " Pression         : " << fixed << setprecision (1) << capteur.obtenirPression() << " hPa"<< endl;
    	cout << " Humidité         : " << fixed << setprecision (1) << capteur.obtenirHumidite() << " %"<< endl;
    	cout << " Pression P0      : " << fixed << setprecision (1) << capteur.obtenirPression0() << " hPa"<< endl;
    	cout << " Point de rosée   : " << fixed << setprecision (1) << capteur.obtenirPointDeRosee() << " °C"<< endl;
    	sleep(1);
    }

    return 0;
}
