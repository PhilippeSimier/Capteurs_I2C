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

bh1750::obtenirLuminosite_Lux()
{

}
