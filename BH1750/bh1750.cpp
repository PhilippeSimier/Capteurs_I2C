/**************************************************************************
/*!
    \file     bh1750.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \brief    Classe pour le composant i2c  bh1750

    \version    1.0 - First release
*/

#include "bh1750.h"
#include "i2c.h"


using namespace std;

bh1750::bh1750(int i2cAddress)
{
    deviceI2C = new i2c(i2cAddress);

}

/*!
    @brief  destructor
*/

bh1750::~bh1750()
{
   if (deviceI2C != NULL)
        delete deviceI2C;
}


float bh1750::obtenirLuminosite_Lux()
{
    unsigned short level;
    deviceI2C->Write(0x21); // One-time measurement at 0.5 lx resolution. Measurement Time is typically 120ms. It is automatically set to Power Down mode after measurement.
    sleep(1);
    level = deviceI2C->ReadReg16(0x00);
    level = ((level & 0x00FF) << 8) | ((level & 0xFF00) >> 8); // inversion msb lsb
    // Convert raw value to lux and return
    return (float)level / 1.2;
}
