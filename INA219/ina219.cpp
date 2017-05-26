/**
  Pour comprendre la calibration du INA219
  sachez que la conversion se fait sur 12 bits (2 exp 12 = 4096)

  L'ADC peut mesurer des tensions comprises entre ± 40mV (± pour la mesure du courant bidirectionnel).
  le PGA est un diviseur de tension programmable par 1, 2, 4, or 8
  Cela donne à l'INA219 une plage effective de ± 40 mV, ± 80 mV, ± 160mV, ou ± 320mV respectivement.
  http://cdwilson.us/articles/understanding-the-INA219

*/
#include "ina219.h"
#include "i2c.h"

using namespace std;

ina219::ina219(int i2cAddress, float  _quantum)  // Le constructeur  calibration 32V 2A
{
  deviceI2C = new i2c(i2cAddress);
  deviceI2C->WriteReg16(REG_CONFIG, 0x0080);   // reset
  deviceI2C->WriteReg16(REG_CALIBRATION , 4096);  // écriture du registre de calibration
  uint16_t config;
  config  = BVOLTAGERANGE_32V | GAIN_8 | BADCRES_12BIT | SADCRES_12BIT_32S | MODE_SANDBVOLT_CONTINUOUS;
  config = ((config & 0x00FF) << 8) | ((config & 0xFF00) >> 8);  // inversion msb lsb

  deviceI2C->WriteReg16(REG_CONFIG, config);
  quantum = _quantum;
}

ina219::~ina219()		//le Destructeur
{
   if (deviceI2C != NULL)
        delete deviceI2C;
}

float ina219::obtenirTension_V(){   // La tension sur le bus d'alimentation en V

    float vb;
    unsigned short data;

    data = deviceI2C->ReadReg16(REG_BUS);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    // printf("%X",data >> 3); à décommenter pour  évaluer le quantum expérimentalement
    vb = (data >> 3) * quantum/1000.0;  // decalage de 3 bits vers la droite 4.0495 mv par bit
    return vb;

}

float ina219::obtenirTensionShunt_mV(){ // la tension aux bornes du shunt 0.01 ohm en mV

    float shuntVoltage;
    short data,vb;

    data = deviceI2C->ReadReg16(REG_SHUNT);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    shuntVoltage = 9.76E-3 * (float)data;   // 9,765625  microV par bit
    return shuntVoltage;
}

float ina219::obtenirCourant_A(){

    short data;
    deviceI2C->WriteReg16(REG_CALIBRATION , 4096);  // écriture du registre de calibration
    data = deviceI2C->ReadReg16(REG_CURRENT);
    return (float)data * 100E-6;   // 100 micro Ampere par bit

}

float ina219::obtenirPuissance_W(){

    short data;

    data = deviceI2C->ReadReg16(REG_POWER);
    return (float)data * 2E-3;     // 2 mW par bit


}

// retourne la version de la classe
void  ina219::version(){

    cout << "\nINA219 PS Touchard Version 1.1\n" << endl;

}
