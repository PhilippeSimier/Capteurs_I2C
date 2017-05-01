#include "ina219.h"
#include "i2c.h"

using namespace std;

ina219::ina219(int i2cAddress)  // Le constructeur
{
  deviceI2C = new i2c(i2cAddress);

}

ina219::~ina219()		//le Destructeur
{
   if (deviceI2C != NULL)
        delete deviceI2C;
}

float ina219::obtenirTensionEnV(){   // La tension sur le bus d'alimentation en V

    float busVoltage;
    short data,vb;

    data = deviceI2C->ReadReg16(REG_BUS);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    vb = (data >> 3) * 4;  // decalage de 3 bits vers la droite 4mv par bit
    busVoltage = 0.001 * (float)vb; // conversion des mV en V
    return busVoltage;

}

float ina219::obtenirTensionShuntEnV(){ // la tension aux bornes du shunt 0.01 ohm

    float shuntVoltage;
    short data,vb;

    data = deviceI2C->ReadReg16(REG_SHUNT);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    shuntVoltage = 0.00001 * (float)data;
    return shuntVoltage;
}

float ina219::obtenirCourantEnA(){

    short data;

    data = deviceI2C->ReadReg16(REG_CURRENT);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    return (float)data;

}

float ina219::obtenirPuissanceEnW(){

    short data;

    data = deviceI2C->ReadReg16(REG_POWER);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    return (float)data;


}

// retourne la version de la classe
void  ina219::version(){

    cout << "\nINA219 PS Touchard Version 1.1\n" << endl;

}
