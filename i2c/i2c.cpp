/***************************************************************************
*   Class i2c pour le raspberry pi
*   I2C (pronounce: I squared C) is a protocol developed by Philips. It is a 
*   slow two-wire protocol (variable speed, up to 400 kHz), with a high speed
*   extension (3.4 MHz).  It provides an inexpensive bus for connecting many
*   types of devices with infrequent or low bandwidth communications needs.
*   I2C is widely used with embedded systems.
***************************************************************************/
#include "i2c.h"

    // Le constructeur
    i2c::i2c(int adresseI2C, int idBusI2C){
        char filename[20];
        snprintf(filename, 19, "/dev/i2c-%d", idBusI2C);
        if ((fd = open (filename, O_RDWR)) < 0){
            cout << "Erreur d'ouverture du bus I2C" << endl;
            exit(1);
        }
        //  Change slave address. The address is passed in the
        //  7 lower bits of the  argument
        if (ioctl (fd, I2C_SLAVE, adresseI2C) < 0){
            cout << "Impossible de sélectionner l'adresse I2C" << endl ;
            exit(1);
        }
    }

    int i2c::i2c_smbus_access (char rw, uint8_t command, int size, union i2c_smbus_data *data)
    {
        struct i2c_smbus_ioctl_data args ;

        args.read_write = rw ;
        args.command    = command ;
        args.size       = size ;
        args.data       = data ;
        return ioctl (fd, I2C_SMBUS, &args) ;
    }


    unsigned char i2c::Read(){
        union i2c_smbus_data data ;

        if (i2c_smbus_access (I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data))
            return -1 ;
        else
            return data.byte & 0xFF ;

    }

    unsigned char i2c::ReadReg8 (int reg){
         union i2c_smbus_data data;

        if (i2c_smbus_access (I2C_SMBUS_READ, reg, I2C_SMBUS_BYTE_DATA, &data))
            return -1 ;
        else
            return data.byte & 0xFF ;
    }

    unsigned short i2c::ReadReg16 (int reg){
        union i2c_smbus_data data;

        if (i2c_smbus_access (I2C_SMBUS_READ, reg, I2C_SMBUS_WORD_DATA, &data))
            return -1 ;
        else
            return data.word & 0xFFFF ;
    }

    unsigned char i2c::Write (int data){
        return i2c_smbus_access (I2C_SMBUS_WRITE, data, I2C_SMBUS_BYTE, NULL) ;

    }

    unsigned char i2c::WriteReg8 (int reg, int value){
        union i2c_smbus_data data ;

        data.byte = value ;
        return i2c_smbus_access (I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE_DATA, &data) ;
    }


    unsigned short i2c::WriteReg16 (int reg, int value){
        union i2c_smbus_data data ;

        data.word = value ;
        return i2c_smbus_access (I2C_SMBUS_WRITE, reg, I2C_SMBUS_WORD_DATA, &data) ;

    }






