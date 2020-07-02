#ifndef SPIDATATYPES_H
#define SPIDATATYPES_H

#include <iostream>

#include <sstream>
#include <cstdarg>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <fstream>
#include <memory.h>
#include <map>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>


#include "config.h"
#define VARNAME(Variable) (#Variable)


struct SFP_DATA_FORMAT
{
    float sfp_temperature;
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


        sfp_temperature = (float)temp_temperature / 100000;
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
        int temp_temperature = sfp_temperature * 100000;
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


    void serializeJson(rapidjson::Writer<rapidjson::StringBuffer> &JsonWriter) const
    {
        JsonWriter.Key(VARNAME(status));
        JsonWriter.String(status ? "Connected":"Disconnected");

        JsonWriter.Key(VARNAME(sfp_temperature));
        JsonWriter.Int(sfp_temperature);

        JsonWriter.Key(VARNAME(vcc));
        JsonWriter.Double(vcc);

        JsonWriter.Key(VARNAME(tx_bias));
        JsonWriter.Double(tx_bias);

        JsonWriter.Key(VARNAME(tx_power));
        JsonWriter.Double(tx_power);

        JsonWriter.Key(VARNAME(rx_power));
        JsonWriter.Double(rx_power);

    }

    void parseJson(const rapidjson::Value &JsonObject)
    {

        if(JsonObject.HasMember(VARNAME(status)))
            if(JsonObject[VARNAME(status)].GetString() == "Connected")
                status = 1;
            else
                status = 0;

        if(JsonObject.HasMember(VARNAME(sfp_temperature)))
            sfp_temperature = JsonObject[VARNAME(sfp_temperature)].GetInt();

        if(JsonObject.HasMember(VARNAME(vcc)))
            vcc = JsonObject[VARNAME(vcc)].GetDouble();

        if(JsonObject.HasMember(VARNAME(tx_bias)))
            tx_bias = JsonObject[VARNAME(tx_bias)].GetDouble();

        if(JsonObject.HasMember(VARNAME(tx_power)))
            tx_power = JsonObject[VARNAME(tx_power)].GetDouble();

        if(JsonObject.HasMember(VARNAME(rx_power)))
            rx_power = JsonObject[VARNAME(rx_power)].GetDouble();

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
        unsigned char *data = new unsigned char[SENSOR_DATA_SIZE];

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

    void serializeJson(rapidjson::Writer<rapidjson::StringBuffer> &JsonWriter) const
    {

        JsonWriter.Key(VARNAME(temperature));
        JsonWriter.Int(temperature);

        JsonWriter.Key(VARNAME(compass_degree));
        JsonWriter.Int(compass_degree);

        JsonWriter.Key(VARNAME(pressure));
        JsonWriter.Int(pressure);

        JsonWriter.Key(VARNAME(altitude));
        JsonWriter.Int(altitude);

        JsonWriter.Key(VARNAME(wheather_condition));
        JsonWriter.Int(wheather_condition);

    }

    void parseJson(rapidjson::Value &JsonObject)
    {

        if(JsonObject.HasMember(VARNAME(temperature)))
            temperature = JsonObject[VARNAME(temperature)].GetInt();

        if(JsonObject.HasMember(VARNAME(compass_degree)))
            compass_degree = JsonObject[VARNAME(compass_degree)].GetInt();

        if(JsonObject.HasMember(VARNAME(pressure)))
            pressure = JsonObject[VARNAME(pressure)].GetInt();

        if(JsonObject.HasMember(VARNAME(altitude)))
            altitude = JsonObject[VARNAME(altitude)].GetInt();

        if(JsonObject.HasMember(VARNAME(wheather_condition)))
            wheather_condition = JsonObject[VARNAME(wheather_condition)].GetInt();

    }
};


struct GYROSCOPE_DATA_FORMAT
{
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;

    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;

    int16_t mag_x;
    int16_t mag_y;
    int16_t mag_z;

    int16_t temp;


    operator unsigned char*()
    {
        unsigned char *raw_data = new unsigned char[GYROSCOPE_DATA_SIZE];
        int index = 0;

        raw_data[index++] = accel_x & 0xff;
        raw_data[index++] = (accel_x >> 8) & 0xff;

        raw_data[index++] = accel_y & 0xff;
        raw_data[index++] = (accel_y >> 8) & 0xff;

        raw_data[index++] = accel_z & 0xff;
        raw_data[index++] = (accel_z >> 8) & 0xff;

        raw_data[index++] = gyro_x & 0xff;
        raw_data[index++] = (gyro_x >> 8) & 0xff;

        raw_data[index++] = gyro_y & 0xff;
        raw_data[index++] = (gyro_y >> 8) & 0xff;

        raw_data[index++] = gyro_z & 0xff;
        raw_data[index++] = (gyro_z >> 8) & 0xff;

        raw_data[index++] = mag_x & 0xff;
        raw_data[index++] = (mag_x >> 8) & 0xff;

        raw_data[index++] = mag_y & 0xff;
        raw_data[index++] = (mag_y >> 8) & 0xff;

        raw_data[index++] = mag_z & 0xff;
        raw_data[index++] = (mag_z >> 8) & 0xff;

        raw_data[index++] = temp & 0xff;
        raw_data[index++] = (temp >> 8) & 0xff;

        return raw_data;
    }

    GYROSCOPE_DATA_FORMAT& operator = (unsigned char* RawData)
    {
        int index = 0;

        accel_x = RawData[index++];
        accel_x |= RawData[index++] << 8;

        accel_y = RawData[index++];
        accel_y |= RawData[index++] << 8;

        accel_z = RawData[index++];
        accel_z |= RawData[index++] << 8;

        gyro_x = RawData[index++];
        gyro_x |= RawData[index++] << 8;

        gyro_y = RawData[index++];
        gyro_y |= RawData[index++] << 8;

        gyro_z = RawData[index++];
        gyro_z |= RawData[index++] << 8;

        mag_x = RawData[index++];
        mag_x |= RawData[index++] << 8;

        mag_y = RawData[index++];
        mag_y |= RawData[index++] << 8;

        mag_z = RawData[index++];
        mag_z |= RawData[index++] << 8;

        temp = RawData[index++];
        temp |= RawData[index++] << 8;

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

    void serializeJson(rapidjson::Writer<rapidjson::StringBuffer> &JsonWriter) const
    {

        JsonWriter.Key(VARNAME(latitude));
        JsonWriter.Double(latitude);

        JsonWriter.Key(VARNAME(sfp_temp));
        JsonWriter.String((const char *)&ns_indicator);

        JsonWriter.Key(VARNAME(longnitude));
        JsonWriter.Double(longnitude);

        JsonWriter.Key(VARNAME(we_indicator));
        JsonWriter.String((const char *)&we_indicator);


    }

    void parseJson(rapidjson::Value &JsonObject)
    {

        if(JsonObject.HasMember(VARNAME(latitude)))
            latitude = JsonObject[VARNAME(latitude)].GetDouble();

//        if(JsonObject.HasMember(VARNAME(ns_indicator)))
//            ns_indicator = JsonObject[VARNAME(ns_indicator)].GetString();

        if(JsonObject.HasMember(VARNAME(longnitude)))
            longnitude = JsonObject[VARNAME(longnitude)].GetDouble();

//        if(JsonObject.HasMember(VARNAME(we_indicator)))
//            we_indicator = (unsigned char)JsonObject[VARNAME(we_indicator)].GetString();

    }
};


struct SPI_TRANSFER_FORMAT
{

    enum HEADER
    {
        CONTROL_DATA = 0x2222,
        ENVIRONMENT_DATA = 0x2223,
        GYROSCOPE_DATA = 0x2224,
        UPDATE_FILE = 0x5055
    };

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
    GYROSCOPE_DATA_FORMAT gyroscope_data;
    uint8_t step_motor_breaks;

    std::string gps_string;


    ENVIRONMENT_DATA_FORMAT()
    {

    }

    operator SPI_TRANSFER_FORMAT()
    {
        SPI_TRANSFER_FORMAT spi_data;
        int index = 0;


        spi_data.header = SPI_TRANSFER_FORMAT::ENVIRONMENT_DATA;

        for(int i = 0; i<GPS_STRING_SIZE; i++)
            spi_data.data[index++] = gps_string.c_str()[i];

        spi_data.data[index++] = step_motor1_step & 0xff;
        spi_data.data[index++] = (step_motor1_step >> 8) & 0xff;
        spi_data.data[index++] = (step_motor1_step >> 16) & 0xff;
        spi_data.data[index++] = (step_motor1_step >> 24) & 0xff;

        spi_data.data[index++] = step_motor2_step & 0xff;
        spi_data.data[index++] = (step_motor2_step >> 8) & 0xff;
        spi_data.data[index++] = (step_motor2_step >> 16) & 0xff;
        spi_data.data[index++] = (step_motor2_step >> 24) & 0xff;

        spi_data.data[index++] = servo_motor1_degree & 0xff;
        spi_data.data[index++] = servo_motor2_degree & 0xff;

        memcpy(spi_data.data + index, sensor_data, SENSOR_DATA_SIZE);
        index += SENSOR_DATA_SIZE;

        memcpy(spi_data.data + index, gyroscope_data, GYROSCOPE_DATA_SIZE);
        index += GYROSCOPE_DATA_SIZE;

        spi_data.data[index++] = step_motor_breaks;

        spi_data.checksum = 0;



        return spi_data;

    }

    ENVIRONMENT_DATA_FORMAT& operator = (const SPI_TRANSFER_FORMAT& SpiData)
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

            if(SpiData.data[index] != 0)
                servo_motor1_degree = SpiData.data[index++];
            else
                index++;

            if(SpiData.data[index] != 0)
                servo_motor2_degree = SpiData.data[index++];
            else
                index++;

            sensor_data = (unsigned char *)&SpiData.data[index];
            index += SENSOR_DATA_SIZE;

            gyroscope_data = (unsigned char *)&SpiData.data[index];
            index += GYROSCOPE_DATA_SIZE;

            step_motor_breaks = SpiData.data[index++];

        }
        catch(std::exception& ex)
        {
            std::cout << "SPI_TX_FORMAT exception: " << ex.what() << std::endl;
        }

        return *this;
    }

    void serializeJson(rapidjson::Writer<rapidjson::StringBuffer> &JsonWriter) const
    {


        JsonWriter.Key(VARNAME(gps_string));
        JsonWriter.String(gps_string.c_str());

        gps_data.serializeJson(JsonWriter);
        sensor_data.serializeJson(JsonWriter);


    }

    void parseJson(rapidjson::Value &JsonObject)
    {
        if(JsonObject.HasMember(VARNAME(gps_string)))
            gps_string = JsonObject[VARNAME(gps_string)].GetString();

        gps_data.parseJson(JsonObject);
        sensor_data.parseJson(JsonObject);
    }

    void move(ENVIRONMENT_DATA_FORMAT &EnvironmentData)
    {
        gps_data = EnvironmentData.gps_data;
        sensor_data = EnvironmentData.sensor_data;
        step_motor_breaks = EnvironmentData.step_motor_breaks;
        gps_string = EnvironmentData.gps_string;
        gyroscope_data = EnvironmentData.gyroscope_data;

        if(EnvironmentData.servo_motor1_degree != 0xFF && EnvironmentData.servo_motor1_degree != 0)
            servo_motor1_degree = EnvironmentData.servo_motor1_degree;

        if(EnvironmentData.servo_motor2_degree != 0xFF && EnvironmentData.servo_motor2_degree != 0)
            servo_motor2_degree = EnvironmentData.servo_motor2_degree;

        if(EnvironmentData.step_motor1_step != 0xFFFF)
            step_motor1_step = EnvironmentData.step_motor1_step;

        if(EnvironmentData.step_motor2_step != 0xFFFF)
            step_motor2_step = EnvironmentData.step_motor2_step;

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

    operator SPI_TRANSFER_FORMAT() const
    {
        int checksum = 0;

        SPI_TRANSFER_FORMAT spi_transfer_format;


        spi_transfer_format.header =  SPI_TRANSFER_FORMAT::UPDATE_FILE;


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


    uint8_t garbage1[CONTROL_DATA_GARBAGE_SIZE]; // header

    uint8_t setting_enable;

    uint32_t x_position;
    uint32_t y_position;
    uint32_t z_position;

    uint8_t step_motor1_direction;
    uint8_t step_motor2_direction;

    uint8_t step_motor1_speed;
    uint8_t step_motor2_speed;

    uint8_t servo_motor1_degree;
    uint8_t servo_motor1_top_degree;
    uint8_t servo_motor1_bottom_degree;

    uint8_t servo_motor2_degree;
    uint8_t servo_motor2_top_degree;
    uint8_t servo_motor2_bottom_degree;

    uint8_t calibrate_sensor;

    uint32_t step_motor1_step;
    uint32_t step_motor1_max_step;

    uint32_t step_motor2_step;
    uint32_t step_motor2_max_step;


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

        setting_enable = SpiData.data[index++];

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

        step_motor1_speed = SpiData.data[index++];
        step_motor2_speed = SpiData.data[index++];

        servo_motor1_degree = SpiData.data[index++];
        servo_motor1_top_degree = SpiData.data[index++];
        servo_motor1_bottom_degree = SpiData.data[index++];

        servo_motor2_degree = SpiData.data[index++];
        servo_motor2_top_degree = SpiData.data[index++];
        servo_motor2_bottom_degree = SpiData.data[index++];

        step_motor1_step = (SpiData.data[index++]);
        step_motor1_step |= (SpiData.data[index++] << 8);
        step_motor1_step |= (SpiData.data[index++] << 16);
        step_motor1_step |= (SpiData.data[index++] << 24);

        step_motor1_max_step = (SpiData.data[index++]);
        step_motor1_max_step |= (SpiData.data[index++] << 8);
        step_motor1_max_step |= (SpiData.data[index++] << 16);
        step_motor1_max_step |= (SpiData.data[index++] << 24);

        step_motor2_step = (SpiData.data[index++]);
        step_motor2_step |= (SpiData.data[index++] << 8);
        step_motor2_step |= (SpiData.data[index++] << 16);
        step_motor2_step |= (SpiData.data[index++] << 24);

        step_motor2_max_step = (SpiData.data[index++]);
        step_motor2_max_step |= (SpiData.data[index++] << 8);
        step_motor2_max_step |= (SpiData.data[index++] << 16);
        step_motor2_max_step |= (SpiData.data[index++] << 24);

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


    operator SPI_TRANSFER_FORMAT() const
    {

        SPI_TRANSFER_FORMAT spi_transfer_data;

        int index = 0;

        spi_transfer_data.header = SPI_TRANSFER_FORMAT::CONTROL_DATA;

        for(int i=0; i<CONTROL_DATA_GARBAGE_SIZE; i++)
            spi_transfer_data.data[i + index] = garbage1[i];

        index += CONTROL_DATA_GARBAGE_SIZE;

        spi_transfer_data.data[index++] = setting_enable;

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

        spi_transfer_data.data[index++] = step_motor1_speed;
        spi_transfer_data.data[index++] = step_motor2_speed;

        spi_transfer_data.data[index++] = servo_motor1_degree;
        spi_transfer_data.data[index++] = servo_motor1_top_degree;
        spi_transfer_data.data[index++] = servo_motor1_bottom_degree;

        spi_transfer_data.data[index++] = servo_motor2_degree;
        spi_transfer_data.data[index++] = servo_motor2_top_degree;
        spi_transfer_data.data[index++] = servo_motor2_bottom_degree;

        spi_transfer_data.data[index++] = calibrate_sensor;

        spi_transfer_data.data[index++] = (step_motor1_step) & 0xff;
        spi_transfer_data.data[index++] = (step_motor1_step >> 8) & 0xff;
        spi_transfer_data.data[index++] = (step_motor1_step >> 16) & 0xff;
        spi_transfer_data.data[index++] = (step_motor1_step >> 24) & 0xff;

        spi_transfer_data.data[index++] = (step_motor1_max_step) & 0xff;
        spi_transfer_data.data[index++] = (step_motor1_max_step >> 8) & 0xff;
        spi_transfer_data.data[index++] = (step_motor1_max_step >> 16) & 0xff;
        spi_transfer_data.data[index++] = (step_motor1_max_step >> 24) & 0xff;


        spi_transfer_data.data[index++] = (step_motor2_step) & 0xff;
        spi_transfer_data.data[index++] = (step_motor2_step >> 8) & 0xff;
        spi_transfer_data.data[index++] = (step_motor2_step >> 16) & 0xff;
        spi_transfer_data.data[index++] = (step_motor2_step >> 24) & 0xff;

        spi_transfer_data.data[index++] = (step_motor2_max_step) & 0xff;
        spi_transfer_data.data[index++] = (step_motor2_max_step >> 8) & 0xff;
        spi_transfer_data.data[index++] = (step_motor2_max_step >> 16) & 0xff;
        spi_transfer_data.data[index++] = (step_motor2_max_step >> 24) & 0xff;


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

        setting_enable = SpiData.data[index++];

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

        step_motor1_speed = SpiData.data[index++];
        step_motor2_speed = SpiData.data[index++];

        servo_motor1_degree = SpiData.data[index++];
        servo_motor1_top_degree = SpiData.data[index++];
        servo_motor1_bottom_degree = SpiData.data[index++];

        servo_motor2_degree = SpiData.data[index++];
        servo_motor2_top_degree = SpiData.data[index++];
        servo_motor2_bottom_degree = SpiData.data[index++];

        calibrate_sensor = SpiData.data[index++];

        step_motor1_step = (SpiData.data[index++]);
        step_motor1_step |= (SpiData.data[index++] << 8);
        step_motor1_step |= (SpiData.data[index++] << 16);
        step_motor1_step |= (SpiData.data[index++] << 24);

        step_motor1_max_step = (SpiData.data[index++]);
        step_motor1_max_step |= (SpiData.data[index++] << 8);
        step_motor1_max_step |= (SpiData.data[index++] << 16);
        step_motor1_max_step |= (SpiData.data[index++] << 24);

        step_motor2_step = (SpiData.data[index++]);
        step_motor2_step |= (SpiData.data[index++] << 8);
        step_motor2_step |= (SpiData.data[index++] << 16);
        step_motor2_step |= (SpiData.data[index++] << 24);

        step_motor2_max_step = (SpiData.data[index++]);
        step_motor2_max_step |= (SpiData.data[index++] << 8);
        step_motor2_max_step |= (SpiData.data[index++] << 16);
        step_motor2_max_step |= (SpiData.data[index++] << 24);


        for(int i=0; i<CONTROL_DATA_GARBAGE_SIZE; i++)
            garbage2[i] = SpiData.data[i + index];

        index += CONTROL_DATA_GARBAGE_SIZE;

        is_transmitted = true;


        return *this;

    }

    void clear()
    {
        setting_enable = 0;

        x_position = 0;
        y_position = 0;

        step_motor1_direction = 0;
        step_motor2_direction = 0;

        step_motor1_speed = 0;
        step_motor2_speed = 0;

        servo_motor1_degree = 0;
        servo_motor2_degree = 0;

        calibrate_sensor = 0;

        step_motor1_step = 0;
        step_motor2_step = 0;

        is_transmitted = false;
    }

};



#endif // SPIDATATYPES_H
