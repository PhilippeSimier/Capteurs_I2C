#ifndef BM280_H_INCLUDED
#define BM280_H_INCLUDED

#include <iostream>
#include <iomanip>
#include "wiringPiI2C.h"
#include <stdint.h>       // pour les types uint8_t etc
#include <math.h>

#define ADRESSE_I2C_DEFAUT              0x77
//Register names:

#define BME280_REGISTER_DIG_T1        0x88
#define BME280_REGISTER_DIG_T2        0x8A
#define BME280_REGISTER_DIG_T3        0x8C
#define BME280_REGISTER_DIG_P1        0x8E
#define BME280_REGISTER_DIG_P2        0x90
#define BME280_REGISTER_DIG_P3        0x92
#define BME280_REGISTER_DIG_P4        0x94
#define BME280_REGISTER_DIG_P5        0x96
#define BME280_REGISTER_DIG_P6        0x98
#define BME280_REGISTER_DIG_P7        0x9A
#define BME280_REGISTER_DIG_P8        0x9C
#define BME280_REGISTER_DIG_P9        0x9E
#define BME280_REGISTER_DIG_H1        0xA1
#define BME280_REGISTER_DIG_H2        0xE1
#define BME280_REGISTER_DIG_H3        0xE3
#define BME280_REGISTER_DIG_H4        0xE4
#define BME280_REGISTER_DIG_H5        0xE5
#define BME280_REGISTER_DIG_H6        0xE7
#define BME280_REGISTER_CHIPID        0xD0
#define BME280_REGISTER_VERSION       0xD1
#define BME280_REGISTER_SOFTRESET     0xE0
#define BME280_RESET                  0xB6
#define BME280_REGISTER_CAL26         0xE1
#define BME280_REGISTER_CONTROLHUMID  0xF2
#define BME280_REGISTER_CONTROL       0xF4
#define BME280_REGISTER_CONFIG        0xF5
#define BME280_REGISTER_PRESSUREDATA  0xF7
#define BME280_REGISTER_TEMPDATA      0xFA
#define BME280_REGISTER_HUMIDDATA     0xFD

#define MEAN_SEA_LEVEL_PRESSURE         1013


//  les registres des données pour la pression température et humidité

typedef struct
{
  uint8_t pmsb;
  uint8_t plsb;
  uint8_t pxsb;

  uint8_t tmsb;
  uint8_t tlsb;
  uint8_t txsb;

  uint8_t hmsb;
  uint8_t hlsb;

  uint32_t temperature;
  uint32_t pressure;
  uint32_t humidity;

} bme280_raw_data;


// structure pour enregistrer les constantes  de calibration
typedef struct
{
  uint16_t dig_T1;
  int16_t  dig_T2;
  int16_t  dig_T3;

  uint16_t dig_P1;
  int16_t  dig_P2;
  int16_t  dig_P3;
  int16_t  dig_P4;
  int16_t  dig_P5;
  int16_t  dig_P6;
  int16_t  dig_P7;
  int16_t  dig_P8;
  int16_t  dig_P9;

  uint8_t  dig_H1;
  int16_t  dig_H2;
  uint8_t  dig_H3;
  int16_t  dig_H4;
  int16_t  dig_H5;
  int8_t   dig_H6;
} bme280_calib_data;


class bm280
{

public:
    // le constructeur
    bm280(int i2cAddress=ADRESSE_I2C_DEFAUT);

    // méthodes pour lire la température le pression et l'humidité

    int32_t getTemperatureCalibration();
    float obtenirTemperatureEnC();
    float obtenirTemperatureEnF();
    float obtenirPression();
    float obtenirHumidite();

    // methode pour obtnir l'altitude en métre
    float obtenirAltitudeEnMetres();
    float obtenirAltitudeEnPieds();


private:


    int fd;                          // file descriptor
    bme280_calib_data cal;           // calibration
    bme280_raw_data raw;             // les registres
    void readCalibrationData();
    void getRawData();
};

#endif // BM280_H_INCLUDED
