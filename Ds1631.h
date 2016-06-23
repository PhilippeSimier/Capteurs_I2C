#ifndef DEF_DS1631
#define DEF_DS1631

#include <iostream>
#include <iomanip>
#include "wiringPi.h"
#include "wiringPiI2C.h"


class Ds1631
{
    public:

    Ds1631(int i2cAddress=0x48);
    float getTemperature();			   // Donne la temperature en °C
    void  afficher(std::ostream &flux);            // Methode pour afficher la temperature en °C
    float getThigh();				   // donne le seuil haut du thermostat
    float getTlow();    			   // donne le seuil bas du thermostat
    void  setTlow(float valeur);		   // fixe le seuil bas du thermostat
    void  setThigh(float valeur);		   // fixe le seuil haut du thermostat
    void  stopConvert();			   // stop la conversion de temperature

    private:

    int m_adresse;                                  // adresse i2c du 1631
    int m_fd;                                       // file descriptor
    int m_config;                                   // la valeur du registre de configuration

    float lireRegistre(char code);                  // fonction pour lire un registre
    void  ecrireRegistre(char code, float valeur);  // fonction pour écrire un registre
};

// surcharge de l'opérateur << pour afficher la température en °C
std::ostream &operator<<(std::ostream &flux, Ds1631 &thermometre);

#endif
