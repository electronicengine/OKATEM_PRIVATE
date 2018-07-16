/*
 * SerialLib.h
 *
 *  Created on: Oct 5, 2017
 *      Author: root
 */

#ifndef SERIALLIB_H_
#define SERIALLIB_H_

#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <time.h>
#include "config.h"
#include "PracticalSocket.h" // For UDPSocket and SocketException
#include "PackageQueue.h"

#define SUCCESS 0
#define FAIL -1

#define TRANSMISSION_HEADER_SIZE 4
#define TRANSMISSION_SIZE 8


class SerialLib {
public:

	SerialLib();
	virtual ~SerialLib();

	unsigned char *generateRandom();
	int uartInit(char *BaundRate, char *Port);
	int readUart(unsigned char *RecievedData, int Size);
	int readHeader(unsigned char *Header);
	int writeUart(unsigned char *TransmittedData, int Size);
	int writeHeader(unsigned char *Header);
	int parseDataAndSend(unsigned char *Data, long Size);
	int putQuiue(unsigned char *Package, int Size);

	void closeUart();
	void checkData();
	void listenPort();
	void sendMessage();
	void sendRandom(int Sequence);
	int sendFile();
	void sendVideoStream();
	int receiveVideoStream(uint32_t Size);
	int recieveFile(uint32_t DataSize);

	int gDataCount = 0;
	int gFileDescriptor = -1;
	bool gListeningFlag = false;
	PackageQueue gUartQuiue;



private:



};

#endif /* SERIALLIB_H_ */
