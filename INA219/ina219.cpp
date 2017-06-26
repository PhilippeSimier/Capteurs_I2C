/**************************************************************************
/*!
    \file     ina219.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)

    \brief    Classe pour le composant i2c  INA219
    \detail   Pour comprendre la calibration du INA219
    	la conversion se fait sur 12 bits (2 exp 12 = 4096)

    	L'ADC peut mesurer des tensions comprises entre ± 40mV (± pour la mesure du courant bidirectionnel).
    	le PGA est un diviseur de tension programmable par 1, 2, 4, or 8
    	Cela donne à l'INA219 une plage effective de ± 40 mV, ± 80 mV, ± 160mV, ou ± 320mV respectivement.
    	http://cdwilson.us/articles/understanding-the-INA219

    \version    1.0 - First release

*/
#include "ina219.h"
#include "i2c.h"

using namespace std;

/*!
    @brief  Instantiates a new INA219 class
            and Configures to INA219 to be able to measure up to 32V and 3.2A
            of current.  Each unit of current corresponds to 100uA, and
            each unit of power corresponds to 2mW. Counter overflow
            occurs at 3.2A.

    @note   These calculations assume a 0.1 ohm resistor is present
*/

ina219::ina219(int i2cAddress, float  _quantum)
{
    deviceI2C = new i2c(i2cAddress);
    deviceI2C->WriteReg16(REG_CONFIG, 0x0080);   // reset

    short rc = 4096;
    rc = ((rc & 0x00FF) << 8) | ((rc & 0xFF00) >> 8);
    deviceI2C->WriteReg16(REG_CALIBRATION , rc);  // écriture du registre de calibration

    uint16_t config;
    config  = BVOLTAGERANGE_32V | GAIN_8 | BADCRES_12BIT | SADCRES_12BIT_128S | MODE_SANDBVOLT_CONTINUOUS;
    config = ((config & 0x00FF) << 8) | ((config & 0xFF00) >> 8);  // inversion msb lsb
    deviceI2C->WriteReg16(REG_CONFIG, config);

    quantum = _quantum;
}
/*!
    @brief  destructor

*/

ina219::~ina219()
{
   if (deviceI2C != NULL)
        delete deviceI2C;
}

/*!
    @brief  Set calibration at 16V
*/

void ina219::fixerCalibration_16V(){

    uint16_t config;
    config  = BVOLTAGERANGE_16V | GAIN_8 | BADCRES_12BIT | SADCRES_12BIT_128S | MODE_SANDBVOLT_CONTINUOUS;
    config = ((config & 0x00FF) << 8) | ((config & 0xFF00) >> 8);  // inversion msb lsb
    deviceI2C->WriteReg16(REG_CONFIG, config);


}

/*!
    @brief  Gets the raw bus voltage (float)
*/

float ina219::obtenirTension_V(){

    float vb;
    unsigned short data;

    data = deviceI2C->ReadReg16(REG_BUS);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    // printf("%X",data >> 3); à décommenter pour  évaluer le quantum expérimentalement
    vb = (data >> 3) * quantum/1000.0;  // decalage de 3 bits vers la droite 4.0495 mv par bit
    return vb;

}

/*!
    @brief  Gets the shunt voltage in mili volts
*/

float ina219::obtenirTensionShunt_mV(){ // la tension aux bornes du shunt 0.01 ohm en mV

    float shuntVoltage;
    short data,vb;

    data = deviceI2C->ReadReg16(REG_SHUNT);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    shuntVoltage = 9.76E-3 * (float)data;   // 9,765625  microV par bit
    return shuntVoltage;
}

/*!
    @brief  Gets the current value in Ampere (float)
*/

float ina219::obtenirCourant_A(){

    short data;
    short rc = 4096;
    rc = ((rc & 0x00FF) << 8) | ((rc & 0xFF00) >> 8);
    deviceI2C->WriteReg16(REG_CALIBRATION , rc);  // écriture du registre de calibration
    data = deviceI2C->ReadReg16(REG_CURRENT);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    return (float)data * 100E-6;   // 100 micro Ampere par bit

}

/*!
    @brief  Gets the current power in Watt (float)
*/


float ina219::obtenirPuissance_W(){

    short data;

    data = deviceI2C->ReadReg16(REG_POWER);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    return (float)data * 2E-3;     // 2 mW par bit


}


/*!
    @brief  Gets the current version of the class
*/

void  ina219::version(){

    cout << "\nINA219 PS Touchard Version 1.0\n" << endl;

}
