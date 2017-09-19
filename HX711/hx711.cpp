#include <stdio.h>
#include <inttypes.h>
#include <wiringPi.h>
#include "hx711.h"

HX711::HX711(uint8_t _clockPin, uint8_t _dataPin, uint8_t _skipSetup) :
	gainBits(1),
	scale(1.0f),
	offset(0),
	clockPin(_clockPin),
	dataPin(_dataPin)
{
	this->initialiser(_skipSetup);
}

void HX711::initialiser(uint8_t _skipSetup){
	if((!_skipSetup) && wiringPiSetup() == -1){
		printf("Erreur à l'initialisation");
	}
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, INPUT);
}

bool HX711::isReady(){
	return digitalRead(dataPin) == LOW;
}

void HX711::fixerGain(uint8_t _gain){
	switch(_gain){
		case GAIN_128:
			this->gainBits = 1;
		break;
		case GAIN_64:
			this->gainBits = 3;
		break;
		case GAIN_32:
			this->gainBits = 2;
		break;
		default:
			// gain invalide, on ignore
		break;
	}

	digitalWrite(clockPin, LOW);
	lecture();
}

int32_t HX711::lecture() {
	// attend que la puce soit prête
	while (!this->isReady());

	int32_t data = 0;
	// Envoie 24 impulsions sur la sortie clock pour lire les données
	for(uint8_t i = 24; i--;){
		digitalWrite(clockPin, HIGH);

		digitalRead(dataPin);
		data |= (digitalRead(dataPin) << i);

		digitalWrite(clockPin, LOW);
	}

	// fixe le canal et le facteur de gain pour la prochaine lecture
	// en applicant des impulsions sur la sortie clock

	for (int i = 0; i < gainBits; i++) {
		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}
	if(data & 0x800000){
		data |= (long) ~0xffffff;
	}

	return data;
}

int32_t HX711::obtenirMoyenne(uint8_t times) {
        int32_t val;
	val = lecture();
	int32_t max = val;
        int32_t min = val;
	int64_t sum = val;

	for (uint8_t i = 1; i < times; i++) {
	    val = lecture();
	    sum += val;
	    if (val > max) max = val;
	    if (val < min) min = val;
	}
	return (sum-max-min) / (times-2);
}

// retourne la valeur brute du convertisseur en tenant compte de la tare
int32_t HX711::obtenirValeur(uint8_t times) {
	return obtenirMoyenne(times) - offset;
}

// retourne la valeur du poids (fonction de la valeur scale)
float HX711::obtenirPoids(uint8_t times) {
	float val;
	return val =  obtenirValeur(times) / scale;
}

void HX711::tarer(uint8_t times) {
	uint64_t sum = obtenirMoyenne(times);
	fixerOffset(sum);
}

void HX711::fixerEchelle(float _scale) {
	scale = _scale;
}

void HX711::fixerOffset(int32_t _offset) {
	offset = _offset;
}

void HX711::powerDown() {
	digitalWrite(clockPin, LOW);
	digitalWrite(clockPin, HIGH);
}

void HX711::powerUp() {
	digitalWrite(clockPin, LOW);
}

int32_t HX711::obtenirOffset(){
	return this->offset;
}

float HX711::obtenirEchelle(){
	return this->scale;
}

