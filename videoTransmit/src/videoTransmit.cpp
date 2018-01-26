//============================================================================
// Name        : videoTransmit.cpp
// Author      : Yusuf Bülbül
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>          // For cout and cerr
#include <cstdlib>           // For atoi()
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <stdlib.h>
#include <time.h>
#include <mutex>
#include "SerialLib.h"
#include "config.h"
#include "PracticalSocket.h" // For UDPSocket and SocketException
#include "TcpSocket.h"
#include "PackageQueue.h"

#define BUF_LEN 65540 // Larger than maximum UDP packet size

using namespace cv;

void ethernetToUartBridge();
void publishVideoStream();
void uartQuiue(unsigned char *Data, int Size);
void sendUartDatatoEthernet();

SerialLib serial_bus;

TcpSocket client_socket;

PackageQueue uart_queue;

bool full_quiue = false;
int quiue_count=0;

unsigned char **quiue = new unsigned char*[2048];


int main(int argc, char * argv[]) {

//    if (argc != 2) { // Test for correct number of parameters
//        cerr << "Usage: " << argv[0] << " <Server Port>" << endl;
//        exit(1);
//    }

    int ret;
    int selection;
    string baund_rate;
    string uart_port;

    baund_rate = "B4000000";
    uart_port = "/dev/ttyAMA0";

	ret = serial_bus.uartInit((char *)baund_rate.c_str(), (char *)uart_port.c_str());
	if(ret != FAIL)
	    printf("Uart Port is opened succesfully\n");
	else
		printf("Uart Port can't opened\n");

	cout << "*Select 1, To play stream Tcp to Uart" << endl;
	cout << "*Select 2, To play stream on Uart" << endl;
	cout << "*Select 3, To publish stream" << endl;
	cout << endl;
	cout << "> ";

	cin >> selection;

	if(selection == 1)
	{
		ethernetToUartBridge();
	}
	else if (selection == 2)
	{
		serial_bus.listenPort();

		thread sendData(sendUartDatatoEthernet);
		sendData.detach();

		client_socket.connectServer("10.100.93.14", 2000);

		while(true);
	}
	else if (selection == 3)
	{
		publishVideoStream();
	}


    return 0;
}


void ethernetToUartBridge()
{
	int size = 0;
	unsigned char client_message[PACK_SIZE];
	int port = 2000;
	int total_pack_size;
	int remain_package_size = PACK_SIZE;
	int package_sequence;
	int total_pack;
	unsigned char *longbuf;


	//	cout << "Enter Port " << endl;
	//	cout <<">";
	//	cin >> port;
	TcpSocket tcp_soc;
	tcp_soc.createServerSocket(port);

	while(true)
	{

		size = tcp_soc.receiveDatafromClient(&client_message[0]);
		if(size != PACK_SIZE)
			printf("Package: %d\n", size);

		if(size < 0)
		{
			printf("error: %d\n", size);
			continue;
		}

		total_pack_size = ( (client_message[1] << 24 )
											   + (client_message[2] << 16)
											   + (client_message[3] << 8)
											   + (client_message[4]) );

		package_sequence = ( (client_message[5] << 24 )
											   + (client_message[6] << 16)
											   + (client_message[7] << 8)
											   + (client_message[8]) );

		if(total_pack_size <= 0 || total_pack_size >= 1000000)
		{
			printf("wrong pack size %d\n", total_pack_size);
			continue;
		}
//
//		cout << "expecting total pack size:" << total_pack_size << endl;
//		cout << "Package Sequence:" << package_sequence << endl;
		longbuf = (unsigned char*)calloc(total_pack_size, 1);

		total_pack = total_pack_size / PACK_SIZE;
		if(total_pack_size % PACK_SIZE != 0)
		{
			total_pack++;
			remain_package_size = total_pack_size % PACK_SIZE;
		}

//		cout << "total pack:" << total_pack << endl;

		for (int i = 0; i < total_pack; i++)
		{
//			cout << "recieving pack part - :" << i << endl;

			size = tcp_soc.receiveDatafromClient(&client_message[0]);
			if(size != PACK_SIZE)
				printf("Package: %d\n", size);

//			for(int i = 1019; i < 1024; i++)
//				printf("%02X-", client_message[i]);
//			printf("\n");

			if(i == total_pack - 1)
				memcpy(&longbuf[i*PACK_SIZE], &client_message[0] ,remain_package_size);
			else
				memcpy(&longbuf[i*PACK_SIZE], &client_message[0] ,PACK_SIZE);
		}

		serial_bus.sendVideoStream(longbuf, total_pack_size);


	}

}

void publishVideoStream()
{
	string ip = "10.100.93.14";
	int port = 2000;
	unsigned char parted_bytes[PACK_SIZE];
	vector < int > compression_params;
	int total_pack_size;
	int total_pack;
	int package_sequence = 0;
	int remain_size = PACK_SIZE;

//	cout << "*Enter Ip" << endl;
//	cout << "> ";
//	cin >> ip;
//
//	cout << "*Enter Port" << endl;
//	cout << "> ";
//	cin >> port;

	TcpSocket tcp_soc;
	tcp_soc.connectServer((char *) ip.c_str(), port);

	int jpegqual =  ENCODE_QUALITY; // Compression Parameter

	Mat frame, send;
	vector < uchar > encoded;
	VideoCapture cap("/home/pi/Downloads/example0.5MBPS.mp4"); // Grab the camera
	namedWindow("send", CV_WINDOW_AUTOSIZE);

	if (!cap.isOpened())
	{
		cerr << "OpenCV Failed to open media";
		exit(1);
	}

	while(true)
	{

		cap >> frame;
		if(frame.size().width==0)continue;//simple integrity check; skip erroneous data...
	     	resize(frame, send, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_LINEAR);

		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
		compression_params.push_back(jpegqual);

		imencode(".jpg", send, encoded, compression_params);

		total_pack_size = encoded.size();
		total_pack = total_pack_size / PACK_SIZE;
		if(total_pack_size % PACK_SIZE != 0)
		{
			total_pack++;
			remain_size = total_pack_size % PACK_SIZE;
		}

//		cout << "Total Pack Size: " << total_pack_size << endl;
//		cout << "Total Pack: " << total_pack<< endl;
//		cout << "Package_Sequence;  " << package_sequence << endl;

		memset(&parted_bytes[0], 0x20, PACK_SIZE);

		parted_bytes[1] = (int)((total_pack_size & 0xFF000000) >> 24);
		parted_bytes[2] = (int)((total_pack_size & 0x00FF0000) >> 16);
		parted_bytes[3] = (int)((total_pack_size & 0x0000FF00) >> 8);
		parted_bytes[4] = (int)((total_pack_size & 0X000000FF));

		parted_bytes[5] = (int)((package_sequence & 0xFF000000) >> 24);
		parted_bytes[6] = (int)((package_sequence & 0x00FF0000) >> 16);
		parted_bytes[7] = (int)((package_sequence & 0x0000FF00) >> 8);
		parted_bytes[8] = (int)((package_sequence & 0X000000FF));

		tcp_soc.sendDatatoServer(&parted_bytes[0]);

		for (int i = 0; i < total_pack; i++)
		{

//			cout << "recieving pack part - :" << i << endl;

			if(total_pack - 1 == i)
				memcpy(&parted_bytes[0], &encoded[i * PACK_SIZE], remain_size);
			else
				memcpy(&parted_bytes[0], &encoded[i * PACK_SIZE], PACK_SIZE);

//			for(int i = 1019; i < 1024; i++)
//				printf("%02X-", parted_bytes[i]);
//			printf("\n");

			tcp_soc.sendDatatoServer(&parted_bytes[0]);

		}

		package_sequence++;

		if(package_sequence >= 4000000)
			package_sequence = 0;

//		imshow("send", send);
//		waitKey(FRAME_INTERVAL);
	}
}

void uartQuiue(unsigned char *Data, int Size)
{

	uart_queue.push(Data, Size);

//	quiue[quiue_count] = new unsigned char[Size];
//	memcpy(quiue[quiue_count], Data, Size);
//
//	thread sendData(sendUartDatatoEthernet, quiue[quiue_count], Size);
//	sendData.detach();
//
//	if(quiue_count >= 1024)
//			delete quiue[quiue_count - 1024];
//
//	if(full_quiue == true)
//		if(quiue_count < 1024)
//			delete quiue[2047 - quiue_count];
//
//	quiue_count++;
//	if(quiue_count >= 2047)
//	{
//		full_quiue = true;
//		quiue_count = 0;
//	}
}


void sendUartDatatoEthernet()
{

	int package_size;
	static int package_sequence;
	unsigned char parted_bytes[PACK_SIZE];
	unsigned char *queue_package;
	int remain_size = PACK_SIZE;
	int total_pack;


	while(true)
	{

		package_size = uart_queue.isEmpty();

		if(package_size != FAIL)
		{

			total_pack = package_size / PACK_SIZE;
			if(package_size % PACK_SIZE != 0)
			{
				total_pack++;
				remain_size = package_size % PACK_SIZE;
			}

			queue_package = new unsigned char[package_size];
			uart_queue.pop(queue_package, package_size);

			memset(&parted_bytes[0], 0x20, PACK_SIZE);

			parted_bytes[1] = (int)((package_size & 0xFF000000) >> 24);
			parted_bytes[2] = (int)((package_size & 0x00FF0000) >> 16);
			parted_bytes[3] = (int)((package_size & 0x0000FF00) >> 8);
			parted_bytes[4] = (int)((package_size & 0X000000FF));

			parted_bytes[5] = (int)((package_sequence & 0xFF000000) >> 24);
			parted_bytes[6] = (int)((package_sequence & 0x00FF0000) >> 16);
			parted_bytes[7] = (int)((package_sequence & 0x0000FF00) >> 8);
			parted_bytes[8] = (int)((package_sequence & 0X000000FF));

			client_socket.sendDatatoServer(&parted_bytes[0]);
		//

				for (int i = 0; i < total_pack; i++)
				{
					if(total_pack - 1 == i)
						memcpy(&parted_bytes[0], &queue_package[i * PACK_SIZE], remain_size);
					else
						memcpy(&parted_bytes[0], &queue_package[i * PACK_SIZE], PACK_SIZE);

					client_socket.sendDatatoServer(&parted_bytes[0]);
				}

			delete queue_package;

		//	package_sequence++;
		}
	}


}


