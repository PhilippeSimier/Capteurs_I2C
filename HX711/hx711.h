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
	float scale;
	int32_t offset;

	uint8_t clockPin;
	uint8_t dataPin;

public:
	HX711(uint8_t _clockPin, uint8_t _dataPin, uint8_t _skipSetup);
	void initialize(uint8_t _skipSetup);
	bool isReady();
	void setGain(uint8_t _gain);
	int32_t read();
	int32_t readAverage(uint8_t times = 5);
	int32_t getRawValue(uint8_t times = 5);
	float getUnits(uint8_t times = 3);
	void tare(uint8_t times = 20);
	void setScale(float _scale);
	void setOffset(int32_t _offset);
	void powerDown();
	void powerUp();
	int32_t getOffset();
	float getScale();
};

#endif //_HX711_H_
