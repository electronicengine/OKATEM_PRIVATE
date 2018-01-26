//============================================================================
// Name        : videoPlay.cpp
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

#define BUF_LEN 65540 // Larger than maximum UDP packet size

using namespace cv;

void playVideoStream();
void publishVideoStream();
void ethQuiue(unsigned char *Data, int Size);
SerialLib serial_bus;
std::mutex mtx;

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
		playVideoStream();
	}
	else if (selection == 2)
	{
		serial_bus.listenPort();
		while(true);
	}
	else if (selection == 3)
	{
		publishVideoStream();
	}

    return 0;
}


void playVideoStream()
{
	int size = 0;
	uint32_t total_pack_size;
	uint32_t package_sequence;
	unsigned char client_message[PACK_SIZE];
	int port = 2000;
	int remain_pack_size = PACK_SIZE;
	int total_pack;
	unsigned char *longbuf;
	int key;
	Mat rawData;
	Mat frame;
	unsigned char **quiue = new unsigned char*[1024];

	double delay_time;
	double delay_per_byte = 1;

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
			remain_pack_size = total_pack_size % PACK_SIZE;
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
				memcpy(&longbuf[i*PACK_SIZE], &client_message[0] ,remain_pack_size);
			else
				memcpy(&longbuf[i*PACK_SIZE], &client_message[0] ,PACK_SIZE);
		}


		rawData = Mat(1, total_pack_size, CV_8UC1, longbuf);
		frame = imdecode(rawData, CV_LOAD_IMAGE_COLOR);

		if (frame.size().width == 0)
		{
			cerr << "decode failure!" << endl;
			continue;
		}
		else
		{
			imshow("recv", frame);
			waitKey(1);
		}

//		delay_time = delay_per_byte * total_pack_size + 10;

//		clock_t sending_start = clock();

//		serial_bus.sendVideoStream(longbuf, total_pack_size);

		free(longbuf);

//		clock_t sending_end = clock();
//
//		delay_time = (double)((double)sending_end - (double)sending_start);
//		cout << "Sending Time: " << sending_start << endl;
//		cout << "Sending Time: " << sending_end << endl;
//		delay_per_byte = (delay_time / total_pack_size) ;

	}
}


void publishVideoStream()
{
	string ip = "10.100.93.33";
	int port = 2000;
	unsigned char parted_bytes[PACK_SIZE];
	vector < int > compression_params;
	int total_pack_size;
	int total_pack;
	int package_sequence = 0;
	int remain_size = PACK_SIZE;
	int length;
	int rows;
	int cols;
	int num_el;

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
	VideoCapture cap("/root/Downloads/example1.5MBPS.mp4"); // Grab the camera

	if (!cap.isOpened())
	{
		cerr << "OpenCV Failed to open media";
		exit(1);
	}

	while(true)
	{
		cap >> frame;

		rows = frame.rows;
		cols = frame.cols;
		num_el = rows*cols;
		length = num_el*frame.elemSize1();

//		cout << "lenght: " << length << endl;

		if(frame.size().width==0)continue;//simple integrity check; skip erroneous data...
//		resize(frame, send, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_LINEAR);

		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
		compression_params.push_back(jpegqual);

		imencode(".jpg", frame, encoded, compression_params);

		total_pack_size = encoded.size();
		total_pack = total_pack_size / PACK_SIZE;
		if(total_pack_size % PACK_SIZE != 0)
		{
			total_pack++;
			remain_size = total_pack_size % PACK_SIZE;
		}

		memset(&parted_bytes[0], 0x20, PACK_SIZE);

		parted_bytes[1] = (int)((total_pack_size & 0xFF000000) >> 24 );
		parted_bytes[2] = (int)((total_pack_size & 0x00FF0000) >> 16 );
		parted_bytes[3] = (int)((total_pack_size & 0x0000FF00) >> 8 );
		parted_bytes[4] = (int)((total_pack_size & 0X000000FF));

		parted_bytes[5] = (int)((package_sequence & 0xFF000000) >> 24 );
		parted_bytes[6] = (int)((package_sequence & 0x00FF0000) >> 16 );
		parted_bytes[7] = (int)((package_sequence & 0x0000FF00) >> 8 );
		parted_bytes[8] = (int)((package_sequence & 0X000000FF));

//		usleep(total_pack_size*2);

		tcp_soc.sendDatatoServer(&parted_bytes[0]);



		for (int i = 0; i < total_pack; i++)
		{

			if(total_pack - 1 == i)
			{
				memset(&parted_bytes[0], 0x20, PACK_SIZE);
				memcpy(&parted_bytes[0], &encoded[i * PACK_SIZE], remain_size);
			}
			else
				memcpy(&parted_bytes[0], &encoded[i * PACK_SIZE], PACK_SIZE);

			tcp_soc.sendDatatoServer(&parted_bytes[0]);


		}
		package_sequence++;

		if(package_sequence >=1000000)
			package_sequence = 0;

		imshow("send", frame);
		waitKey(1);

	}
}
