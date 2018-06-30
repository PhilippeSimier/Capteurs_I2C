/**
 *  @file     hx711.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     6 juin 2018
 *  @brief    Classe pour le composant HX711
*/

#include "hx711.h"

using namespace std;

/**
 * @brief hx711::hx711
 * @details Constructeur de la classe, initialise les attributs
 *          par défaut spi, scale, offset
 */

hx711::hx711(float _scale)
{
    /* Ouverture de spidev0.0 avec le  mode 0 et la vitesse max 1MHz */
    if (spi_open(&spi, "/dev/spidev0.0", 0, 1000000) < 0) {
        std::cout << "spi_open(): " << spi_errmsg(&spi) << std::endl;
        exit(1);
    }
    scale = _scale;
    offset = 0;
    bufferEmission[0] = 0xaa;
    bufferEmission[1] = 0xaa;
    bufferEmission[2] = 0xaa;
    bufferEmission[3] = 0xaa;
    bufferEmission[4] = 0xaa;
    bufferEmission[5] = 0xaa;
    bufferEmission[6] = 0xa8;   // 0xa8 gain = 64  0x80 gain = 128
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

        usleep(110000); // attente fin de conversion
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
	else
	    valeur = valeur & 0x007ffff;
	//cout << valeur << endl; a décommenter en mode debug
	return valeur;
}

/**
 * @brief hx711::obtenirPoids()
 *
 * @details Permet d'obtenir la valeur du poids en unité de mesure
 * @return float la valeur du poids
 */


float hx711::obtenirPoids(int nb)
{
    int max = obtenirValeur();
    int min = max;
    int som = 0;
    for (int i=0; i < nb; i++)
    {
        valeurBrute = obtenirValeur();
        if (valeurBrute > max) max = valeurBrute;
        if (valeurBrute < min) min = valeurBrute;
        som += valeurBrute;
    }
    valeurBrute = (som - max - min) / (nb-2);
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

/**
 * @brief hx711::fixerEchelle()
 *
 * @details Permet de configurer l'échelle de mesure
 */

void hx711::fixerEchelle(float _scale)
{
    scale = _scale;
}


/**
 * @brief hx711::fixerOffset()
 *
 * @details Permet de configurer l'offset
 * Cette valeur est obtenue après tarage de la balance
 */

void hx711::fixerOffset(int _offset)
{
	offset = _offset;
}



/**
 * @brief hx711::fixerOffset()
 *
 * @details Permet d'obtenir la valeur de l'offset
 * Cette valeur est obtenue après tarage de la balance
 */

int hx711::obtenirOffset()
{
	return offset;
}


/**
 * @brief hx711::configurerGain()
 *
 * @details Permet de configurer la valeur du gain de l'amplificateur
 * pour le canal A deux valeurs possibles 128 ou 64
 */

void hx711::configurerGain(char gain)
{
    switch(gain){
	case 128:
	    bufferEmission[6] = 0x80; // 25 impulsions
            break;
        case 64:
	    bufferEmission[6] = 0xa8; // 27 impulsions
            break;
        default:
            bufferEmission[6] = 0xa8; // 27 impulsions

    }
}
