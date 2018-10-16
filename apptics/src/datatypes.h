#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>

#include <sstream>
#include <cstdarg>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <fstream>

#include <map>

#define SUCCESS 1
#define FAIL 2

#define MAX_LOG_LINE 1000
#define LOG_FILE "/var/www/html/log.txt"


#define SPI_ENTITY_SIZE 108
#define SPI_TRANSFER_SIZE 120
#define SPI_DATA_SIZE 116



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
    int type;
    float temperature;
    float vcc;
    float tx_bias;
    float tx_power;
    float rx_power;
    int status;

};

struct SENSOR_DATA
{
    uint32_t temperature;
    uint32_t compass_degree;
    uint32_t pressure;
    uint32_t altitude;
    uint8_t wheather_condition;

    SENSOR_DATA& operator = (unsigned char *TransferData)
    {
        temperature = TransferData[3] << 24 | TransferData[2] << 16 | TransferData[1] << 8 | TransferData[0] ;
        compass_degree = TransferData[7] << 24 | TransferData[6] << 16 | TransferData[5] << 8 | TransferData[4] ;
        pressure = TransferData[11] << 24 | TransferData[10] << 16 | TransferData[9] << 8 | TransferData[8] ;
        altitude = TransferData[15] << 24 | TransferData[14] << 16 | TransferData[13] << 8 | TransferData[12] ;
        wheather_condition = TransferData[16];

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
        int pos;

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
        catch(std::exception ex)
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


    operator unsigned char*()
    {

        unsigned char *spi_data = new unsigned char[SPI_TRANSFER_SIZE];

        spi_data[0] = header & 0xff;
        spi_data[1] = (header >> 8) & 0xff;

        for(int i = 0; i<SPI_DATA_SIZE; i++)
            spi_data[i + 2 ] = data[i];

        spi_data[118] = checksum & 0xff;
        spi_data[119] = (checksum >> 8) & 0xff;

        return spi_data;

    }

    SPI_TRANSFER_FORMAT& operator =(unsigned char *SpiData)
    {



        header = SpiData[0] | (SpiData[1] << 8);

        for(int i = 2; i<SPI_DATA_SIZE + 2; i++)
            data[i - 2] = SpiData[i];

        checksum = (SpiData[118]) & (SpiData[119] << 8);


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

    ENVIRONMENT_DATA_FORMAT& operator = (SPI_TRANSFER_FORMAT& SpiData)
    {

        try
        {

            gps_string = std::string(&SpiData.data[0], &SpiData.data[98]);

            gps_data = gps_string;

            sensor_data = &SpiData.data[99];

        }
        catch(std::exception ex)
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

    CONTROL_DATA_FORMAT& operator =(bool Var)
    {
        is_transmitted = Var;

        return *this;
    }


    operator SPI_TRANSFER_FORMAT()
    {

        SPI_TRANSFER_FORMAT spi_transfer_data;


        spi_transfer_data.header = ('C' | 'O' << 8);

        for(int i=0; i<45; i++)
        {
            garbage1[i] = 0x20;
            spi_transfer_data.data[i] = garbage1[i];
        }


        spi_transfer_data.data[45] = mode;

        spi_transfer_data.data[46] = (x_position) & 0xff;
        spi_transfer_data.data[47] = (x_position >> 8) & 0xff;
        spi_transfer_data.data[48] = (x_position >> 16) & 0xff;
        spi_transfer_data.data[49] = (x_position >> 24) & 0xff;

        spi_transfer_data.data[50] = (y_position) & 0xff;
        spi_transfer_data.data[51] = (y_position >> 8) & 0xff;
        spi_transfer_data.data[52] = (y_position >> 16) & 0xff;
        spi_transfer_data.data[53] = (y_position >> 24) & 0xff;

        spi_transfer_data.data[54] = (z_position) & 0xff;
        spi_transfer_data.data[55] = (z_position >> 8) & 0xff;
        spi_transfer_data.data[56] = (z_position >> 16) & 0xff;
        spi_transfer_data.data[57] = (z_position >> 24) & 0xff;

        spi_transfer_data.data[58] = step_motor1_direction;
        spi_transfer_data.data[59] = step_motor2_direction;
        spi_transfer_data.data[60] = step_motor3_direction;
        spi_transfer_data.data[61] = step_motor4_direction;
        spi_transfer_data.data[62] = servo_motor1_direction;
        spi_transfer_data.data[63] = servo_motor2_direction;

        spi_transfer_data.data[64] = step_motor1_speed;
        spi_transfer_data.data[65] = step_motor2_speed;
        spi_transfer_data.data[66] = step_motor3_speed;
        spi_transfer_data.data[67] = step_motor4_speed;
        spi_transfer_data.data[68] = servo_motor1_degree;
        spi_transfer_data.data[69] = servo_motor2_degree;

        spi_transfer_data.data[70] = calibrate_sensor;


        for(int i=71; i<118; i++)
        {
            garbage2[i - 71] = 0x20;
            spi_transfer_data.data[i] = garbage2[i];
        }

        spi_transfer_data.checksum = 0x20;


        return spi_transfer_data;

    }

    CONTROL_DATA_FORMAT& operator =(const SPI_TRANSFER_FORMAT& SpiData)
    {

        for(int i=0; i<45; i++)
            garbage1[i] = SpiData.data[i];

        mode = SpiData.data[45];

        x_position = (SpiData.data[46]) | (SpiData.data[47] << 8) | (SpiData.data[48] << 16) | (SpiData.data[49] << 24);
        y_position = (SpiData.data[50]) | (SpiData.data[51] << 8) | (SpiData.data[52] << 16) | (SpiData.data[53] << 24);
        z_position = (SpiData.data[54]) | (SpiData.data[55] << 8) | (SpiData.data[56] << 16) | (SpiData.data[57] << 24);

        step_motor1_direction = SpiData.data[58];
        step_motor2_direction = SpiData.data[59];
        step_motor3_direction = SpiData.data[60];
        step_motor4_direction = SpiData.data[61];
        servo_motor1_direction = SpiData.data[62];
        servo_motor2_direction = SpiData.data[63];

        step_motor1_speed = SpiData.data[64];
        step_motor2_speed = SpiData.data[65];
        step_motor3_speed = SpiData.data[66];
        step_motor4_speed = SpiData.data[67];
        servo_motor1_degree = SpiData.data[68];
        servo_motor2_degree = SpiData.data[69];

        calibrate_sensor = SpiData.data[70];


        for(int i=71; i<118; i++)
            garbage2[i - 71] = SpiData.data[i];


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

struct MOTOR_POSITION_FORMAT
{
    int step_motor1_position;
    int step_motor2_position;
    int servo_motor1_degree;
    int servo_motor2_degree;
};


#endif // DATATYPES_H
