#ifndef ETHERNETDATATYPES_H
#define ETHERNETDATATYPES_H

#include <iostream>

#include <sstream>
#include <cstdarg>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <fstream>
#include <memory.h>
#include <map>

#include "config.h"
#include "spidatatypes.h"



struct UDP_DATA_FORMAT
{

    enum HEADER
    {
        SPI_DATA = 0x1111,
        INFORMATION_DATA_CALLBACK,
        INFORMATION_DATA,
        STREAM_DATA,
        FEEDBACK_DATA,
        CAMERA_SETTING_DATA,
        LASER_SWITCH_REQUEST,
        RF_SWITCH_REQUEST
    };

    uint16_t header;
    unsigned char data[ETHERNET_ENTITY_SIZE];
    uint16_t checksum;


    UDP_DATA_FORMAT& operator = (SPI_TRANSFER_FORMAT &SpiData)
    {

        int index = 0;

        header = SPI_DATA;

        data[index++] = SpiData.header & 0xff;
        data[index++] = (SpiData.header >> 8) & 0xff;

        for(int i=0; i<SPI_DATA_SIZE; i++)
            data[i + index] = SpiData.data[i];

        index += SPI_DATA_SIZE;

        data[index++] = SpiData.checksum & 0xff;
        data[index++] = (SpiData.checksum >> 8) & 0xff;

        checksum = 0x1111;

        return *this;

    }


    UDP_DATA_FORMAT& operator = (std::vector<unsigned char> Data)
    {

        if(Data.size() == ETHERNET_TRANSFER_SIZE)
        {
            int index = 0;

            header =  Data[index++];
            header |=  (Data[index++] << 8);

            for(int i=0; i<ETHERNET_ENTITY_SIZE; i++)
                data[i] = Data[i + index];

            index += ETHERNET_ENTITY_SIZE;

            checksum = Data[index++];
            checksum |= Data[index++] << 8;

        }

        return *this;

    }

    operator std::vector<unsigned char> ()
    {

        std::vector<unsigned char> data_all(ETHERNET_TRANSFER_SIZE);
        int index = 0;

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
    u_int32_t total_pack;
    u_int32_t current_pack;
    unsigned char data[STREAM_DATA_SIZE];

    bool is_available = false;
    bool data_correct;


    STREAM_DATA_FORMAT& operator = (UDP_DATA_FORMAT& UdpData)
    {

        int index = 0;

        total_pack = (UdpData.data[index++] & 0xff);
        total_pack |= ((UdpData.data[index++] & 0xff) << 8);
        total_pack |= ((UdpData.data[index++] & 0xff) << 16);
        total_pack |= ((UdpData.data[index++] & 0xff) << 24);

        current_pack = (UdpData.data[index++] & 0xff) ;
        current_pack |= ((UdpData.data[index++] & 0xff) << 8);
        current_pack |= ((UdpData.data[index++] & 0xff) << 16);
        current_pack |= ((UdpData.data[index++] & 0xff) << 24);

       for(int i = 0; i<STREAM_DATA_SIZE; i++)
           data[i] = UdpData.data[i + index];

       return *this;
    }

    operator UDP_DATA_FORMAT()
    {
        UDP_DATA_FORMAT udp_data;

        int index = 0;

        udp_data.header = UDP_DATA_FORMAT::STREAM_DATA;

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

        udp_data.checksum = 0x1111;

        return udp_data;
    }


    void clear()
    {
        total_pack = -1;
        current_pack = 0;

        for(int i=0; i<STREAM_DATA_SIZE; i++)
            data[i] = 0;

        is_available = false;
    }

};



struct INFORMATION_DATA_FORMAT
{
    CONTROL_DATA_FORMAT control_data;
    ENVIRONMENT_DATA_FORMAT environment_data;
    SFP_DATA_FORMAT sfp_data;

    bool is_available = false;

    operator UDP_DATA_FORMAT()
    {
        UDP_DATA_FORMAT udp_data;


        int index = 0;
        unsigned char *controldata_bytes = (unsigned char *)(SPI_TRANSFER_FORMAT)control_data;
        unsigned char *environmentdata_bytes = (unsigned char *)(SPI_TRANSFER_FORMAT)environment_data;
        unsigned char *sfpdata_bytes = (unsigned char *) sfp_data;

        udp_data.header = UDP_DATA_FORMAT::INFORMATION_DATA;

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

        temp_data = (unsigned char *) &UdpData.data[index];
        control_data = temp_data;
        index += SPI_TRANSFER_SIZE;

        temp_data = (unsigned char *) &UdpData.data[index];
        environment_data = temp_data;
        index += SPI_TRANSFER_SIZE;

        sfp_data = (unsigned char *) &UdpData.data[index];

        index += SFP_DATA_SIZE;

        return *this;

    }

};



struct CAMERA_SETTINGS_FORMAT
{
    uint8_t write_enable;

    uint8_t brighness;
    uint8_t contrast;
    uint8_t saturation;
    int8_t hue;

    uint8_t exposure;
    uint8_t auto_exposure;

    uint8_t gain;
    uint8_t auto_gain;

    uint8_t horizontal_flip;
    uint8_t vertical_flip;
    uint8_t power_frequency;
    uint8_t sharpness;

    uint8_t zoom;

    bool available = false;

    CAMERA_SETTINGS_FORMAT operator =(UDP_DATA_FORMAT& UdpData)
    {
        int index = 0;

        write_enable = UdpData.data[index++];
        brighness = UdpData.data[index++];
        contrast = UdpData.data[index++];
        saturation = UdpData.data[index++];
        hue = UdpData.data[index++];

        exposure = UdpData.data[index++];
        auto_exposure = UdpData.data[index++];

        gain = UdpData.data[index++];
        auto_gain = UdpData.data[index++];

        horizontal_flip = UdpData.data[index++];
        vertical_flip = UdpData.data[index++];
        power_frequency = UdpData.data[index++];
        sharpness = UdpData.data[index++];
        zoom = UdpData.data[index++];

        return *this;
    }

    operator UDP_DATA_FORMAT()
    {

        UDP_DATA_FORMAT udp_data;
        int index = 0;

        udp_data.header = UDP_DATA_FORMAT::CAMERA_SETTING_DATA;

        udp_data.data[index++] = write_enable;
        udp_data.data[index++] = brighness;
        udp_data.data[index++] = contrast;
        udp_data.data[index++] = saturation;
        udp_data.data[index++] = hue;

        udp_data.data[index++] = exposure;
        udp_data.data[index++] = auto_exposure;

        udp_data.data[index++] = gain;
        udp_data.data[index++] = auto_gain;

        udp_data.data[index++] = horizontal_flip;
        udp_data.data[index++] = vertical_flip;
        udp_data.data[index++] = power_frequency;
        udp_data.data[index++] = sharpness;
        udp_data.data[index++] = zoom;

        udp_data.checksum = 'C';
        udp_data.checksum |= 'H' << 8;

        return udp_data;

    }

};



#endif // ETHERNETDATATYPES_H
