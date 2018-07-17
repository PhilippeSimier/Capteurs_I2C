/*!
    @file     thingSpeak.cpp
    @author   Philippe SIMIER (Touchard Wahington le Mans)
    @license  BSD (see license.txt)
    @brief    Programme pour logger le poids -> thingSpeak
    @date     Juin 2018
    @version  v1.0 - First release
    @detail   Prérequis    : apt-get update
                             apt-get install libcurl4-openssl-dev
              Compilation  : g++  thingSpeak.cpp HTTPDownloader.cpp SimpleIni.cpp hx711.cpp spi.c  -lcurl -o thingSpeak
              Execution    : ./main
*/



#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "hx711.h"
#include "SimpleIni.h"
#include "HTTPDownloader.h"

using namespace std;

int main()
{
    hx711 balance;
    SimpleIni ini;
    HTTPDownloader downloader;
    ostringstream url;

    // Lecture du fichier de configuration
    if(!ini.Load("/home/pi/Capteurs_I2C/HX711/configuration.ini"))
    {
        cout << "\"error\":\"Impossible d'ouvrir le fichier configuration.ini\"" << endl;
        return -1;
    }

    // Configuration de la balance
    balance.fixerEchelle( ini.GetValue<float>("balance", "scale", 1.0 ));
    balance.fixerOffset( ini.GetValue<int>("balance", "offset", 0));
    balance.configurerGain(  ini.GetValue<int>("balance", "gain", 128));

    string key = ini.GetValue<string>("thingSpeak", "key", " ");
    url << "https://api.thingspeak.com/update?api_key=" << key << "&field1=" << balance.obtenirPoids();
    cout << url.str() << endl;

    string contenu = downloader.obtenirUrl(url.str());
    cout << contenu << endl;

    return 0;
}
