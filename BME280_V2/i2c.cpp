#include "i2c.h"


    i2c::i2c(int adresseI2C){
        SetupInterface("/dev/i2c-1",adresseI2C);
    }



    void i2c::SetupInterface (const char *device, int devId){
        if ((fd = open (device, O_RDWR)) < 0)
            cout << "Unable to open I2C device:" << endl;

        if (ioctl (fd, I2C_SLAVE, devId) < 0)
            cout << "Unable to select I2C device:" << endl ;

    }

    int i2c::i2c_smbus_access (int fd, char rw, uint8_t command, int size, union i2c_smbus_data *data)
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

        if (i2c_smbus_access (fd, I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data))
            return -1 ;
        else
            return data.byte & 0xFF ;

    }

    unsigned char i2c::ReadReg8 (int reg){
         union i2c_smbus_data data;

        if (i2c_smbus_access (fd, I2C_SMBUS_READ, reg, I2C_SMBUS_BYTE_DATA, &data))
            return -1 ;
        else
            return data.byte & 0xFF ;

    }

    unsigned short i2c::ReadReg16 (int reg){
        union i2c_smbus_data data;

        if (i2c_smbus_access (fd, I2C_SMBUS_READ, reg, I2C_SMBUS_WORD_DATA, &data))
            return -1 ;
        else
            return data.word & 0xFFFF ;
    }

    unsigned char i2c::Write (int data){
        return i2c_smbus_access (fd, I2C_SMBUS_WRITE, data, I2C_SMBUS_BYTE, NULL) ;

    }

    unsigned char i2c::WriteReg8 (int reg, int value){
        union i2c_smbus_data data ;

        data.byte = value ;
        return i2c_smbus_access (fd, I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE_DATA, &data) ;

    }

    unsigned short i2c::WriteReg16 (int reg, int value){
        union i2c_smbus_data data ;

        data.word = value ;
        return i2c_smbus_access (fd, I2C_SMBUS_WRITE, reg, I2C_SMBUS_WORD_DATA, &data) ;

    }






