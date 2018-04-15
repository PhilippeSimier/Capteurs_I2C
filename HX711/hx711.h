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
    void  effectuerTarage();

private:

    spi_t spi;
    int   valeurBrute;
    int   offset;
    int   scale;
    int obtenirValeur();


};

#endif // HX711_H_INCLUDED
