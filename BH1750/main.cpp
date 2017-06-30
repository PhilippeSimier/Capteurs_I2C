/************************************************************************************
/*!
    \file     main.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \date     26 Juin 2017
    \brief    Programme exemple mise en oeuvre du capteur d'éclairement lumineux bh170
    \details
	compilation : g++ main.cpp i2c.cpp  bh1750.cpp -o main

    \version V1.0 First release
*/


#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "bh1750.h"

using namespace std;

int main()
{
    system("clear");
    bh1750 capteur;

    cout << "Capteur d'éclairement" << endl;

    capteur.activer();
    capteur.reset();


    while(1){
        capteur.configurer(BH1750_CONTINUOUS_HIGH_RES_MODE_2);
	cout << "Eclairement : " << fixed << setprecision (1) << capteur.obtenirLuminosite_Lux()  << " lx" << endl;
        sleep(1);

    }
    return 0;
}
