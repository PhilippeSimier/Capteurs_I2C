/**************************************************************************
/*!
    \file     main.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \brief    programme pour tester la classe i2c
    \detail   test de la classe i2C avec un composant DS1631
	      Affiche la température en °C
    \compilation    g++ main.cpp i2c.cpp -o main

    \version  v1.0 - First release
*/



#include <iostream>
#include "i2c.h"

using namespace std;

int main()
{
    i2c Ds1631(0x4F, 1);  // création d'un objet DS1631 à l'adresse 4F sur le bus 1
    int tab[32]={0};
    int val, i;

    short valeur, data;
    char etat;
    if (!Ds1631.getError()){
    	Ds1631.Write(0x51);  // demarrage de la conversion
    	do{
	    etat = Ds1631.ReadReg8(0xAC) & 0x80;
        } while (etat != 0x80);  // attente fin de conversion

    	valeur = Ds1631.ReadReg16(0xAA);
    	data = ((valeur & 0x00FF) << 8) | ((valeur & 0xFF00) >> 8);  // permutation des octets
    	cout << (float)data/256 << endl;   // affichage de la temperature

    	val = Ds1631.ReadBlockData (0xAA, 4, tab);  // test de la lecture d'un bloc de donnée
    	cout << val << endl;    // affiche le nombre de donnée lue
    	if (val !=0){
	    for(i = 0; i< val; i++){
	    	cout << " " << tab[i];
	    }
    	cout << endl;
    	}
    }
    else{
	cout << "le capteur DS1631 n'est pas présent sur le bus !" << endl;
    }
    return 0;
}
