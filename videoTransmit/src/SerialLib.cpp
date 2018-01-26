/*
 * SerialLib.cpp
 *
 *  Created on: Oct 5, 2017
 *      Author: root
 */
#include <opencv2/opencv.hpp>
#include "SerialLib.h"
#include "config.h"
#include "PracticalSocket.h" // For UDPSocket and SocketException

#define BUF_LEN 65540 // Larger than maximum UDP packet size

extern void uartQuiue(unsigned char *Data, int Size);

using namespace cv;
using namespace std;

SerialLib::SerialLib() {
	// TODO Auto-generated constructor stub

}

SerialLib::~SerialLib() {
	// TODO Auto-generated destructor stub
}

unsigned char* SerialLib::generateRandom()
{
	unsigned char* bytes = new unsigned char[TRANSMISSION_SIZE];

	for(int i=0; i<TRANSMISSION_SIZE; i++)
	{
		bytes[i]=rand() % 255;
	}

	return bytes;
}

int SerialLib::uartInit(char *BaundRate, char* Port)
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
	gFileDescriptor = open(Port, O_RDWR | O_NOCTTY | O_NDELAY );		//Open in non blocking read/write mode
	if (gFileDescriptor == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		printf("+Error - Unable to open UART.  Ensure it is not in use by another application\n");
		return FAIL;
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
	tcgetattr(gFileDescriptor, &options);
	if(strcmp(BaundRate,"B1200") == 0)
		options.c_cflag = B1200 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B2400") == 0)
		options.c_cflag = B2400 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B4800") == 0)
		options.c_cflag = B4800 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B9600") == 0)
		options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B19200") == 0)
		options.c_cflag = B19200 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B38400") == 0)
		options.c_cflag = B38400 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B57600") == 0)
		options.c_cflag = B57600 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B115200") == 0)
		options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B230400") == 0)
		options.c_cflag = B230400 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B460800") == 0)
		options.c_cflag = B460800 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B500000") == 0)
		options.c_cflag = B500000 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B576000") == 0)
		options.c_cflag = B576000 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B921600") == 0)
		options.c_cflag = B921600 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B1000000") == 0)
		options.c_cflag = B1000000 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B1152000") == 0)
		options.c_cflag = B1152000 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B1500000") == 0)
		options.c_cflag = B1500000 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B2000000") == 0)
		options.c_cflag = B2000000 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B2500000") == 0)
		options.c_cflag = B2500000 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B3000000") == 0)
		options.c_cflag = B3000000 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B3500000") == 0)
		options.c_cflag = B3500000 | CS8 | CLOCAL | CREAD;
	else if(strcmp(BaundRate,"B4000000") == 0)
		options.c_cflag = B4000000 | CS8 | CLOCAL | CREAD;
	else
	{
		printf("+Error - Unable to open UART.  Ensure it is not in use by another application\n");
		closeUart();
		return FAIL;
	}

	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(gFileDescriptor, TCIFLUSH);
	tcsetattr(gFileDescriptor, TCSANOW, &options);

	return SUCCESS;
}


int SerialLib::readHeader(unsigned char *RecievedData)
{
	int data_count = 0;
	int read_size = 0;
	unsigned char rx_buffer;

	if (gFileDescriptor != -1)
	{
			// Read up to 255 characters from the port if they are there

		do
		{
			read_size = read(gFileDescriptor, &rx_buffer, 1);		//Filestream, buffer to store in, number of bytes to read (max)
			if (read_size > 0)
			{
				memcpy(&RecievedData[data_count], &rx_buffer, 1);
				data_count += read_size;
			}

		}while(data_count != TRANSMISSION_SIZE);

	}
	else
	{
		return FAIL;
	}

	return SUCCESS;
}


int SerialLib::readUart(unsigned char *RecievedData, int Size)
{

	int data_count = 0;
	int read_size = 0;
	unsigned char rx_buffer;

	if (gFileDescriptor != -1)
	{
			// Read up to 255 characters from the port if they are there

		do
		{
			read_size = read(gFileDescriptor, &rx_buffer, 1);		//Filestream, buffer to store in, number of bytes to read (max)
			if (read_size > 0)
			{
				memcpy(&RecievedData[data_count], &rx_buffer, 1);
				data_count += read_size;
			}

		}while(data_count != Size);

	}
	else
	{
		return FAIL;
	}

	return SUCCESS;
}

int SerialLib::writeHeader(unsigned char* TransmittedData)
{
	int data_count = 0;
	int write_size = 0;

	if (gFileDescriptor != -1)
	{

		do
		{
			write_size = write(gFileDescriptor, &TransmittedData[data_count], 1);		//Filestream, bytes to write, number of bytes to write
			if(write_size > 0)
				data_count += write_size;


		}while(data_count != TRANSMISSION_SIZE);
	}

	data_count = 0;
	write_size = 0;


	return SUCCESS;
}

int SerialLib::writeUart(unsigned char* TransmittedData, int Size)
{
	//----- TX BYTES -----
	//----- TX BYTES -----
	int data_count = 0;
	int write_size = 0;

	if (gFileDescriptor != -1)
	{

		do
		{
			write_size = write(gFileDescriptor, &TransmittedData[data_count], 1);		//Filestream, bytes to write, number of bytes to write
			if(write_size > 0)
				data_count += write_size;


		}while(data_count != Size);
	}

	data_count = 0;
	write_size = 0;


	return SUCCESS;
}

void SerialLib::closeUart()
{
//  ----- CLOSE THE UART -----
	close(gFileDescriptor);
}



void SerialLib::listenPort()
{
	if(gListeningFlag == false)
	{
		printf("+Listening the Uart Port...\n");

		thread listen_thread(&SerialLib::checkData, this);
		listen_thread.detach();
		gListeningFlag = true;
	}
	else
	{
		printf("+The Port is already listening.\n");
	}

}



//int SerialLib::parseDataAndSend(unsigned char* Data, long Size)
//{
//
//	int sequence;
//	int remain_size = TRANSMISSION_SIZE;
//	unsigned char last_part[TRANSMISSION_SIZE];
//
//	sequence = Size / TRANSMISSION_SIZE;
//	if((Size % TRANSMISSION_SIZE) != 0)
//	{
//		remain_size = Size % TRANSMISSION_SIZE;
//		sequence++;
//	}
//
//	for(int i=0; i<sequence; i++)
//	{
//		if(sequence -1 == i)
//		{
//			memset(&last_part[0], 0, TRANSMISSION_SIZE);
//			memcpy(&last_part[0], &Data[i*TRANSMISSION_SIZE], remain_size);
//			writeUart(&last_part[0]);
//		}
//		else
//			writeUart(&Data[i*TRANSMISSION_SIZE]);
//	}
//
//	return SUCCESS;
//}


void SerialLib::checkData()
{
	int ret;
	uint32_t package_size;
	unsigned char rx_buffer[TRANSMISSION_SIZE];

	if (gFileDescriptor != -1)
	{
		while(true)
		{
			ret = readHeader(&rx_buffer[0]);
			if(ret == SUCCESS)
			{
				if(strncmp((char*)&rx_buffer[0], "senv", TRANSMISSION_HEADER_SIZE) == 0)
				{
					package_size = ( (rx_buffer[4] << 24)
					                   + (rx_buffer[5] << 16)
					                   + (rx_buffer[6] << 8)
					                   + (rx_buffer[7] ) );

					receiveVideoStream(package_size);
				}
			}
		}
	}
	else
	{
		printf("+ERROR! Port is not Open\n");
	}
}

int SerialLib::receiveVideoStream(uint32_t Size)
{
//	unsigned char rx_buffer[Size];

	int remain_size = TRANSMISSION_SIZE;
	int sequence;
	unsigned char longbuf[Size];

//	printf("Package Size: %d \n", Size);

	if(Size == 0)
		return FAIL;

//	sequence = Size / TRANSMISSION_SIZE;
//	if((Size % TRANSMISSION_SIZE) != 0)
//	{
//		remain_size = Size % TRANSMISSION_SIZE;
//		sequence++;
//	}
//
//	for(int i=0; i<sequence; i++)
//	{
//
//		readUart(&rx_buffer[0]);
//
//		if(i == sequence - 1)
//			memcpy(&longbuf[i*TRANSMISSION_SIZE], &rx_buffer[0] ,remain_size);
//		else
//			memcpy(&longbuf[i*TRANSMISSION_SIZE], &rx_buffer[0] ,TRANSMISSION_SIZE);
//
//	}



//	printf("\n Uart Recieving Data: ");
//	for(int i= 0; i<Size; i++)
//		printf("%02X-", longbuf[i]);
//	printf("\n");

	readUart(longbuf, Size);

	uartQuiue(longbuf, Size);

	return SUCCESS;

}



int SerialLib::sendVideoStream(unsigned char* Data, uint32_t Size)
{

	char *header = "senv";
	unsigned char package_size[TRANSMISSION_HEADER_SIZE];
	unsigned char data_header[TRANSMISSION_SIZE];

//	cout << "+File Size: " << Size << endl;

	package_size[0] = (int)((Size & 0xFF000000) >> 24 );
	package_size[1] = (int)((Size & 0x00FF0000) >> 16 );
	package_size[2] = (int)((Size & 0x0000FF00) >> 8 );
	package_size[3] = (int)((Size & 0X000000FF));

	memcpy(&data_header[0], (unsigned char *)&header[0], TRANSMISSION_HEADER_SIZE);
	memcpy(&data_header[TRANSMISSION_HEADER_SIZE], &package_size[0], TRANSMISSION_HEADER_SIZE);

	writeHeader(&data_header[0]); // file_descriptor is sending

//	printf("\n Uart Sending Data: ");
//	for(int i= 0; i<Size; i++)
//		printf("%02X-", Data[i]);
//	printf("\n");
	writeUart(Data, Size);

//	parseDataAndSend(Data, Size);

	// terminate

	return SUCCESS;

}

