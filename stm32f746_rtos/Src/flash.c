

/* Includes ------------------------------------------------------------------*/
#include "flash.h"

void reWriteFlash(unsigned char *Data, size_t Size, long Address)
{
    FLASH_Erase_Sector(FLASH_SECTOR_6, VOLTAGE_RANGE_3);

    for(size_t i = 0; i<Size; i++)
        HAL_FLASH_Program(TYPEPROGRAM_BYTE, Address + i , Data[i]);

}

void writeFlash(uint8_t Data, long Address)
{
    HAL_FLASH_Program(TYPEPROGRAM_BYTE, Address , (uint8_t) Data);
}



uint8_t *readFlash(int Address)
{
    uint8_t *flash_data;

    flash_data = (uint8_t *)Address;

    return flash_data;
}



void loadUpdateFile(unsigned char *Buffer, uint32_t Size)
{
    HAL_StatusTypeDef status;

    HAL_FLASH_Unlock();

    mprintf("Memory Ereasing...\r\n");

    FLASH_Erase_Sector(FLASH_SECTOR_2, VOLTAGE_RANGE_3);
    FLASH_Erase_Sector(FLASH_SECTOR_3, VOLTAGE_RANGE_3);
    FLASH_Erase_Sector(FLASH_SECTOR_4, VOLTAGE_RANGE_3);
    FLASH_Erase_Sector(FLASH_SECTOR_5, VOLTAGE_RANGE_3);


    HAL_Delay(50);

    mprintf("UpdateFile is writing on memory\r\n");

    for(int i=0; i<Size; i++)
    {
        status = HAL_FLASH_Program(TYPEPROGRAM_BYTE, APPLICATION_ADDRESS + i , Buffer[i]);

        if(status != HAL_OK)
            mprintf("Hal flash error\r\n");

    }

    HAL_FLASH_Lock();


    mprintf("UpdateFile has been writen on memory\r\n");


    HAL_Delay(100);

}

