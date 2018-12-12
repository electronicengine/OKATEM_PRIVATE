

#include "spicom.h"
#include "spi.h"


volatile short int UpdateDataAvailable = 0;
volatile short int UpdateFinished = 0;

int NextUpdateDataPackage = 1;

void SPI1_IRQHandler(void)
{

   HAL_SPI_StateTypeDef status;
   HAL_StatusTypeDef update_file_status;

    HAL_SPI_IRQHandler(&hspi1);

    status = HAL_SPI_GetState(&hspi1);

    if(status == HAL_SPI_STATE_READY)
    {


        update_file_status = checkIfUpdateData();

        if(update_file_status == HAL_OK)
        {

            update_file_status = confirmUpdateDataAccuracy();

            if(update_file_status == HAL_OK)
            {
                UpdateDataAvailable = 1;
            }
            else
            {
                UpdateDataAvailable = 0;
            }

            putUpdateDataResponse();

        }

    }


    if(UpdateFinished == 0)
        HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t *)SpiTxData, (uint8_t *)SpiRxData,  SPI_TRANSFER_SIZE);

}



HAL_StatusTypeDef confirmUpdateDataAccuracy()
{

    uint16_t checksum = 0;


    for(int i=0; i< SPI_ENTITY_SIZE; i++)
        checksum += UpdateFile->data[i];


    if(UpdateFile->current_sequence_number == 0 || UpdateFile->total_sequence_number == 0)
        return HAL_ERROR;

    if(checksum != SpiRxData->checksum)
    {
        return HAL_ERROR;
    }

    if(UpdateFile->current_sequence_number != NextUpdateDataPackage)
    {
        return HAL_ERROR;
    }
    else
    {
        NextUpdateDataPackage++;
        return HAL_OK;

    }

}



HAL_StatusTypeDef checkIfUpdateData()
{

    if((SpiRxData->header & 0xff) == 'U' && ((SpiRxData->header >> 8) & 0xff) == 'P')
    {
        memcpy(UpdateFile, SpiRxData->data, SPI_DATA_SIZE);
        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }

}



void putUpdateDataResponse()
{

    SpiTxData->header = 'U' | 'P' << 8;
    SpiTxData->data[4] = NextUpdateDataPackage & 0xff;
    SpiTxData->data[5] = (NextUpdateDataPackage >>  8) & 0xff;
    SpiTxData->data[6] = (NextUpdateDataPackage >> 16) & 0xff;
    SpiTxData->data[7] = (NextUpdateDataPackage >> 24) & 0xff;

}



Update_File processUpdateData()
{

    static unsigned char *buffer;
    static short int memory_allocated = 0;
    static uint32_t size = 0;
    Update_File descriptor;


    if(UpdateFile->current_sequence_number == 1 && memory_allocated == 0)
    {
        size = UpdateFile->total_sequence_number * UPDATE_FILE_PACKAGE_SIZE;
        buffer = malloc(size);
        memory_allocated = 1;

        descriptor.file_size = size;
    }

    descriptor.receive_complited = 0;

    memcpy(&buffer[(UpdateFile->current_sequence_number - 1) * UPDATE_FILE_PACKAGE_SIZE], &UpdateFile->data[0], UPDATE_FILE_PACKAGE_SIZE);

    if(UpdateFile->current_sequence_number == UpdateFile->total_sequence_number)
    {

        mprintf("Upgrading...\r\n");

        SpiRxData->header = 0;
        SpiRxData->checksum = 0;
        UpdateFile->current_sequence_number = 0;
        UpdateFile->total_sequence_number = -1;


        HAL_Delay(50);

        descriptor.receive_complited = 1;
        descriptor.file_size = size;
        descriptor.file_pointer = buffer;
//        descriptor.file_pointer = malloc(size);

//        memcpy(descriptor.file_pointer, buffer, size);

//        free(buffer);

        return descriptor;

    }
    else
    {
        return descriptor;
    }



}

int checkDataAvailable()
{
    return UpdateDataAvailable;
}

int setDataRecieved()
{
    UpdateDataAvailable = 0;
    return 0;
}

void updateFinished()
{
    UpdateFinished = 1;
}
