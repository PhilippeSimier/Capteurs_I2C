/**
  Pour comprendre la calibration du INA219
  sachez que la conversion se fait sur 12 bits (2 exp 12 = 4096)
  http://cdwilson.us/articles/understanding-the-INA219

*/
#include "ina219.h"
#include "i2c.h"

using namespace std;

ina219::ina219(int i2cAddress)  // Le constructeur  calibration 32V 2A
{
  deviceI2C = new i2c(i2cAddress);
  deviceI2C->WriteReg16(REG_CONFIG, 0x399F);  // reset = 0x399F
  deviceI2C->WriteReg16(REG_CALIBRATION , 4096);  // écriture du registre de calibration
  uint16_t config;
  config  = BVOLTAGERANGE_32V | GAIN_8_320MV | BADCRES_12BIT | SADCRES_12BIT_1S_532US | MODE_SANDBVOLT_CONTINUOUS;
  deviceI2C->WriteReg16(REG_CONFIG, config);
}

ina219::~ina219()		//le Destructeur
{
   if (deviceI2C != NULL)
        delete deviceI2C;
}

float ina219::obtenirTension_V(){   // La tension sur le bus d'alimentation en V

    float busVoltage;
    short data,vb;

    data = deviceI2C->ReadReg16(REG_BUS);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    vb = (data >> 3) * 4;  // decalage de 3 bits vers la droite mv par 3.90 bit
    busVoltage = 0.001 * (float)vb; // conversion des mV en V
    return busVoltage;

}

float ina219::obtenirTensionShunt_mV(){ // la tension aux bornes du shunt 0.01 ohm en mV

    float shuntVoltage;
    short data,vb;

    data = deviceI2C->ReadReg16(REG_SHUNT);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    shuntVoltage = 9.7E-3 * (float)data;   // 9,765625  microV par bit
    return shuntVoltage;
}

float ina219::obtenirCourant_A(){

    short data;
    deviceI2C->WriteReg16(REG_CALIBRATION , 4096);  // écriture du registre de calibration
    data = deviceI2C->ReadReg16(REG_CURRENT);
    //data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    //printf("%X\n", data);
    return (float)data * 100E-6;   // 100 micro Ampere par bit

}

float ina219::obtenirPuissance_W(){

    short data;

    data = deviceI2C->ReadReg16(REG_POWER);
    //data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    return (float)data * 2E-3;     // 2 mW par bit


}

// retourne la version de la classe
void  ina219::version(){

    cout << "\nINA219 PS Touchard Version 1.1\n" << endl;

}
