/**************************************************************************
/*!
    \file     bh1750.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \brief    Classe pour le composant i2c  bh1750 capteur d'éclairement
    \detail   Le lux est une unité de mesure de l'éclairement lumineux (symbole : lx). 
              Il caractérise le flux lumineux reçu par unité de surface
    \version    1.0 - First release
*/

#include "bh1750.h"
#include "i2c.h"

using namespace std;

/*!
    @brief  constructor
*/

bh1750::bh1750(int i2cAddress)
{
    deviceI2C = new i2c(i2cAddress);
    resolution = 1.0;

}

/*!
    @brief  destructor
*/

bh1750::~bh1750()
{
   if (deviceI2C != NULL)
        delete deviceI2C;
}

/*!
    @brief  Methode pour obtenir la valeur de l'éclairement en lx
    @return retourne un float (valeur de l'éclairement en lux)
*/

float bh1750::obtenirLuminosite_Lux()
{
    unsigned short level;
    level = deviceI2C->ReadReg16(0x00);
    level = ((level & 0x00FF) << 8) | ((level & 0xFF00) >> 8); // inversion msb lsb
    // Convert raw value to lux and return
    if (resolution == 1.0){
    	return (float)level / 1.2;
    }
    else{
	return (float)level * resolution / 1.2 ;
    }
}

/*!
    @brief  Methode pour configuer le mode de fct
*/

void bh1750::activer(void)
{
    deviceI2C->Write(BH1750_POWER_ON);
}

void bh1750::desactiver(void)
{
    deviceI2C->Write(BH1750_POWER_DOWN);
}

void bh1750::reset(void)
{
    deviceI2C->Write( BH1750_RESET);
}

void bh1750::configurer(int mode)
{
    switch (mode)
    {
        case BH1750_CONTINUOUS_HIGH_RES_MODE:
        case BH1750_CONTINUOUS_LOW_RES_MODE:
        case BH1750_ONE_TIME_HIGH_RES_MODE:
        case BH1750_ONE_TIME_LOW_RES_MODE:
            // apply mode 1 res 1 lx
            deviceI2C->Write(mode);
            resolution = 1.0;
            deviceI2C->delay_ms(180);
            break;

        case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
        case BH1750_ONE_TIME_HIGH_RES_MODE_2:
            // apply mode 2 res 0.5 lx
            deviceI2C->Write(mode);
            resolution = 0.5;
            deviceI2C->delay_ms(180);
            break;

        default:
            // Invalid measurement mode
            printf("Invalid measurement mode !\n");
            break;
    }
}
