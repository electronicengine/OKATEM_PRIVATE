/*
 * Socket.h
 *
 *  Created on: Jul 17, 2017
 *      Author: yusuf
 */

#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <iostream>
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <time.h>

#define FAIL -1
#define SUCCESS 0

class TcpSocket {
public:
	TcpSocket();
	virtual ~TcpSocket();

	void connection_handler(void *);

	int createServerSocket(int Port);
	int sendDatatoClient();
	int receiveDatafromClient(unsigned char *Data);
	int connectServer(char* Ip, int Port);
	int recieveDatafromServer(unsigned char *Message);
	int sendDatatoServer(unsigned char *Message);
	int listenServer();
	int acceptDataPackage(unsigned char *Package);

	void checkData(int Socket, int Size);


private:
	int gSocket;
	const int DATA_PACKAGE_SIZE = 1024;

    int gServerSocket , gClientSocket , gIncomingSocket;
    struct sockaddr_in server , client;


};

#endif /* TCPSOCKET_H_ */
