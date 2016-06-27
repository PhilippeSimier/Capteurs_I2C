/************************************************************************
  Sujet   : Affichage des valeurs  du thermostat Ds1631
          : Les valeurs sont envoyés sur la sortie standard
          : au format Json
  Autheur : SIMIER Philippe
  Date    : Mai 2016

  Compilation : g++ temperature.cpp Ds1631.cpp -l wiringPi -o temperature
  puis          chmod +s temperature
                mv thermostat /usr/lib/cgi-bin/temperature

*************************************************************************/
#include <iostream>
#include <iomanip>
#include "Ds1631.h"

using namespace std;

int main()
{
   float temperature,tlow,thigh;
   Ds1631 capteur1(0x4F);

   cout << "Content-type: application/json" << endl << endl;
   cout << "{" << endl;

   cout << "\"Ambiante\":\"" << capteur1 << "\"," << endl;

   tlow  = capteur1.getTlow();
   cout << "\"Tl\":\"" << fixed << setprecision (2) << tlow << " C\"," << endl;

   thigh = capteur1.getThigh();
   cout << "\"Th\":\"" << fixed << setprecision (2) << thigh << " C\"" << endl;

   cout << "}" << endl;

   return 0;
}
