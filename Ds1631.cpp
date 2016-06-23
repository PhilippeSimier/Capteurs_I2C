#include "Ds1631.h"

using namespace std;


Ds1631::Ds1631(int i2cAddress)  	// Le constructeur
{
    m_fd = wiringPiI2CSetup(i2cAddress);

    m_config = 8+4+1; 			// conversion sur 12 bits / one shot
    wiringPiI2CWriteReg8(m_fd, 0xAC, m_config);
}

float Ds1631::lireRegistre(char code)
{
    short data,msb,lsb;
    float valeur;

    data = wiringPiI2CReadReg16(m_fd, code);
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
    wiringPiI2CWriteReg16(m_fd,code , data);
}

void Ds1631::stopConvert()
{
     wiringPiI2CWrite(m_fd, 0x22);       // arret de la conversion
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

    wiringPiI2CWrite(m_fd, 0x51);      		 // demarrage de la conversion

    do{
        etat = wiringPiI2CReadReg8(m_fd, 0xAC);  // lecture du registre de conf
	etat = etat & 0x80;
	delay(100);                              // attente de 100ms
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
