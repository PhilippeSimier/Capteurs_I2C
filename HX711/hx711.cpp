/**
 *  @file     hx711.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date 4 mars 2018
 *  @brief    Classe pour le composant HX711
*/

#include "hx711.h"

using namespace std;

/**
 * @brief hx711::hx711
 * @details Constructeur de la classe, initialise les attributs
 *          par défaut spi, scale, offset
 */

hx711::hx711(int _scale)
{
    /* Ouverture de spidev0.0 avec le  mode 0 et la vitesse max 1MHz */
    if (spi_open(&spi, "/dev/spidev0.0", 0, 1000000) < 0) {
        std::cout << "spi_open(): " << spi_errmsg(&spi) << std::endl;
        exit(1);
    }
    scale = _scale;
    offset = 0;
}

/**
 * @brief hx711::~hx711
 * @details Destructeur de la classe
 */
hx711::~hx711()
{
    spi_close(&spi);
}


/**
 * @brief hx711::obtenirValeur()
 *
 * @details Permet d'obtenir la valeur brute de la conversion
 */
int hx711::obtenirValeur()
{
	unsigned char byte;
	int valeur = 0;

        unsigned char bufferReception[7];
        unsigned char bufferEmission[7] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x80}; // To change the gain to 64, change the last byte(0x80)

        spi_transfer(&spi, bufferEmission, bufferReception, sizeof(bufferEmission));


	for (int i=0; i<6; i++){
	    for (int j=6; j>=0; j=j-2){
	    	byte = bufferReception[i] & (1<<j);
	    	byte >>= j;
	    	valeur = valeur | byte ;
	    	if ((j>0) | (i<5))
	            valeur = (valeur<<1);
	    }
	}
	if (valeur > 0x7ffff)
	    valeur = valeur | 0xfff00000;

	return valeur;
}

/**
 * @brief hx711::obtenirPoids()
 *
 * @details Permet d'obtenir la valeur du poids en g
 * @return float la valeur du poids
 */


float hx711::obtenirPoids()
{
    int valeurBrute;
    valeurBrute = obtenirValeur();
    return (float)(valeurBrute - offset)/scale;
}

/**
 * @brief hx711::effectuerTarage()
 *
 * @details Permet de mettre à jour la valeur de l'offset
 */

void  hx711::effectuerTarage()
{
    offset = obtenirValeur();
}

