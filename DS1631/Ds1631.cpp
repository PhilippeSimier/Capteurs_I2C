#include "Ds1631.h"
#include "i2c.h"

using namespace std;


Ds1631::Ds1631(int i2cAddress)  	// Le constructeur
{

    deviceI2C = new i2c(i2cAddress);

    m_config = 8+4+1; 			// conversion sur 12 bits / one shot
    deviceI2C->WriteReg8(0xAC, m_config);
}

float Ds1631::lireRegistre(int code)
{
    short data,msb,lsb;
    float valeur;

    data = deviceI2C->ReadReg16(code);
    msb = (data & 0x00FF) << 8; // valeur entière (en complément à 2)
    lsb = (data & 0xFF00) >> 8; // Partie  fractionnaire de la valeur en 1/256
    data = msb | lsb;
    valeur = (float)data/256;
    return valeur;
}

void Ds1631::ecrireRegistre(char code, float valeur)
{
    short data,msb,lsb;
    data = (short)(valeur * 256);
    msb = (data & 0x00FF) << 8; // permutation de l'octet de poids faible
    lsb = (data & 0xFF00) >> 8; // avec l'octet de poids fort
    data = msb | lsb;
    deviceI2C->WriteReg16(code , data);
}

void Ds1631::stopConvert()
{
     deviceI2C->Write(0x22);       // arret de la conversion
}

void Ds1631::setTlow(float valeur)
{
    ecrireRegistre(0xA2, valeur);
}

void Ds1631::setThigh(float valeur)
{
    ecrireRegistre(0xA1, valeur);
}

float Ds1631::getTemperature()
{
    float valeur;
    int  etat;

    deviceI2C->Write(0x51);      		 // demarrage de la conversion

    do{
        etat = deviceI2C->ReadReg8(0xAC);  // lecture du registre de conf
	etat = etat & 0x80;
	                              // attente de 100ms
    }  while (etat != 0x80);			 // attente du bit Done environ 600 ms


    valeur = lireRegistre(0xAA);

    return valeur;
}

void Ds1631::afficher(ostream &flux)
{
     flux << fixed << setprecision (2) << Ds1631::getTemperature() << " C";
}

float Ds1631::getTlow()
{
    return lireRegistre(0xA2);
}

float Ds1631::getThigh()
{
    return lireRegistre(0xA1);
}

ostream &operator<<( ostream &flux, Ds1631 &thermometre)
{
    thermometre.afficher(flux) ;
    return flux;
}
