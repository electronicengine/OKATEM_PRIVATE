#include "sfp.h"
#include "main.h"
#include "i2c.h"


//const unsigned char WRITE_ADDRESS = 0x00;

#define SFP_I2C_INFO_ADDRESS 0x50
#define SFP_I2C_DIAG_ADDRESS 0x51

int getSfpTemperature()
{

    HAL_StatusTypeDef i2c_status;
    char buffer[256];
    unsigned char data = 0x00;


    i2c_status = HAL_I2C_Master_Transmit(&hi2c2, 0x51, &data, 1, 1000);

//  if(i2c_status != HAL_OK)
    return i2c_status;


//    i2c_status = HAL_I2C_Master_Receive(&hi2c2, SFP_I2C_DIAG_ADDRESS, &buffer, 256, 1000);

//    if(i2c_status != HAL_OK)
//        return 2.0f;


//    return 3.0f;

}
