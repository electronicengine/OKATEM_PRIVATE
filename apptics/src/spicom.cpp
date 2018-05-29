#include "spicom.h"
#include "globals.h"

SpiCom::Spi_Status SpiCom::spiTransmiteReceive(unsigned char *TransmittedData, int Size)
{
    int container_size = Size;
    struct spi_ioc_transfer spi[container_size];
    int ret = -1;

    //one spi transfer for each byte

    for (int i = 0 ; i < container_size ; i++)
    {
        memset(&spi[i], 0, sizeof (spi[i]));
        spi[i].tx_buf        = (unsigned long)(TransmittedData + i); // transmit from "data"
        spi[i].rx_buf        = (unsigned long)(TransmittedData + i) ; // receive into "data"
        spi[i].len           = sizeof(unsigned char) ;
        spi[i].delay_usecs   = 0 ;
        spi[i].speed_hz      = gmSpiSpeed ;
        spi[i].bits_per_word = gmSpiPerWords ;
        spi[i].cs_change = 0;
    }

    ret = ioctl(gmSpiFileDescriptor, SPI_IOC_MESSAGE(container_size), &spi) ;

    if(ret < 0)
    {
        printAll("Error - Problem transmitting spi data..ioctl");
        return Spi_Status::cannot_writeread;
    }

    return Spi_Status::succesfully_writeread;
}

SpiCom::Spi_Status SpiCom::spiClosePort()
{

    int ret;

    ret = close(gmSpiFileDescriptor);
    if(ret < 0)
    {
        printAll("Error - Could not close SPI device");
        return Spi_Status::cannot_close;
    }
    else
        return Spi_Status::succesfully_closed;

}

SpiCom::Spi_Status SpiCom::init()
{

    int ret;
    //----- SET SPI MODE -----
    //SPI_MODE_0 (0,0) 	CPOL = 0, CPHA = 0, Clock idle low, data is clocked in on rising edge, output data (change) on falling edge
    //SPI_MODE_1 (0,1) 	CPOL = 0, CPHA = 1, Clock idle low, data is clocked in on falling edge, output data (change) on rising edge
    //SPI_MODE_2 (1,0) 	CPOL = 1, CPHA = 0, Clock idle high, data is clocked in on falling edge, output data (change) on rising edge
    //SPI_MODE_3 (1,1) 	CPOL = 1, CPHA = 1, Clock idle high, data is clocked in on rising, edge output data (change) on falling edge
    gmSpiMode = SPI_MODE_0;


//	if (spi_device)
        gmSpiFileDescriptor = open(gmSpiFile.c_str(), O_RDWR);
//	else
//		*spi_cs_fd = open(std::string("/dev/spidev0.0").c_str(), O_RDWR);

    if (gmSpiFileDescriptor < 0)
    {
        printAll("Error - Could not open SPI device");

    }
    else
    {
        ret = ioctl(gmSpiFileDescriptor, SPI_IOC_WR_MODE, &gmSpiMode);
        if(ret < 0)
        {
            printAll("Could not set SPIMode (WR)...ioctl fail");
            return Spi_Status::cannot_open;
        }
        else
        {
            ret = ioctl(gmSpiFileDescriptor, SPI_IOC_RD_MODE, &gmSpiMode);
            if(ret < 0)
            {
              printAll("Could not set SPIMode (RD)...ioctl fail");
              return Spi_Status::cannot_open;
            }
            else
            {
                ret = ioctl(gmSpiFileDescriptor, SPI_IOC_WR_BITS_PER_WORD, &gmSpiPerWords);
                if(ret < 0)
                {
                  printAll("Could not set SPI bitsPerWord (WR)...ioctl fail");
                  return Spi_Status::cannot_open;
                }
                else
                {
                    ret = ioctl(gmSpiFileDescriptor, SPI_IOC_RD_BITS_PER_WORD, &gmSpiPerWords);
                    if(ret < 0)
                    {
                      printAll("Could not set SPI bitsPerWord(RD)...ioctl fail");
                      return Spi_Status::cannot_open;
                    }
                    else
                    {
                        ret = ioctl(gmSpiFileDescriptor, SPI_IOC_WR_MAX_SPEED_HZ, &gmSpiSpeed);
                        if(ret < 0)
                        {
                          printAll("Could not set SPI speed (WR)...ioctl fail");
                          return Spi_Status::cannot_open;
                        }
                        else
                        {
                            ret = ioctl(gmSpiFileDescriptor, SPI_IOC_RD_MAX_SPEED_HZ, &gmSpiSpeed);
                            if(ret < 0)
                            {
                              printAll("Could not set SPI speed (RD)...ioctl fail");
                              return Spi_Status::cannot_open;
                            }
                        }
                    }
                }
            }
        }

        printAll("SpiPort Succesfully Opened\n");

        return Spi_Status::succesfully_opened;
    }

}

SpiCom::SpiCom() : gmSpiDevice(0), gmSpiFile("/dev/spidev32766.0"), gmSpiMode(SPI_MODE_0), gmSpiPerWords(8), gmSpiSpeed(500000)
{
    init();
}

SpiCom::SpiCom(const std::string& SpiFile, int SpiSpeed) : gmSpiDevice(0), gmSpiFile(SpiFile), gmSpiMode(SPI_MODE_0), gmSpiPerWords(8), gmSpiSpeed(SpiSpeed)
{
    init();
}


