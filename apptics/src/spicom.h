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

class SpiCom
{
public:

    enum class Spi_Status
    {
        time_out,
        cannot_open,
        cannot_close,
        cannot_writeread,
        succesfully_opened,
        succesfully_closed,
        succesfully_writeread,

    }Status;

    SpiCom();
    SpiCom(const std::string& SpiFile, int SpiSpeed);

    Spi_Status spiTransmiteReceive(unsigned char *TransmittedData, int Size);
    Spi_Status spiClosePort();


private:
    int gmSpiSpeed;
    int gmSpiDevice;
    int gmSpiFileDescriptor;			//file descriptor for the SPI device

    std::string gmSpiFile;

    unsigned char gmSpiMode;
    unsigned char gmSpiPerWords;

    Spi_Status init();

};

#endif // SPICOM_H
