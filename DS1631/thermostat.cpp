/************************************************************************
  Sujet   : Réglage du thermostat du Ds1631
          : Les valeurs sont reçues sur l'entree standard
          : Via un formulaire par la  methode POST
  Autheur : SIMIER Philippe
  Date    : Mai 2016

  Compilation : g++ thermostat.cpp Ds1631.cpp -l wiringPI -o thermostat
  puis          chmod +s thermostat
                mv thermostat /usr/lib/cgi-bin/thermostat

*************************************************************************/

#include<cstdlib>
#include <iostream>
using namespace std;

#include "Ds1631.h"

int main(void)
{
	float tHigh = 0;
	float tLow = 0;
	char *lenstr;
	char ch_formulaire[100];
	long len;
	int erreur;
        Ds1631 capteur1(0x4F);

	lenstr = getenv("CONTENT_LENGTH");
	if (lenstr == NULL || sscanf(lenstr,"%ld",&len)!=1){
		cout << "Content-type:text/plain\n\n";
		cout << "Erreur de traitement du formulaire\n";
	}
	else {

		fgets(ch_formulaire, len +1, stdin);

		erreur = sscanf(ch_formulaire,"Tl=%f&Th=%f&envoyer=reglage", &tLow, &tHigh);
		capteur1.setTlow(tLow);
		capteur1.setThigh(tHigh);

		cout << "Content-type: text/html; charset=utf-8\n";
		cout << "Location: /gpio/temperature2.html\n\n";

		return 0;
	}
}
