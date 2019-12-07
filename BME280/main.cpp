/*******************************************************************************************
*   Compilation :  g++ main.cpp i2c.cpp  bme280.cpp -o main
*******************************************************************************************/

#include <iostream>
#include "bme280.h"
#include <unistd.h>

using namespace std;

int main()
{
    char adresse = 0x77;    // l'adresse du composant BME280
    bme280 capteur(adresse);
    if (!capteur.obtenirErreur()){

    	cout << "Capteur BME 280 présent sur le bus I2C" << endl;
        capteur.donnerAltitude(62);

        while(1){
    	    cout << " Température    : " << fixed << setprecision (2) << capteur.obtenirTemperatureEnC() << " °C"<< endl;
	    cout << " Pression       : " << fixed << setprecision (1) << capteur.obtenirPression() << " hPa"<< endl;
            cout << " Humidité       : " << fixed << setprecision (1) << capteur.obtenirHumidite() << " %"<< endl;
            cout << " Pression P0    : " << fixed << setprecision (1) << capteur.obtenirPression0() << " hPa"<< endl;
            cout << " Point de rosée : " << fixed << setprecision (1) << capteur.obtenirPointDeRosee() << " °C"<< endl;

    	    sleep(1);
	    system("clear");
    	}
    }
    else{
	cout << " Le capteur BME280 n'est pas présent à l'adresse : 0x" << hex << (int)adresse << endl;
	capteur.version();
    }

    return 0;
}
