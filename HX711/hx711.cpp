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
	this->initialize(_skipSetup);
}

void HX711::initialize(uint8_t _skipSetup){
	if((!_skipSetup) && wiringPiSetup() == -1){
		printf("initialization failed");
	}
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, INPUT);
}

bool HX711::isReady(){
	return digitalRead(dataPin) == LOW;
}

void HX711::setGain(uint8_t _gain){
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
			//invalid gain, ignore
		break;
	}

	digitalWrite(clockPin, LOW);
	read();
}

int32_t HX711::read() {
	// wait for the chip to become ready
	while (!this->isReady());

	int32_t data = 0;
	// pulse the clock pin 24 times to read the data
	for(uint8_t i = 24; i--;){
		digitalWrite(clockPin, HIGH);

		digitalRead(dataPin);
		data |= (digitalRead(dataPin) << i);

		digitalWrite(clockPin, LOW);
	}

	// set the channel and the gain factor for the next reading using the clock pin
	for (int i = 0; i < gainBits; i++) {
		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}

	if(data & 0x800000){
		data |= (long) ~0xffffff;
	}

	return data;
}

int32_t HX711::readAverage(uint8_t times) {
	int64_t sum = 0;
	for (uint8_t i = 0; i < times; i++) {
		sum += read();
	}
	return sum / times;
}

int32_t HX711::getRawValue(uint8_t times) {
	return readAverage(times) - offset;
}

float HX711::getUnits(uint8_t times) {
	return getRawValue(times) / scale;
}

void HX711::tare(uint8_t times) {
	uint64_t sum = readAverage(times);
	setOffset(sum);
}

void HX711::setScale(float _scale) {
	scale = _scale;
}

void HX711::setOffset(int32_t _offset) {
	offset = _offset;
}

void HX711::powerDown() {
	digitalWrite(clockPin, LOW);
	digitalWrite(clockPin, HIGH);
}

void HX711::powerUp() {
	digitalWrite(clockPin, LOW);
}

int32_t HX711::getOffset(){
	return this->offset;
}

float HX711::getScale(){
	return this->scale;
}

