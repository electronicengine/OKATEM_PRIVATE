#ifndef SPICOM_H
#define SPICOM_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>		//Needed for SPI port
#include <sys/ioctl.h>		//Needed for SPI port
#include <linux/spi/spidev.h>	//Needed for SPI port
#include <unistd.h>		//Needed for SPI port
#include <vector>
#include <string.h>

#include "globals.h"

class SpiCom
{
public:

    SpiCom();
    SpiCom(const std::string& SpiFile, int SpiSpeed);

    Status spiTransmiteReceive(unsigned char *TransmittedData, int Size);
    Status spiClosePort();


    Status init();


private:
    int gmSpiSpeed;
    int gmSpiDevice;
    int gmSpiFileDescriptor;			//file descriptor for the SPI device

    std::string gmSpiFile;

    unsigned char gmSpiMode;
    unsigned char gmSpiPerWords;

};

#endif // SPICOM_H
