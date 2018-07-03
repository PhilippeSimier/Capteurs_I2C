/**
 *  @file     scaleCGI.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     02 juillet 2018
 *  @brief    programme pour déterminer l'échelle via API HTTP
 *            ce programme détermine la constante scale et
 *            l'enregistre dans le fichier configuration.ini
 *            compilation: g++ scaleCGI.cpp hx711.cpp SimpleIni.cpp  spi.c -o scaleCGI
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "hx711.h"
#include "SimpleIni.h"


using namespace std;

int main()
{

    hx711 balance;
    SimpleIni ini;
    int gain, offset;
    string key;
    float poids = 0.0;
    float scale = 1.0;


    cout << "Content-type: application/json" << endl << endl;
    cout << "{" << endl;

    if(!ini.Load("/home/pi/Capteurs_I2C/HX711/configuration.ini"))
    {
        cout << "\"success\": false, " << endl;
        cout << "\"error\":\"Impossible d'ouvrir le fichier configuration.ini\"" << endl;
	cout << "}" << endl;
        return -1;
    }

    gain   = ini.GetValue<int>("balance", "gain", 128);
    balance.configurerGain(gain);
    offset = ini.GetValue<int>("balance", "offset", 0);
    balance.fixerOffset(offset);

    // lecture de la masse connue (methode POST)

    getline(cin, key, '=');
    cin >> poids;
    cout << "\"poids\":" << poids << "," << endl;
    if (poids <= 0.0){
        cout << "\"success\": false, " << endl;
        cout << "\"error\":\"Le poids doit être supérieur à zéro\"" << endl;
        cout << "}" << endl;
        return -1;
    }

    int x, max, min, som;
    som = balance.obtenirValeur();
    max = som;
    min = som;
    for(int i=1 ; i<10 ; i++)
    {
        x = balance.obtenirValeur();
        som += x;
        if (x > max) max = x;
        if (x < min) min = x;

    }
    x = (som - max - min)/8 ;
    scale = (float)(x - offset)/poids;

    ini.SetValue<float>("balance", "scale", scale);

    // Ecriture du fichier de configuration
    if(!ini.SaveAs("/home/pi/Capteurs_I2C/HX711/configuration.ini"))
    {
        cout << "\"success\": false, " << endl;
        cout << "\"error\":\"Erreur d'écriture du fichier de configuration\"" << endl;
        cout << "}" << endl;
        return -1;
    }
    else
    {
        cout << "\"scale\":" << scale << "," << endl;
        cout << "\"success\": true " << endl;
        cout << "}" << endl;
        return 0;

    }
}

