#ifndef HX711_H_INCLUDED
#define HX711_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "spi.h"

class hx711
{

public:

    // le constructeur
    hx711(int scale = -414);
    // le destructeur
    ~hx711();
    // Méthode pour obtenir la valeur du poids
    float obtenirPoids();
    // Méthode pour effectuer le tarage
    void  effectuerTarage();
    // Méthode pour obtenir la valeur brute
    int   obtenirValeur();
    // Méthode pour fixer l'échelle de mesure (nb de points par unité de mesure)
    void fixerEchelle(int _scale);
    // Méthode pour fixer l'offset (décalage d'origine)
    void fixerOffset(int _offset);
    // Méthode pour obtenir l'offset
    int obtenirOffset();


private:

    spi_t spi;
    int   valeurBrute;
    int   offset;
    int   scale;

};

#endif // HX711_H_INCLUDED
