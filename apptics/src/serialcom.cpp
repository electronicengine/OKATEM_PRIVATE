#include "serialcom.h"





SerialCom::Serial_Status SerialCom::readData(std::vector<unsigned char>& Container, int &Size, int Timeout)
{
   int data_index = 0;
   int read_size = 0;
   int rx_data;

   if (gmFileDescriptor != -1)
   {

       if(Timeout != 0)
       {
           std::thread timeoutOps(&SerialCom::setTimeout, this, Timeout);
           timeoutOps.detach();
       }

       if(Size == 0)
           Size = 999999;



       do
       {

           read_size = read(gmFileDescriptor, &rx_data, sizeof(unsigned char));
           if (read_size > 0)
           {

               Container.push_back(rx_data);
               data_index += read_size;

           }

           if(gmTimeOutFlag == 1)
           {
               gmTimeOutFlag = 0;
               Size = data_index;
               return Serial_Status::time_out;

           }

       }
       while(data_index != Size);

       return Serial_Status::succesfully_read;
   }
   else
   {
       return Serial_Status::cannot_read;
   }
}


void SerialCom::setTimeout(int TimeOut)
{

//    gmMutex.lock();
    gmTimeOutFlag = 0;
//    gmMutex.unlock();

    usleep(TimeOut*1000);

//    gmMutex.lock();
    gmTimeOutFlag = 1;
//    gmMutex.unlock();

}



SerialCom::Serial_Status SerialCom::Close()
{
   tcflush(gmFileDescriptor, TCIFLUSH);
   close(gmFileDescriptor);
}



SerialCom::Serial_Status SerialCom::Init()
{

    //-------------------------
    //----- SETUP USART 0 -----
    //-------------------------
    //At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively

    //OPEN THE UART
    //The flags (defined in fcntl.h):
    //	Access modes (use 1 of these):
    //		O_RDONLY - Open for reading only.
    //		O_RDWR - Open for reading and writing.
    //		O_WRONLY - Open for writing only.
    //
    //	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
    //											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
    //											immediately with a failure status if the output can't be written immediately.
    //
    //	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.
    gmFileDescriptor = open(gmPort.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
    if (gmFileDescriptor == -1)
    {
            //ERROR - CAN'T OPEN SERIAL PORT
            printAll("Serial Port file can not opened\n");
            return Serial_Status::cannot_open;
    }

    //CONFIGURE THE UART
    //The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
    //	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
    //	CSIZE:- CS5, CS6, CS7, CS8
    //	CLOCAL - Ignore modem status lines
    //	CREAD - Enable receiver
    //	IGNPAR = Ignore characters with parity errors
    //	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
    //	PARENB - Parity enable
    //	PARODD - Odd parity (else even)
    struct termios options;
    tcgetattr(gmFileDescriptor, &options);
     options.c_cflag = CS8 | CLOCAL | CREAD;

    if (strcmp(gmBaundRate.c_str(),"B1200") == 0)
            options.c_cflag |= B1200 ;
    else if(strcmp(gmBaundRate.c_str(),"B2400") == 0)
            options.c_cflag |= B2400;
    else if(strcmp(gmBaundRate.c_str(),"B4800") == 0)
            options.c_cflag |= B4800;
    else if(strcmp(gmBaundRate.c_str(),"B9600") == 0)
            options.c_cflag |= B9600;
    else if(strcmp(gmBaundRate.c_str(),"B19200") == 0)
            options.c_cflag |= B19200;
    else if(strcmp(gmBaundRate.c_str(),"B38400") == 0)
            options.c_cflag |= B38400;
    else if(strcmp(gmBaundRate.c_str(),"B57600") == 0)
            options.c_cflag |= B57600;
    else if(strcmp(gmBaundRate.c_str(),"B115200") == 0)
            options.c_cflag |= B115200;
    else if(strcmp(gmBaundRate.c_str(),"B230400") == 0)
            options.c_cflag |= B230400;
    else if(strcmp(gmBaundRate.c_str(),"B460800") == 0)
            options.c_cflag |= B460800;
    else if(strcmp(gmBaundRate.c_str(),"B500000") == 0)
            options.c_cflag |= B500000;
    else if(strcmp(gmBaundRate.c_str(),"B576000") == 0)
            options.c_cflag |= B576000;
    else if(strcmp(gmBaundRate.c_str(),"B921600") == 0)
            options.c_cflag |= B921600;
    else if(strcmp(gmBaundRate.c_str(),"B1000000") == 0)
            options.c_cflag |= B1000000;
    else if(strcmp(gmBaundRate.c_str(),"B1152000") == 0)
            options.c_cflag |= B1152000;
    else if(strcmp(gmBaundRate.c_str(),"B1500000") == 0)
            options.c_cflag |= B1500000;
    else if(strcmp(gmBaundRate.c_str(),"B2000000") == 0)
            options.c_cflag |= B2000000;
    else if(strcmp(gmBaundRate.c_str(),"B2500000") == 0)
            options.c_cflag |= B2500000;
    else if(strcmp(gmBaundRate.c_str(),"B3000000") == 0)
            options.c_cflag |= B3000000;
    else if(strcmp(gmBaundRate.c_str(),"B3500000") == 0)
            options.c_cflag |= B3500000;
    else if(strcmp(gmBaundRate.c_str(),"B4000000") == 0)
            options.c_cflag |= B4000000;
    else
    {
            printAll("Serial Port Baundrate is wrongly\n");
            Close();
            return Serial_Status::cannot_open;
    }

    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(gmFileDescriptor, TCIFLUSH);
    tcsetattr(gmFileDescriptor, TCSANOW, &options);


    return Serial_Status::succesfully_opened;

}


SerialCom::SerialCom() : gmBaundRate("B57600"), gmPort("/dev/ttyS2")
{
    Status = Init();
    if(Status == Serial_Status::succesfully_opened)
        printAll("Serial Port Succesfully Opened\n");
    else
        printAll("Serial Port Can Not Opened\n");

}

SerialCom::SerialCom(const std::string& BaundRate) : gmBaundRate(BaundRate), gmPort("/dev/ttyS2")
{
    Status = Init();
    if(Status == Serial_Status::succesfully_opened)
        printAll("Serial Port Succesfully Opened\n");
    else
        printAll("Serial Port Can Not Opened\n");
}

SerialCom::SerialCom(const std::string& BaundRate, const std::string& Port) : gmBaundRate(BaundRate), gmPort(Port)
{
    Status = Init();
    if(Status == Serial_Status::succesfully_opened)
        printAll("Serial Port Succesfully Opened\n");
    else
        printAll("Serial Port Can Not Opened\n");
}



