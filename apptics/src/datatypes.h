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
#define CONTROL_DATA_GARBAGE_SIZE 41
#define GPS_STRING_SIZE 87

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
        unsigned char *data = new unsigned char[SFP_DATA_SIZE];
        int index = 0;
        u_int32_t temp_temperature = (u_int32_t)(temperature * 100000);
        u_int32_t temp_vcc = (u_int32_t)(vcc * 100000);
        u_int32_t temp_tx_bias = (u_int32_t)(tx_bias * 100000);
        u_int32_t temp_tx_power = (u_int32_t)(tx_power * 100000);
        u_int32_t temp_rx_power = (u_int32_t)(rx_power * 100000);


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

        int index = 0;
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

            index++;

            if(!token[index].empty())
                utc_time = (double)std::atof(token[index].c_str());

            index++;

            if(!token[index].empty())
                status = (unsigned char)*token[index].c_str();

            index++;

            if(!token[index].empty())
            {
                degrees = (double)std::atof(token[index].substr(0, 2).c_str());
                minutes = (double)std::atof(token[index].substr(2, 7).c_str());
                latitude =  degrees + (minutes / 60);
            }

            index++;

            if(!token[index].empty())
                ns_indicator = (unsigned char)*token[4].c_str();

            index++;

            if(!token[index].empty())
            {
                degrees = (double)std::atof(token[index].substr(0, 3).c_str());
                minutes = (double)std::atof(token[index].substr(3, 7).c_str());
                longnitude = degrees + (minutes / 60);
            }

            index++;

            if(!token[index].empty())
                we_indicator = (unsigned char)*token[index].c_str();

            index++;

            if(!token[index].empty())
                speed_over_ground = (double)std::atof(token[index].c_str());

            index++;

            if(!token[index].empty())
                course_over_ground =(double)std::atof(token[index].c_str());

            index++;

            if(!token[index].empty())
                date = token[index];

            index++;

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

    uint32_t step_motor1_step;
    uint32_t step_motor2_step;

    uint16_t servo_motor1_degree;
    uint16_t servo_motor2_degree;

    SENSOR_DATA sensor_data;


    std::string gps_string;

    ENVIRONMENT_DATA_FORMAT()
    {

    }

    ENVIRONMENT_DATA_FORMAT(SPI_TRANSFER_FORMAT SpiData)
    {
        try
        {
            int index = 0;

            gps_string = std::string(&SpiData.data[0], &SpiData.data[GPS_STRING_SIZE - 1]);
            gps_data = gps_string;
            index += GPS_STRING_SIZE;

            step_motor1_step = SpiData.data[index++];
            step_motor1_step |= SpiData.data[index++] << 8;
            step_motor1_step |= SpiData.data[index++] << 16;
            step_motor1_step |= SpiData.data[index++] << 24;

            step_motor2_step = SpiData.data[index++];
            step_motor2_step |= SpiData.data[index++] << 8;
            step_motor2_step |= SpiData.data[index++] << 16;
            step_motor2_step |= SpiData.data[index++] << 24;

            servo_motor1_degree = SpiData.data[index++];
            servo_motor1_degree |= SpiData.data[index++] << 8;

            servo_motor2_degree = SpiData.data[index++];
            servo_motor2_degree |= SpiData.data[index++] << 8;

            sensor_data = &SpiData.data[index];

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
        spi_data.header |= 'N' << 8;



        for(int i = 0; i<GPS_STRING_SIZE; i++)
            spi_data.data[i + index] = gps_string.c_str()[i];

        index += GPS_STRING_SIZE;

        spi_data.data[index++] = step_motor1_step & 0xff;
        spi_data.data[index++] = (step_motor1_step >> 8) & 0xff;
        spi_data.data[index++] = (step_motor1_step >> 16) & 0xff;
        spi_data.data[index++] = (step_motor1_step >> 24) & 0xff;

        spi_data.data[index++] = step_motor2_step & 0xff;
        spi_data.data[index++] = (step_motor2_step >> 8) & 0xff;
        spi_data.data[index++] = (step_motor2_step >> 16) & 0xff;
        spi_data.data[index++] = (step_motor2_step >> 24) & 0xff;

        spi_data.data[index++] = servo_motor1_degree & 0xff;
        spi_data.data[index++] = (servo_motor1_degree >> 8) & 0xff;

        spi_data.data[index++] = servo_motor2_degree & 0xff;
        spi_data.data[index++] = (servo_motor2_degree >> 8) & 0xff;

        sensor_data_pointer = sensor_data;

        memcpy(&spi_data.data[index], sensor_data_pointer, sizeof(SENSOR_DATA));

        index += sizeof(SENSOR_DATA);

        spi_data.checksum = 0;

        delete sensor_data_pointer;


        return spi_data;

    }

    ENVIRONMENT_DATA_FORMAT& operator = (SPI_TRANSFER_FORMAT& SpiData)
    {

        try
        {
            int index = 0;

            gps_string = std::string(&SpiData.data[0], &SpiData.data[GPS_STRING_SIZE - 1]);
            gps_data = gps_string;
            index += GPS_STRING_SIZE;

            step_motor1_step = SpiData.data[index++];
            step_motor1_step |= SpiData.data[index++] << 8;
            step_motor1_step |= SpiData.data[index++] << 16;
            step_motor1_step |= SpiData.data[index++] << 24;

            step_motor2_step = SpiData.data[index++];
            step_motor2_step |= SpiData.data[index++] << 8;
            step_motor2_step |= SpiData.data[index++] << 16;
            step_motor2_step |= SpiData.data[index++] << 24;

            servo_motor1_degree = SpiData.data[index++];
            servo_motor1_degree |= SpiData.data[index++] << 8;

            servo_motor2_degree = SpiData.data[index++];
            servo_motor2_degree |= SpiData.data[index++] << 8;

            sensor_data = &SpiData.data[index];

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
        int index = 0;

        SPI_TRANSFER_FORMAT spi_transfer_format;


        spi_transfer_format.header =  'U' | 'P' << 8;


        spi_transfer_format.data[index++] = (total_sequence_number) & 0xff;
        spi_transfer_format.data[index++] = (total_sequence_number >> 8) & 0xff;
        spi_transfer_format.data[index++] = (total_sequence_number >> 16) & 0xff;
        spi_transfer_format.data[index++] = (total_sequence_number >> 24) & 0xff;

        spi_transfer_format.data[index++] = (current_sequence_number) & 0xff;
        spi_transfer_format.data[index++] = (current_sequence_number >> 8) & 0xff;
        spi_transfer_format.data[index++] = (current_sequence_number >> 16) & 0xff;
        spi_transfer_format.data[index++] = (current_sequence_number >> 24) & 0xff;

        for(int i=0; i<SPI_ENTITY_SIZE; i++)
          spi_transfer_format.data[i + index] = data[i];

        index += SPI_ENTITY_SIZE;

        for(int i=0; i<SPI_ENTITY_SIZE; i++)
            checksum += data[i];

        spi_transfer_format.checksum = checksum;


        return spi_transfer_format;

    }

    UPDATE_FILE_FORMAT& operator =(const SPI_TRANSFER_FORMAT& SpiData)
    {

        int index = 0;

        total_sequence_number = (SpiData.data[index++]);
        total_sequence_number |= (SpiData.data[index++] << 8);
        total_sequence_number |= (SpiData.data[index++] << 16);
        total_sequence_number |= (SpiData.data[index++] << 24);

        current_sequence_number = (SpiData.data[index++]);
        current_sequence_number |= (SpiData.data[index++] << 8);
        current_sequence_number |= (SpiData.data[index++] << 16);
        current_sequence_number |= (SpiData.data[index++] << 24);

        for(int i=0; i<SPI_ENTITY_SIZE; i++)
            data[i] = SpiData.data[i + index];

        index += SPI_ENTITY_SIZE;

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


    uint8_t garbage1[CONTROL_DATA_GARBAGE_SIZE]; // header

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

    uint32_t step_motor1_step;
    uint32_t step_motor2_step;

    uint8_t garbage2[CONTROL_DATA_GARBAGE_SIZE]; //footer

    volatile bool is_transmitted;
    volatile bool is_available;

    operator bool()
    {
        return is_transmitted;
    }

    CONTROL_DATA_FORMAT(){}

    CONTROL_DATA_FORMAT(SPI_TRANSFER_FORMAT SpiData)
    {
        int index = 0;

        for(int i=0; i<CONTROL_DATA_GARBAGE_SIZE; i++)
            garbage1[i] = SpiData.data[i + index];

        index += CONTROL_DATA_GARBAGE_SIZE;

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

        step_motor1_step = (SpiData.data[index++]);
        step_motor1_step |= (SpiData.data[index++] << 8);
        step_motor1_step |= (SpiData.data[index++] << 16);
        step_motor1_step |= (SpiData.data[index++] << 24);

        step_motor2_step = (SpiData.data[index++]);
        step_motor2_step |= (SpiData.data[index++] << 8);
        step_motor2_step |= (SpiData.data[index++] << 16);
        step_motor2_step |= (SpiData.data[index++] << 24);

        calibrate_sensor = SpiData.data[index++];


        for(int i=0; i<CONTROL_DATA_GARBAGE_SIZE; i++)
            garbage2[i] = SpiData.data[i + index];

        index += CONTROL_DATA_GARBAGE_SIZE;

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

        for(int i=0; i<CONTROL_DATA_GARBAGE_SIZE; i++)
            spi_transfer_data.data[i + index] = garbage1[i];

        index += CONTROL_DATA_GARBAGE_SIZE;

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

        spi_transfer_data.data[index++] = (step_motor1_step) & 0xff;
        spi_transfer_data.data[index++] = (step_motor1_step >> 8) & 0xff;
        spi_transfer_data.data[index++] = (step_motor1_step >> 16) & 0xff;
        spi_transfer_data.data[index++] = (step_motor1_step >> 24) & 0xff;

        spi_transfer_data.data[index++] = (step_motor2_step) & 0xff;
        spi_transfer_data.data[index++] = (step_motor2_step >> 8) & 0xff;
        spi_transfer_data.data[index++] = (step_motor2_step >> 16) & 0xff;
        spi_transfer_data.data[index++] = (step_motor2_step >> 24) & 0xff;

        for(int i=0; i<CONTROL_DATA_GARBAGE_SIZE; i++)
            spi_transfer_data.data[i + index] = garbage2[i];

        index += CONTROL_DATA_GARBAGE_SIZE;

        spi_transfer_data.checksum = 0x20;

        return spi_transfer_data;

    }

    CONTROL_DATA_FORMAT& operator =(const SPI_TRANSFER_FORMAT& SpiData)
    {

        int index = 0;

        for(int i=0; i<CONTROL_DATA_GARBAGE_SIZE; i++)
            garbage1[i] = SpiData.data[i + index];

        index += CONTROL_DATA_GARBAGE_SIZE;

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

        step_motor1_step = SpiData.data[index++];
        step_motor1_step |= SpiData.data[index++] << 8;
        step_motor1_step |= SpiData.data[index++] << 16;
        step_motor1_step |= SpiData.data[index++] << 24;

        step_motor2_step = SpiData.data[index++];
        step_motor2_step |= SpiData.data[index++] << 8;
        step_motor2_step |= SpiData.data[index++] << 16;
        step_motor2_step |= SpiData.data[index++] << 24;


        for(int i=0; i<CONTROL_DATA_GARBAGE_SIZE; i++)
            garbage2[i] = SpiData.data[i + index];

        index += CONTROL_DATA_GARBAGE_SIZE;

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

        step_motor1_step = 0;
        step_motor2_step = 0;

        is_transmitted = false;
    }

};



struct UDP_DATA_FORMAT
{
    uint16_t header;
    unsigned char data[ETHERNET_ENTITY_SIZE];
    uint16_t checksum;


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

        u_int32_t tem;

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
