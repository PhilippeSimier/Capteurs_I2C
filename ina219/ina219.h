#ifndef INA219_H_INCLUDED
#define INA219_H_INCLUDED

#include <iostream>
#include <iomanip>
#include "i2c.h"
#include <stdint.h>       // pour les types uint8_t etc
#include <math.h>


#define ADRESSE_I2C_DEFAUT              0x40  // adresse I2C par défaut pour ina219
//Adresse des Registres internes du composant
#define REG_CONFIG      0x00
#define REG_SHUNT       0x01
#define REG_BUS         0x02
#define REG_POWER       0x03
#define REG_CURRENT     0x04
#define REG_CALIBRATION 0x05

    #define BVOLTAGERANGE_MASK        (0x2000)  // Bus Voltage Range Mask
    #define BVOLTAGERANGE_16V         (0x0000)  // 0-16V Range
    #define BVOLTAGERANGE_32V         (0x2000)  // 0-32V Range

    #define GAIN_MASK                 (0x1800)  // Gain Mask
    #define GAIN_1_40MV               (0x0000)  // Gain 1, 40mV Range
    #define GAIN_2_80MV               (0x0800)  // Gain 2, 80mV Range
    #define GAIN_4_160MV              (0x1000)  // Gain 4, 160mV Range
    #define GAIN_8_320MV              (0x1800)  // Gain 8, 320mV Range

    #define BADCRES_MASK              (0x0780)  // Bus ADC Resolution Mask
    #define BADCRES_9BIT              (0x0080)  // 9-bit bus res = 0..511
    #define BADCRES_10BIT             (0x0100)  // 10-bit bus res = 0..1023
    #define BADCRES_11BIT             (0x0200)  // 11-bit bus res = 0..2047
    #define BADCRES_12BIT             (0x0400)  // 12-bit bus res = 0..4095

    #define SADCRES_MASK              (0x0078)  // Shunt ADC Resolution and Averaging Mask
    #define SADCRES_9BIT_1S_84US      (0x0000)  // 1 x 9-bit shunt sample
    #define SADCRES_10BIT_1S_148US    (0x0008)  // 1 x 10-bit shunt sample
    #define SADCRES_11BIT_1S_276US    (0x0010)  // 1 x 11-bit shunt sample
    #define SADCRES_12BIT_1S_532US    (0x0018)  // 1 x 12-bit shunt sample
    #define SADCRES_12BIT_2S_1060US   (0x0048)	// 2 x 12-bit shunt samples averaged together
    #define SADCRES_12BIT_4S_2130US   (0x0050)  // 4 x 12-bit shunt samples averaged together
    #define SADCRES_12BIT_8S_4260US   (0x0058)  // 8 x 12-bit shunt samples averaged together
    #define SADCRES_12BIT_16S_8510US  (0x0060)  // 16 x 12-bit shunt samples averaged together
    #define SADCRES_12BIT_32S_17MS    (0x0068)  // 32 x 12-bit shunt samples averaged together
    #define SADCRES_12BIT_64S_34MS    (0x0070)  // 64 x 12-bit shunt samples averaged together
    #define SADCRES_12BIT_128S_69MS   (0x0078)  // 128 x 12-bit shunt samples averaged together

    #define MODE_MASK                 (0x0007)  // Operating Mode Mask
    #define MODE_POWERDOWN            (0x0000)
    #define MODE_SVOLT_TRIGGERED      (0x0001)
    #define MODE_BVOLT_TRIGGERED      (0x0002)
    #define MODE_SANDBVOLT_TRIGGERED  (0x0003)
    #define MODE_ADCOFF               (0x0004)
    #define MODE_SVOLT_CONTINUOUS     (0x0005)
    #define MODE_BVOLT_CONTINUOUS     (0x0006)
    #define MODE_SANDBVOLT_CONTINUOUS (0x0007)
/*=========================================================================*/


class ina219
{

    public:
    // le constructeur
    ina219(int i2cAddress=ADRESSE_I2C_DEFAUT);
    // le destructeur
    ~ina219();
    // Les méthodes pour lire la tension et le courant du bus
    float obtenirTension_V();
    float obtenirCourant_A();
    float obtenirPuissance_W();
    float obtenirTensionShunt_mV();
    void  version();
    private:

    i2c *deviceI2C;                   // file descriptor
};

#endif // INA219_H_INCLUDED
