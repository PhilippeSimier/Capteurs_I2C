#include <inttypes.h>

#ifndef _HX711_H_
#define _HX711_H_

//channel A, gain 128
#define GAIN_128 128

//channel A, gain 64
#define GAIN_64 64

//channel B, gain 32
#define GAIN_32 32

class HX711{
private:
	uint8_t gainBits;
	float   scale;
	int32_t offset;

	uint8_t clockPin;
	uint8_t dataPin;

	int32_t lecture();
	void    initialiser(uint8_t _skipSetup);
	int32_t obtenirMoyenne(uint8_t times = 5);
        int32_t obtenirValeur(uint8_t times = 5);
	void    fixerOffset(int32_t _offset);

public:
	HX711(uint8_t _clockPin, uint8_t _dataPin, uint8_t _skipSetup=0);

	bool    isReady();
	void    fixerGain(uint8_t _gain);

	float   obtenirPoids(uint8_t times = 3);
	void    tarer(uint8_t times = 20);
	void    fixerEchelle(float _scale);
	void    powerDown();
	void    powerUp();
	int32_t obtenirOffset();
	float   obtenirEchelle();
};

#endif //_HX711_H_
