#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>

#include <sstream>
#include <cstdarg>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <fstream>
#include <memory.h>
#include <map>

#define SUCCESS 1
#define FAIL 2

#define MAX_LOG_LINE 1000
#define LOG_FILE "/var/www/html/log.txt"

#define CONTROLLER_PORT 24000

#define SPI_ENTITY_SIZE 108
#define SPI_TRANSFER_SIZE 120
#define SPI_DATA_SIZE 116

#define SFP_DATA_SIZE 24

#define ETHERNET_TRANSFER_SIZE 292
#define ETHERNET_ENTITY_SIZE 288
#define STREAM_DATA_SIZE 280


#define FORWARD 1
#define BACKWARD 2
#define STOP 0


enum class Status
{

    time_out,
    error,
    ok

};


struct SFP_DATA_FORMAT
{
    float temperature;
    float vcc;
    float tx_bias;
    float tx_power;
    float rx_power;
    int status;

    SFP_DATA_FORMAT& operator =(unsigned char *Data)
    {

        int index = 0;

        int temp_temperature;
        int temp_vcc;
        int temp_tx_bias;
        int temp_tx_power;
        int temp_rx_power;

        temp_temperature = (Data[index++]);
        temp_temperature |= (Data[index++] << 8);
        temp_temperature |= (Data[index++] << 16);
        temp_temperature |= (Data[index++] << 24);


        temp_vcc = (Data[index++]);
        temp_vcc |= (Data[index++] << 8);
        temp_vcc |= (Data[index++] << 16);
        temp_vcc |= (Data[index++] << 24);

        temp_tx_bias = (Data[index++]);
        temp_tx_bias |= (Data[index++] << 8);
        temp_tx_bias |= (Data[index++] << 16);
        temp_tx_bias |= (Data[index++] << 24);

        temp_tx_power = (Data[index++]);
        temp_tx_power |= (Data[index++] << 8);
        temp_tx_power |= (Data[index++] << 16);
        temp_tx_power |= (Data[index++] << 24);

        temp_rx_power = (Data[index++]);
        temp_rx_power |= (Data[index++] << 8);
        temp_rx_power |= (Data[index++] << 16);
        temp_rx_power |= (Data[index++] << 24);

        status = (Data[index++]);
        status |= (Data[index++] << 8);
        status |= (Data[index++] << 16);
        status |= (Data[index++] << 24);


        temperature = (float)temp_temperature / 100000;
        vcc = (float)temp_vcc / 100000;
        tx_bias = (float)temp_tx_bias / 100000;
        tx_power = (float)temp_tx_power / 100000;
        rx_power = (float)temp_rx_power / 100000;

        return *this;

    }



    operator unsigned char *()
    {
        unsigned char *data = new unsigned char[24];
        int index = 0;
        int temp_temperature = temperature * 100000;
        int temp_vcc = vcc * 100000;
        int temp_tx_bias = tx_bias * 100000;
        int temp_tx_power = tx_power * 100000;
        int temp_rx_power = rx_power * 100000;


        data[index++] = temp_temperature & 0xff;
        data[index++] = (temp_temperature >> 8) & 0xff;
        data[index++] = (temp_temperature >> 16) & 0xff;
        data[index++] = (temp_temperature >> 24) & 0xff;

        data[index++] = temp_vcc & 0xff;
        data[index++] = (temp_vcc >> 8) & 0xff;
        data[index++] = (temp_vcc >> 16) & 0xff;
        data[index++] = (temp_vcc >> 24) & 0xff;

        data[index++] = temp_tx_bias & 0xff;
        data[index++] = (temp_tx_bias >> 8) & 0xff;
        data[index++] = (temp_tx_bias >> 16) & 0xff;
        data[index++] = (temp_tx_bias >> 24) & 0xff;

        data[index++] = temp_tx_power & 0xff;
        data[index++] = (temp_tx_power >> 8) & 0xff;
        data[index++] = (temp_tx_power >> 16) & 0xff;
        data[index++] = (temp_tx_power >> 24) & 0xff;

        data[index++] = temp_rx_power & 0xff;
        data[index++] = (temp_rx_power >> 8) & 0xff;
        data[index++] = (temp_rx_power >> 16) & 0xff;
        data[index++] = (temp_rx_power >> 24) & 0xff;

        data[index++] = status & 0xff;
        data[index++] = (status >> 8) & 0xff;
        data[index++] = (status >> 16) & 0xff;
        data[index++] = (status >> 24) & 0xff;


        return data;
    }

};


struct SENSOR_DATA
{
    uint32_t temperature;
    uint32_t compass_degree;
    uint32_t pressure;
    uint32_t altitude;
    uint8_t wheather_condition;


    operator unsigned char*()
    {
        unsigned char *data = new unsigned char[sizeof(SENSOR_DATA)];

        int index = 0;

        data[index++] = temperature & 0xff;
        data[index++] = (temperature >> 8) & 0xff;
        data[index++] = (temperature >> 16) & 0xff;
        data[index++] = (temperature >> 24) & 0xff;

        data[index++] = compass_degree & 0xff;
        data[index++] = (compass_degree >> 8) & 0xff;
        data[index++] = (compass_degree >> 16) & 0xff;
        data[index++] = (compass_degree >> 24) & 0xff;

        data[index++] = pressure & 0xff;
        data[index++] = (pressure >> 8) & 0xff;
        data[index++] = (pressure >> 16) & 0xff;
        data[index++] = (pressure >> 24) & 0xff;

        data[index++] = altitude & 0xff;
        data[index++] = (altitude >> 8) & 0xff;
        data[index++] = (altitude >> 16) & 0xff;
        data[index++] = (altitude >> 24) & 0xff;

        data[index++] = wheather_condition;

        return data;
    }

    SENSOR_DATA& operator = (unsigned char *TransferData)
    {
        int index = 0;

        temperature = TransferData[index++];
        temperature |= (TransferData[index++] << 8);
        temperature |= (TransferData[index++] << 16);
        temperature |= (TransferData[index++] << 24);

        compass_degree = TransferData[index++];
        compass_degree |= (TransferData[index++] << 8);
        compass_degree |= (TransferData[index++] << 16);
        compass_degree |= (TransferData[index++] << 24);

        pressure = TransferData[index++];
        pressure |= (TransferData[index++] << 8);
        pressure |= (TransferData[index++] << 16);
        pressure |= (TransferData[index++] << 24);

        altitude = TransferData[index++];
        altitude |= (TransferData[index++] << 8);
        altitude |= (TransferData[index++] << 16);
        altitude |= (TransferData[index++] << 24);

        wheather_condition = TransferData[index++];
        wheather_condition |= (TransferData[index++] << 8);
        wheather_condition |= (TransferData[index++] << 16);
        wheather_condition |= (TransferData[index++] << 24);


        return *this;
    }


};


struct GPS_DATA
{
    double utc_time;
    unsigned char status;
    double latitude;
    unsigned char ns_indicator;

    double longnitude;
    unsigned char we_indicator;

    double speed_over_ground;
    double course_over_ground;

    std::string date;


    GPS_DATA& operator =(std::string GpsString)
    {

        int i = 0;
        std::size_t pos;

        double degrees;
        double minutes;

        std::string gps_string = GpsString;

        std::string delimiter = ",";
        std::string token[20];


        try
        {
            while((pos = gps_string.find(delimiter)) != std::string::npos)
            {

                if(i<20)
                {
                    token[i] = gps_string.substr(0, pos);
                    gps_string.erase(0, pos + delimiter.length());
                    i++;
                }
                else
                    break;


            }

            i=0;

            if(!token[1].empty())
                utc_time = (double)std::atof(token[1].c_str());

            if(!token[2].empty())
                status = (unsigned char)*token[2].c_str();

            if(!token[3].empty())
            {
                degrees = (double)std::atof(token[3].substr(0, 2).c_str());
                minutes = (double)std::atof(token[3].substr(2, 7).c_str());
                latitude =  degrees + (minutes / 60);
            }

            if(!token[4].empty())
                ns_indicator = (unsigned char)*token[4].c_str();

            if(!token[5].empty())
            {
                degrees = (double)std::atof(token[5].substr(0, 3).c_str());
                minutes = (double)std::atof(token[5].substr(3, 7).c_str());
                longnitude = degrees + (minutes / 60);
            }

            if(!token[6].empty())
                we_indicator = (unsigned char)*token[6].c_str();

            if(!token[7].empty())
                speed_over_ground = (double)std::atof(token[7].c_str());

            if(!token[8].empty())
                course_over_ground =(double)std::atof(token[8].c_str());

            if(!token[9].empty())
                date = token[9];

        }
        catch(std::exception& ex)
        {
            std::cout << "GPS_DATA asign Exception: " << ex.what() << std::endl;
        }

        return *this;
    }
};


struct SPI_TRANSFER_FORMAT
{
    uint16_t header;
    unsigned char data[SPI_DATA_SIZE];
    uint16_t checksum;


    SPI_TRANSFER_FORMAT(){}

    SPI_TRANSFER_FORMAT(unsigned char *SpiData){

        int index = 0;

        header = SpiData[index++];
        header |= (SpiData[index++] << 8);

        for(int i = 0; i<SPI_DATA_SIZE; i++)
            data[i] = SpiData[i + index];

        index += SPI_DATA_SIZE;

        checksum = (SpiData[index++]);
        checksum &= (SpiData[index++] << 8);

    }

    operator unsigned char*()
    {

        int index = 0;
        unsigned char *spi_data = new unsigned char[SPI_TRANSFER_SIZE];

        spi_data[index++] = header & 0xff;
        spi_data[index++] = (header >> 8) & 0xff;

        for(int i = 0; i<SPI_DATA_SIZE; i++)
            spi_data[i + index ] = data[i];

        index += SPI_DATA_SIZE;

        spi_data[index++] = checksum & 0xff;
        spi_data[index++] = (checksum >> 8) & 0xff;

        return spi_data;

    }

    SPI_TRANSFER_FORMAT& operator =(unsigned char *SpiData)
    {

        int index = 0;

        header = SpiData[index++];
        header |= (SpiData[index++] << 8);

        for(int i = 0; i<SPI_DATA_SIZE; i++)
            data[i] = SpiData[i + index];

        index += SPI_DATA_SIZE;

        checksum = (SpiData[index++]);
        checksum &= (SpiData[index++] << 8);


        return *this;

    }

    void clear()
    {
        header = 0;

        for(int i=0; i<SPI_DATA_SIZE; i++)
            data[i] = 0;

        checksum = 0;
    }
};


struct ENVIRONMENT_DATA_FORMAT
{

    GPS_DATA gps_data;
    SENSOR_DATA sensor_data;
    std::string gps_string;

    ENVIRONMENT_DATA_FORMAT()
    {

    }

    ENVIRONMENT_DATA_FORMAT(SPI_TRANSFER_FORMAT SpiData)
    {
        try
        {

            gps_string = std::string(&SpiData.data[0], &SpiData.data[98]);

            gps_data = gps_string;

            sensor_data = &SpiData.data[99];

        }
        catch(std::exception& ex)
        {
            std::cout << "SPI_TX_FORMAT exception: " << ex.what() << std::endl;
        }

    }


    operator SPI_TRANSFER_FORMAT()
    {
        SPI_TRANSFER_FORMAT spi_data;
        int index = 0;

        unsigned char * sensor_data_pointer;

        spi_data.header = 'E';
        spi_data.header |= 'N';

        for(int i = 0; i<99; i++)
            spi_data.data[i] = gps_string.c_str()[i + index];

        index += 99;

        sensor_data_pointer = sensor_data;
        memcpy(&spi_data[index], sensor_data_pointer, sizeof(SENSOR_DATA));

        index += sizeof(SENSOR_DATA);

        delete sensor_data_pointer;

        return spi_data;

    }

    ENVIRONMENT_DATA_FORMAT& operator = (SPI_TRANSFER_FORMAT& SpiData)
    {

        try
        {

            gps_string = std::string(&SpiData.data[0], &SpiData.data[98]);

            gps_data = gps_string;

            sensor_data = &SpiData.data[99];

        }
        catch(std::exception& ex)
        {
            std::cout << "SPI_TX_FORMAT exception: " << ex.what() << std::endl;
        }

        return *this;
    }

};


struct UPDATE_FILE_FORMAT
{

    uint32_t total_sequence_number;
    uint32_t current_sequence_number;
    unsigned char data[SPI_ENTITY_SIZE];

    bool is_available;

    operator bool()
    {
        return is_available;
    }

    void operator =(bool Var)
    {
        is_available = Var;
    }

    operator SPI_TRANSFER_FORMAT()
    {
        int checksum = 0;

        SPI_TRANSFER_FORMAT spi_transfer_format;


        spi_transfer_format.header =  'U' | 'P' << 8;


        spi_transfer_format.data[0] = (total_sequence_number) & 0xff;
        spi_transfer_format.data[1] = (total_sequence_number >> 8) & 0xff;
        spi_transfer_format.data[2] = (total_sequence_number >> 16) & 0xff;
        spi_transfer_format.data[3] = (total_sequence_number >> 24) & 0xff;

        spi_transfer_format.data[4] = (current_sequence_number) & 0xff;
        spi_transfer_format.data[5] = (current_sequence_number >> 8) & 0xff;
        spi_transfer_format.data[6] = (current_sequence_number >> 16) & 0xff;
        spi_transfer_format.data[7] = (current_sequence_number >> 24) & 0xff;

        for(int i=8; i<SPI_ENTITY_SIZE + 8; i++)
          spi_transfer_format.data[i] = data[i - 8];

        for(int i=0; i<SPI_ENTITY_SIZE; i++)
            checksum += data[i];

        spi_transfer_format.checksum = checksum;


        return spi_transfer_format;

    }

    UPDATE_FILE_FORMAT& operator =(const SPI_TRANSFER_FORMAT& SpiData)
    {


        total_sequence_number = (SpiData.data[0]) | (SpiData.data[1] << 8) | (SpiData.data[2] << 16) | (SpiData.data[3] << 24);
        current_sequence_number = (SpiData.data[4]) | (SpiData.data[5] << 8) | (SpiData.data[6] << 16) | (SpiData.data[7] << 24);

        for(int i=8; i<SPI_ENTITY_SIZE + 8; i++)
            data[i - 8] = SpiData.data[i];

        return *this;

    }

    void clear()
    {
        total_sequence_number = 0;
        current_sequence_number = 0;

        for(int i=0;i<SPI_ENTITY_SIZE; i++)
            data[i] = 0;

        is_available = 0;
    }

};


struct CONTROL_DATA_FORMAT
{


    uint8_t garbage1[45]; // header

    uint8_t mode;

    uint32_t x_position;
    uint32_t y_position;
    uint32_t z_position;

    uint8_t step_motor1_direction;
    uint8_t step_motor2_direction;
    uint8_t step_motor3_direction;
    uint8_t step_motor4_direction;
    uint8_t servo_motor1_direction;
    uint8_t servo_motor2_direction;

    uint8_t step_motor1_speed;
    uint8_t step_motor2_speed;
    uint8_t step_motor3_speed;
    uint8_t step_motor4_speed;
    uint8_t servo_motor1_degree;
    uint8_t servo_motor2_degree;

    uint8_t calibrate_sensor;

    uint8_t garbage2[45]; //footer

    volatile bool is_transmitted;

    operator bool()
    {
        return is_transmitted;
    }

    CONTROL_DATA_FORMAT(){}

    CONTROL_DATA_FORMAT(SPI_TRANSFER_FORMAT SpiData)
    {
        int index = 0;

        for(int i=0; i<45; i++)
            garbage1[i] = SpiData.data[i + index];

        index += 45;

        mode = SpiData.data[index++];

        x_position = (SpiData.data[index++]);
        x_position |= (SpiData.data[index++] << 8);
        x_position |= (SpiData.data[index++] << 16);
        x_position |= (SpiData.data[index++] << 24);

        y_position = (SpiData.data[index++]);
        y_position |= (SpiData.data[index++] << 8);
        y_position |= (SpiData.data[index++] << 16);
        y_position |= (SpiData.data[index++] << 24);

        z_position = (SpiData.data[index++]);
        z_position |= (SpiData.data[index++] << 8);
        z_position |= (SpiData.data[index++] << 16);
        z_position |= (SpiData.data[index++] << 24);

        step_motor1_direction = SpiData.data[index++];
        step_motor2_direction = SpiData.data[index++];
        step_motor3_direction = SpiData.data[index++];
        step_motor4_direction = SpiData.data[index++];
        servo_motor1_direction = SpiData.data[index++];
        servo_motor2_direction = SpiData.data[index++];

        step_motor1_speed = SpiData.data[index++];
        step_motor2_speed = SpiData.data[index++];
        step_motor3_speed = SpiData.data[index++];
        step_motor4_speed = SpiData.data[index++];
        servo_motor1_degree = SpiData.data[index++];
        servo_motor2_degree = SpiData.data[index++];

        calibrate_sensor = SpiData.data[index++];


        for(int i=0; i<45; i++)
            garbage2[i] = SpiData.data[i + index];

        index += 45;

        is_transmitted = true;

    }


    CONTROL_DATA_FORMAT& operator =(bool Var)
    {
        is_transmitted = Var;

        return *this;
    }


    operator SPI_TRANSFER_FORMAT()
    {

        SPI_TRANSFER_FORMAT spi_transfer_data;

        int index = 0;

        spi_transfer_data.header = ('C' | 'O' << 8);

        for(int i=0; i<45; i++)
            spi_transfer_data.data[i] = garbage1[i];

        index += 45;

        spi_transfer_data.data[index++] = mode;

        spi_transfer_data.data[index++] = (x_position) & 0xff;
        spi_transfer_data.data[index++] = (x_position >> 8) & 0xff;
        spi_transfer_data.data[index++] = (x_position >> 16) & 0xff;
        spi_transfer_data.data[index++] = (x_position >> 24) & 0xff;

        spi_transfer_data.data[index++] = (y_position) & 0xff;
        spi_transfer_data.data[index++] = (y_position >> 8) & 0xff;
        spi_transfer_data.data[index++] = (y_position >> 16) & 0xff;
        spi_transfer_data.data[index++] = (y_position >> 24) & 0xff;

        spi_transfer_data.data[index++] = (z_position) & 0xff;
        spi_transfer_data.data[index++] = (z_position >> 8) & 0xff;
        spi_transfer_data.data[index++] = (z_position >> 16) & 0xff;
        spi_transfer_data.data[index++] = (z_position >> 24) & 0xff;

        spi_transfer_data.data[index++] = step_motor1_direction;
        spi_transfer_data.data[index++] = step_motor2_direction;
        spi_transfer_data.data[index++] = step_motor3_direction;
        spi_transfer_data.data[index++] = step_motor4_direction;
        spi_transfer_data.data[index++] = servo_motor1_direction;
        spi_transfer_data.data[index++] = servo_motor2_direction;

        spi_transfer_data.data[index++] = step_motor1_speed;
        spi_transfer_data.data[index++] = step_motor2_speed;
        spi_transfer_data.data[index++] = step_motor3_speed;
        spi_transfer_data.data[index++] = step_motor4_speed;
        spi_transfer_data.data[index++] = servo_motor1_degree;
        spi_transfer_data.data[index++] = servo_motor2_degree;

        spi_transfer_data.data[index++] = calibrate_sensor;


        for(int i=0; i<45; i++)
            spi_transfer_data.data[i + index] = garbage2[i];


        index += 45;

        spi_transfer_data.checksum = 0x20;


        return spi_transfer_data;

    }

    CONTROL_DATA_FORMAT& operator =(const SPI_TRANSFER_FORMAT& SpiData)
    {

        int index = 0;

        for(int i=0; i<45; i++)
            garbage1[i] = SpiData.data[i + index];

        index += 45;

        mode = SpiData.data[index++];

        x_position = (SpiData.data[index++]);
        x_position |= (SpiData.data[index++] << 8);
        x_position |= (SpiData.data[index++] << 16);
        x_position |= (SpiData.data[index++] << 24);

        y_position = (SpiData.data[index++]);
        y_position |= (SpiData.data[index++] << 8);
        y_position |= (SpiData.data[index++] << 16);
        y_position |= (SpiData.data[index++] << 24);

        z_position = (SpiData.data[index++]);
        z_position |= (SpiData.data[index++] << 8);
        z_position |= (SpiData.data[index++] << 16);
        z_position |= (SpiData.data[index++] << 24);

        step_motor1_direction = SpiData.data[index++];
        step_motor2_direction = SpiData.data[index++];
        step_motor3_direction = SpiData.data[index++];
        step_motor4_direction = SpiData.data[index++];
        servo_motor1_direction = SpiData.data[index++];
        servo_motor2_direction = SpiData.data[index++];

        step_motor1_speed = SpiData.data[index++];
        step_motor2_speed = SpiData.data[index++];
        step_motor3_speed = SpiData.data[index++];
        step_motor4_speed = SpiData.data[index++];
        servo_motor1_degree = SpiData.data[index++];
        servo_motor2_degree = SpiData.data[index++];

        calibrate_sensor = SpiData.data[index++];


        for(int i=0; i<45; i++)
            garbage2[i] = SpiData.data[i + index];


        is_transmitted = true;


        return *this;

    }

    void clear()
    {
        mode = 0;

        step_motor1_direction = 0;
        step_motor2_direction = 0;
        step_motor3_direction = 0;
        step_motor4_direction = 0;

        step_motor1_speed = 0;
        step_motor2_speed = 0;
        step_motor3_speed = 0;
        step_motor4_speed = 0;

        servo_motor1_degree = 0;
        servo_motor1_degree = 0;

        calibrate_sensor = 0;

        is_transmitted = false;
    }

};


struct UDP_DATA_FORMAT
{
    uint16_t header;
    unsigned char data[ETHERNET_ENTITY_SIZE];
    uint16_t checksum;


//    operator SPI_TRANSFER_FORMAT()
//    {
//        SPI_TRANSFER_FORMAT spi_data;

//        int index = 0;

//        spi_data.header = data[index++];
//        spi_data.header |= data[index++] << 8;

//        for(int i = 0; i<SPI_DATA_SIZE; i++ )
//            spi_data.data[i] = data[i + index];

//        index += SPI_DATA_SIZE;

//        spi_data.checksum = data[index++];
//        spi_data.checksum |= data[index++];

//        return spi_data;


//    }

    UDP_DATA_FORMAT& operator = (SPI_TRANSFER_FORMAT &SpiData)
    {

        int index = 0;

        header = 'S';
        header |= 'P' << 8;

        data[index++] = SpiData.header & 0xff;
        data[index++] = (SpiData.header >> 8) & 0xff;

        for(int i=0; i<SPI_DATA_SIZE; i++)
            data[i + index] = SpiData.data[i];

        index += SPI_DATA_SIZE;

        data[index++] = SpiData.checksum & 0xff;
        data[index++] = (SpiData.checksum >> 8) & 0xff;

        return *this;

    }


    UDP_DATA_FORMAT& operator = (unsigned char * Data)
    {

        int index = 0;

        header =  Data[index++];
        header |=  (Data[index++] << 8);

        for(int i=0; i<ETHERNET_ENTITY_SIZE; i++)
            data[i] = Data[i + index];

        index += ETHERNET_ENTITY_SIZE;

        checksum = Data[index++];
        checksum |= Data[index++] << 8;

        return *this;

    }

    operator unsigned char*()
    {
        int index = 0;

        unsigned char * data_all = new unsigned char[ETHERNET_TRANSFER_SIZE];

        data_all[index++] = header & 0xff;
        data_all[index++] = (header >> 8) & 0xff;

        for(int i = 0; i<ETHERNET_ENTITY_SIZE; i++)
            data_all[index + i] = data[i];

        index += ETHERNET_ENTITY_SIZE;

        data_all[index++] = checksum & 0xff;
        data_all[index++] = (checksum >> 8) & 0xff;

        return data_all;
    }



};


struct STREAM_DATA_FORMAT
{
    int total_pack;
    int current_pack;
    unsigned char data[STREAM_DATA_SIZE];

    bool data_correct;

    STREAM_DATA_FORMAT& operator = (UDP_DATA_FORMAT Data)
    {

        int index = 0;

        total_pack = (Data.data[index++] & 0xff);
        total_pack |= ((Data.data[index++] & 0xff) << 8);
        total_pack |= ((Data.data[index++] & 0xff) << 16);
        total_pack |= ((Data.data[index++] & 0xff) << 24);

        current_pack = (Data.data[index++] & 0xff) ;
        current_pack |= ((Data.data[index++] & 0xff) << 8);
        current_pack |= ((Data.data[index++] & 0xff) << 16);
        current_pack |= ((Data.data[index++] & 0xff) << 24);

       for(int i = 0; i<STREAM_DATA_SIZE; i++)
           data[i] = Data.data[i + index];

       return *this;
    }

    operator UDP_DATA_FORMAT()
    {
        UDP_DATA_FORMAT udp_data;

        int index = 0;

        udp_data.header = ('S' | 'T' << 8);

        udp_data.data[index++] = total_pack & 0xff;
        udp_data.data[index++] = (total_pack >> 8) & 0xff;
        udp_data.data[index++] = (total_pack >> 16) & 0xff;
        udp_data.data[index++] = (total_pack >> 24) & 0xff;

        udp_data.data[index++] = current_pack & 0xff;
        udp_data.data[index++] = (current_pack >> 8) & 0xff;
        udp_data.data[index++] = (current_pack >> 16) & 0xff;
        udp_data.data[index++] = (current_pack >> 24) & 0xff;

        for(int i=0; i<STREAM_DATA_SIZE; i++)
            udp_data.data[index + i] = data[i];

        udp_data.checksum = 0;

        return udp_data;
    }
};


struct INFORMATION_DATA_FORMAT
{
    CONTROL_DATA_FORMAT control_data;
    ENVIRONMENT_DATA_FORMAT environment_data;
    SFP_DATA_FORMAT sfp_data;


    operator UDP_DATA_FORMAT()
    {
        UDP_DATA_FORMAT udp_data;

        int index = 0;
        unsigned char *controldata_bytes = (unsigned char *)(SPI_TRANSFER_FORMAT)control_data;
        unsigned char *environmentdata_bytes = (unsigned char *)(SPI_TRANSFER_FORMAT)environment_data;
        unsigned char *sfpdata_bytes = (unsigned char *) sfp_data;

        udp_data.header = 'I';
        udp_data.header |= 'N' << 8;

        for(int i = 0; i<SPI_TRANSFER_SIZE; i++)
            udp_data.data[i + index] = controldata_bytes[i];

        index += SPI_TRANSFER_SIZE;


        for(int i = 0; i<SPI_TRANSFER_SIZE; i++)
            udp_data.data[i + index] = environmentdata_bytes[i];

        index += SPI_TRANSFER_SIZE;


        for(int i = 0; i<SFP_DATA_SIZE; i++)
            udp_data.data[i + index] = sfpdata_bytes[i];

        index += SFP_DATA_SIZE;



        udp_data.checksum = 2;

        delete controldata_bytes;
        delete environmentdata_bytes;
        delete sfpdata_bytes;

        return udp_data;
    }

    INFORMATION_DATA_FORMAT& operator = (UDP_DATA_FORMAT UdpData)
    {
        SPI_TRANSFER_FORMAT temp_data;
        int index = 0;

        temp_data = &UdpData.data[index];
        control_data = temp_data;
        index += SPI_TRANSFER_SIZE;

        temp_data = &UdpData.data[index];
        environment_data = temp_data;
        index += SPI_TRANSFER_SIZE;

        sfp_data = &UdpData.data[index];

        index += SFP_DATA_SIZE;

        return *this;

    }


};

#endif // DATATYPES_H
