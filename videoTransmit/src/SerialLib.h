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
#include <opencv2/opencv.hpp>
#include "config.h"
#include "PracticalSocket.h" // For UDPSocket and SocketException


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

	void closeUart();
	void checkData();
	void listenPort();
	void sendMessage();
	void sendRandom(int Sequence);
	int sendFile();
	int sendVideoStream(unsigned char *Data, uint32_t Size);
	int receiveVideoStream(uint32_t Size);
	int recieveFile(uint32_t DataSize);

	int gDataCount = 0;
	int gFileDescriptor = -1;
	bool gListeningFlag = false;
	cv::Mat rawData;
	cv::Mat frame;

private:



};

#endif /* SERIALLIB_H_ */
