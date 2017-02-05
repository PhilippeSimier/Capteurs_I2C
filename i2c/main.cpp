/*************************************************************************
*    test de la classe i2C avec un composant DS1620
*    Affiche la température en °C
*    g++ main.cpp i2c.cpp -o test
*************************************************************************/


#include <iostream>
#include "i2c.h"

using namespace std;

int main()
{
    i2c Ds1620(0x4F);  // création d'un objet DS1620 à l'adresse 4F
    int tab[32]={0};
    int val, i;

    short valeur, data;
    char etat;

    Ds1620.Write(0x51);  // demarrage de la conversion
    do{
	etat = Ds1620.ReadReg8(0xAC) & 0x80;
    } while (etat != 0x80);  // attente fin de conversion

    valeur = Ds1620.ReadReg16(0xAA);
    data = ((valeur & 0x00FF) << 8) | ((valeur & 0xFF00) >> 8);  // permutation des octets
    cout << (float)data/256 << endl;   // affichage de la temperature

    val = Ds1620.ReadBlockData (0xAA, 4, tab);  // test de la lecture d'un bloc de donnée
    cout << val << endl;    // affiche le nombre de donnée lue
    if (val !=0){
	for(i = 0; i< val; i++){
	   cout << " " << tab[i];
	}
    cout << endl;
    }
    return 0;
}
