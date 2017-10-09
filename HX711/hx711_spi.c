/*!
    \file     hx711_spi.c
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)

    \brief    Programme pour tester le composant hx711 connecté au bus SPI
    \detail   Connexion Raspberry hx711
	      Raspberry 3.3V (pin 1)  -> VCC
	      Raspberry GND  (pin 20) -> GND
	      Raspberry MISO (pin 21) -> DOUT
	      Raspberry MOSI (pin 19) -> PD_SCK

	      Connexion capteur de pesage -> hx711
	      Excitation+ (E+) ou VCC   fil rouge
	      Excitation- (E-) ou masse fil noir
	      Amplifier+ (A+)  fil blanc
	      Amplifier- (A-)  fil vert

    	      Compilation gcc hx711_spi.c  spi.c  -o hx711

	      L'interface numérique du HX711 est une interface SPI de type propriétaire
              qui utilise une ligne d'horloge (SCK) et de données (DOUT).
              Malheureusement, elle a besoin de 25 impulsions d'horloge,
	      mais le driver SPI peut seulement créer des impusions d'horloge par multiple de 8,
	      pour contourner cette limitation l'astuce conciste à utiliser la ligne de données
	      MOSI du périphérique SPI pour générer les 25 impulsions d'horloge.
              en écrivant la valeur "0xAA", qui donne 4 impulsions par octet,
	      donc nous avons besoin de 6 octets pour obtenir 24 impulsions,
	      puis un octet pour configurer le gain, qui sera (0x80) pour 124,
              0xA8 pour 64 et 0xA0 pour 32!

    \version    1.0 - First release
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "spi.h"

#define SCALE           -414  // parametre de calibration 414 représente un gramme pour un capteur 5 kg

int obtenirValeur(spi_t *spi);

int main(void) {

    spi_t spi;
    int   valeurBrute;
    int   offset;
    float xn, yn, yn_1;
    char  stable;

    /* Ouverture de spidev0.0 avec le  mode 0 et la vitesse max 1MHz */
    if (spi_open(&spi, "/dev/spidev0.0", 0, 1000000) < 0) {
        fprintf(stderr, "spi_open(): %s\n", spi_errmsg(&spi));
        exit(1);
    }

   /* mesure de l'Offset */

	printf("Attente: Tarage\n");

        offset = obtenirValeur(&spi);

	printf("Tare : %d\n", offset);
	printf("Pesage...\n" );
	sleep(1);
	yn = 0.0;
	yn_1 = 0.0;

    while(1)
    {

	valeurBrute = obtenirValeur(&spi);

	// Conversion de la valeur brute en gramme
        xn = (float)(valeurBrute - offset)/SCALE;

        // Filtrage passe bas du premier ordre constante de temps 2.Te  (20ms)
	// poids = 0.33 * capteur.obtenirPoids(3) + 0.66 * poids;   yn = 0,33.xn + 0,66.yn-1
 	// Filtre passe bas du premier ordre constante de temps 10.Te (100ms) // yn = 0,091.xn + 0,91.yn-1
        yn = 0.33 * xn + 0.66 * yn_1;

        if ((yn_1 - yn) < 0.1 && (yn_1 - yn) > - 0.1) stable = '*'; else stable = ' ';
        yn_1 = yn;

	usleep(100000);
	system("clear");
	printf("Poids : %c %.1f g\n", stable, yn);
    }
    spi_close(&spi);
    return 0;
}



int obtenirValeur(spi_t *spi)
{
	unsigned char byte;
	int valeur = 0;
	int i, j;

        unsigned char bufferReception[7];
        unsigned char bufferEmission[7] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x80}; // To change the gain to 64, change the last byte(0x80)

        spi_transfer(spi, bufferEmission, bufferReception, sizeof(bufferEmission));


	for (i=0; i<6; i++){
	    for (j=6; j>=0; j=j-2){
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

