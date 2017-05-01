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


class ina219
{

    public:
    // le constructeur
    ina219(int i2cAddress=ADRESSE_I2C_DEFAUT);
    // le destructeur
    ~ina219();
    // Les méthodes pour lire la tension et le courant du bus
    float obtenirTensionEnV();
    float obtenirCourantEnA();
    float obtenirPuissanceEnW();
    float obtenirTensionShuntEnV();
    void  version();
    private:

    i2c *deviceI2C;                   // file descriptor
};

#endif // INA219_H_INCLUDED
