//============================================================================
// Name        : udp2uart.cpp
// Author      : Yusuf Bülbül
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>          // For cout and cerr
#include <cstdlib>           // For atoi()
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


void ethernetToUartBridge();
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

    baund_rate = "B2000000";
    uart_port = "/dev/ttyAMA0";

	ret = serial_bus.uartInit((char *)baund_rate.c_str(), (char *)uart_port.c_str());
	if(ret != FAIL)
	    printf("Uart Port is opened succesfully\n");
	else
		printf("Uart Port can't opened\n");

//	cout << "*Select 1, To publish stream Udp to Uart" << endl;
//	cout << "*Select 2, To publish stream Uart to Udp" << endl;
//	cout << endl;
//	cout << "> ";
//
//	cin >> selection;
	selection = 2;


	if(selection == 1)
	{
		ethernetToUartBridge();
	}
	else if (selection == 2)
	{
		serial_bus.listenPort();

		thread sendData(sendUartDatatoEthernet);
		sendData.detach();


		while(true);
	}

    return 0;
}


void ethernetToUartBridge()
{

	int ret;
	int server_port = 53000;
	int package_size;
	unsigned char ethernet_data[4090];

	int sock;
	struct sockaddr_in name;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)   {
	perror("Opening datagram socket");
	}

	/* Bind our local address so that the client can send to us */
	bzero((char *) &name, sizeof(name));
	name.sin_family = AF_INET;
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	name.sin_port = htons(server_port);

	if (bind(sock, (struct sockaddr *) &name, sizeof(name))) {
	perror("binding datagram socket");
	}

	  printf("Socket has port number #%d\n", ntohs(name.sin_port));

	thread uart_bridge_thread(&SerialLib::sendVideoStream, &serial_bus);
	uart_bridge_thread.detach();

	while(true)
	{

		package_size = read(sock, ethernet_data, 4090);
		if(package_size > 0)
			ret = serial_bus.putQuiue(ethernet_data, package_size);

	}

}


void uartQuiue(unsigned char *Data, int Size)
{
	uart_queue.push(Data, Size);
}


void sendUartDatatoEthernet()
{


	int package_size;
	unsigned char *queue_package;


	int sockfd;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in serv;

	serv.sin_family = AF_INET;
	serv.sin_port = htons(52000);
	serv.sin_addr.s_addr = inet_addr("10.100.93.14");

	socklen_t m = sizeof(serv);


	while(true)
	{

		package_size = uart_queue.isEmpty();

		if(package_size != FAIL)
		{
			queue_package = new unsigned char[package_size];
			uart_queue.pop(queue_package, package_size);

			sendto(sockfd,queue_package,package_size,0,(struct sockaddr *)&serv,m);

			delete []queue_package;

		//	package_sequence++;
		}
	}
}
