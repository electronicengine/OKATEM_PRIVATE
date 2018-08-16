
#include "gps.h"
#include "usart.h"
#include "gpio.h"
#include "main.h"

char rx_data;

short int gprmc_status = GPS_BUSY;
short int gprmc_enable = GPS_BUSY;

short int gpgga_status = GPS_BUSY;
short int gpgga_enable = GPS_BUSY;

short int gpgsa_status = GPS_BUSY;
short int gpgsa_enable = GPS_BUSY;

short int gpgll_status = GPS_BUSY;
short int gpgll_enable = GPS_BUSY;


void getGPGLL()
{

    static const unsigned char gpgll_header[6] = {'$', 'G', 'P', 'G', 'L', 'L'};
    static unsigned char gpgll_buffer[100];
    static int gpgll_index = 0;

    gpgll_status = GPS_BUSY;

    switch(gpgll_index)
    {

    case 0:
            if(rx_data == gpgll_header[0])
            {
                gpgll_buffer[gpgll_index] = rx_data;
                gpgll_index++;
            }

            break;

        case 1:
            if(rx_data == gpgll_header[1])
            {
                gpgll_buffer[gpgll_index] = rx_data;
                gpgll_index++;
            }

            break;
        case 2:
            if(rx_data == gpgll_header[2])
            {
                gpgll_buffer[gpgll_index] = rx_data;
                gpgll_index++;
            }

            break;
        case 3:
            if(rx_data == gpgll_header[3])
            {
                gpgll_buffer[gpgll_index] = rx_data;
                gpgll_index++;
            }

            break;
        case 4:
            if(rx_data == gpgll_header[4])
            {
                gpgll_buffer[gpgll_index] = rx_data;
                gpgll_index++;
            }

            break;
        case 5:
            if(rx_data == gpgll_header[5])
            {
                gpgll_buffer[gpgll_index] = rx_data;
                gpgll_index++;
            }

            break;
        default:


            if(gpgll_index >= 6 && gpgll_index <= 70)
            {
                if(rx_data == '\n')
                {

                    for(int i=0; i<100; i++)
                     gpsData.gpgll_body[i] = 0;

                    for(int i=0; i<gpgll_index; i++)
                     gpsData.gpgll_body[i] = gpgll_buffer[i];

                    for(int i=0; i<100; i++)
                     gpgll_buffer[i] = 0;

                    gpgll_index = 0;
                    gpgll_status = GPS_READY;
                    gpgll_enable = GPS_READY;

                }
                else
                {
                    gpgll_buffer[gpgll_index] = rx_data;
                    gpgll_index ++;
                }
            }
            break;
    }
}


void getGPGSA()
{
    static const unsigned char gpgsa_header[6] = {'$', 'G', 'P', 'G', 'S', 'A'};
    static volatile unsigned char gpgsa_buffer[100];
    static int gpgsa_index = 0;

    gpgsa_status = GPS_BUSY;

    switch(gpgsa_index)
    {

        case 0:

            if(rx_data == gpgsa_header[0])
            {
                gpgsa_buffer[gpgsa_index] = rx_data;
                gpgsa_index++;
            }

            break;

        case 1:

            if(rx_data == gpgsa_header[1])
            {
                gpgsa_buffer[gpgsa_index] = rx_data;
                gpgsa_index++;
            }

            break;
        case 2:

            if(rx_data == gpgsa_header[2])
            {
                gpgsa_buffer[gpgsa_index] = rx_data;
                gpgsa_index++;
            }

            break;
        case 3:

            if(rx_data == gpgsa_header[3])
            {
                gpgsa_buffer[gpgsa_index] = rx_data;
                gpgsa_index++;
            }

            break;
        case 4:

            if(rx_data == gpgsa_header[4])
            {
                gpgsa_buffer[gpgsa_index] = rx_data;
                gpgsa_index++;
            }

            break;
        case 5:

            if(rx_data == gpgsa_header[5])
            {
                gpgsa_buffer[gpgsa_index] = rx_data;
                gpgsa_index++;
            }

            break;
        default:

            if(gpgsa_index >= 6 && gpgsa_index <= 70)
            {
                if(rx_data == '\n')
                {

                    for(int i=0; i<100; i++)
                     gpsData.gpgsa_body[i] = 0;

                    for(int i=0; i<gpgsa_index; i++)
                     gpsData.gpgsa_body[i] = gpgsa_buffer[i];

                    for(int i=0; i<100; i++)
                     gpgsa_buffer[i] = 0;

                    gpsData.gpgsa_size = gpgsa_index;

                    gpgsa_index = 0;
                    gpgsa_status = GPS_READY;
                    gpgsa_enable = GPS_READY;

                }else
                {
                    gpgsa_buffer[gpgsa_index] = rx_data;
                    gpgsa_index ++;
                }
            }

            break;
    }

}



void getGPGGA()
{
    static const unsigned char gpgga_header[6] = {'$', 'G', 'P', 'G', 'G', 'A'};
    static volatile unsigned char gpgga_buffer[100];
    static int gpgga_index = 0;

    gpgga_status = GPS_BUSY;

    switch(gpgga_index)
    {

        case 0:

            if(rx_data == gpgga_header[0])
            {
                gpgga_buffer[gpgga_index] = rx_data;
                gpgga_index++;
            }

            break;

        case 1:

            if(rx_data == gpgga_header[1])
            {
                gpgga_buffer[gpgga_index] = rx_data;
                gpgga_index++;
            }

            break;
        case 2:

            if(rx_data == gpgga_header[2])
            {
                gpgga_buffer[gpgga_index] = rx_data;
                gpgga_index++;
            }

            break;
        case 3:

            if(rx_data == gpgga_header[3])
            {
                gpgga_buffer[gpgga_index] = rx_data;
                gpgga_index++;
            }

            break;
        case 4:

            if(rx_data == gpgga_header[4])
            {
                gpgga_buffer[gpgga_index] = rx_data;
                gpgga_index++;
            }

            break;
        case 5:

            if(rx_data == gpgga_header[5])
            {
                gpgga_buffer[gpgga_index] = rx_data;
                gpgga_index++;
            }

            break;
        default:

            if(gpgga_index >= 6 && gpgga_index <= 70)
            {
                if(rx_data == '\n')
                {

                    for(int i=0; i<100; i++)
                     gpsData.gpgga_body[i] = 0;

                    for(int i=0; i<gpgga_index; i++)
                     gpsData.gpgga_body[i] = gpgga_buffer[i];

                    for(int i=0; i<100; i++)
                     gpgga_buffer[i] = 0;

                    gpsData.gpgga_size = gpgga_index;

                    gpgga_index = 0;
                    gpgga_status = GPS_READY;
                    gpgga_enable = GPS_READY;

                }else
                {
                    gpgga_buffer[gpgga_index] = rx_data;
                    gpgga_index ++;
                }
            }

            break;
    }

}



void getGPRMC()
{

    static const unsigned char gprmc_header[6] = {'$', 'G', 'P', 'R', 'M', 'C'};
    static unsigned char gprmc_buffer[100];
    static int gprmc_index = 0;

    gprmc_status = GPS_BUSY;

    switch(gprmc_index)
    {

        case 0:
            if(rx_data == gprmc_header[0])
            {
                gprmc_buffer[gprmc_index] = rx_data;
                gprmc_index++;
            }

            break;

        case 1:
            if(rx_data == gprmc_header[1])
            {
                gprmc_buffer[gprmc_index] = rx_data;
                gprmc_index++;
            }

            break;
        case 2:
            if(rx_data == gprmc_header[2])
            {
                gprmc_buffer[gprmc_index] = rx_data;
                gprmc_index++;
            }

            break;
        case 3:
            if(rx_data == gprmc_header[3])
            {
                gprmc_buffer[gprmc_index] = rx_data;
                gprmc_index++;
            }

            break;
        case 4:
            if(rx_data == gprmc_header[4])
            {
                gprmc_buffer[gprmc_index] = rx_data;
                gprmc_index++;
            }

            break;
        case 5:
            if(rx_data == gprmc_header[5])
            {
                gprmc_buffer[gprmc_index] = rx_data;
                gprmc_index++;
            }

            break;
        default:


            if(gprmc_index >= 6 && gprmc_index <= 70)
            {
                if(rx_data == '\n')
                {

                    for(int i=0; i<100; i++)
                     gpsData.gprmc_body[i] = 0;

                    for(int i=0; i<gprmc_index; i++)
                     gpsData.gprmc_body[i] = gprmc_buffer[i];

                    for(int i=0; i<100; i++)
                     gprmc_buffer[i] = 0;

                    gprmc_index = 0;
                    gprmc_status = GPS_READY;
                    gprmc_enable = GPS_READY;

                }
                else
                {
                    gprmc_buffer[gprmc_index] = rx_data;
                    gprmc_index ++;
                }
            }
            break;
    }
}



void gpsInit()
{

    GPIO_PinState gps_state;

    HAL_UART_Receive_IT(&huart4, (uint8_t *)&rx_data, 1);

    do
    {

        HAL_GPIO_WritePin(GPS_ONOFF_GPIO_Port, GPS_ONOFF_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPS_ONOFF_GPIO_Port, GPS_ONOFF_Pin, GPIO_PIN_RESET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPS_ONOFF_GPIO_Port, GPS_ONOFF_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPS_ONOFF_GPIO_Port, GPS_ONOFF_Pin, GPIO_PIN_RESET);

        HAL_Delay(2000);

        gps_state = HAL_GPIO_ReadPin(GPS_RPFWRUP_GPIO_Port, GPS_RPFWRUP_Pin);

        _Event_Handler("GPS_Initializing...");

    }while(gps_state == 0);
}


void receiveGpsData()
{

      if(gprmc_enable != GPS_READY)
        getGPRMC();

      if(gpgga_enable != GPS_READY)
        getGPGGA();

      if(gpgsa_enable != GPS_READY)
        getGPGSA();

      if(gpgll_enable != GPS_READY)
        getGPGLL();

      if(gprmc_enable != GPS_READY || gpgga_enable != GPS_READY
              || gpgsa_enable != GPS_READY || gpgll_enable != GPS_READY)
      {
          rx_data=0;
          HAL_UART_Receive_IT(&huart4, (uint8_t *)&rx_data, 1);
      }

}


void enableGps()
{

    gprmc_enable = GPS_BUSY;
    gpgga_enable = GPS_BUSY;
    gpgsa_enable = GPS_BUSY;
    gpgll_enable = GPS_BUSY;

    HAL_UART_Receive_IT(&huart4, (uint8_t *)&rx_data, 1);

}

int checkGpsData()
{
    if(gprmc_status == GPS_READY && gpgga_status == GPS_READY
            && gpgsa_status == GPS_READY && gpgll_status == GPS_READY)
        return GPS_READY;
    else
        return GPS_BUSY;
}
