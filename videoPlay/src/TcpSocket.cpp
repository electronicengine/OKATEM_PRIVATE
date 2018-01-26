/*
 * Socket.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: yusuf
 */

#include "TcpSocket.h"


using namespace std;
extern void printTicked();

TcpSocket::TcpSocket()
{
	// TODO Auto-generated constructor stub
//	free(gServerSocket);
}



TcpSocket::~TcpSocket()
{
	// TODO Auto-generated destructor stub
	close(gSocket);
}


int TcpSocket::createServerSocket(int Port)
{

	unsigned char Data[DATA_PACKAGE_SIZE];
	int *new_socket;
	//Create socket
	gServerSocket = socket(AF_INET , SOCK_STREAM , 0);

	if (gServerSocket == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(Port);

	//Bind
	if( bind(gServerSocket,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");

	//Listen
	listen(gServerSocket , 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	gIncomingSocket = sizeof(struct sockaddr_in);

	gClientSocket = accept(gServerSocket, (struct sockaddr *)&client, (socklen_t*)&gIncomingSocket);
   if (gClientSocket < 0)
	{
		perror("accept failed");
		return FAIL;
	}
   else
   {
	   printf("Connection accepted\n");
   }


}



int TcpSocket::receiveDatafromClient(unsigned char *Data)
{
	int read_size;
	int remain_size;
	int available_data_length;

	unsigned char buffer[DATA_PACKAGE_SIZE];

	if( (read_size = recv(gClientSocket , &buffer[0] , DATA_PACKAGE_SIZE , 0)) < 0)
	{
		 cout << "receive failed!" << endl;
		 return FAIL;
	}
	else if(read_size == DATA_PACKAGE_SIZE)
	{
		available_data_length = DATA_PACKAGE_SIZE;
		memcpy(&Data[0], &buffer[0] , available_data_length);
	}
	else if(read_size < DATA_PACKAGE_SIZE)
	{
		available_data_length = read_size;
		remain_size = DATA_PACKAGE_SIZE - read_size;

		memcpy(&Data[0], &buffer[0] , available_data_length);

		read_size = recv(gClientSocket , &buffer[0] , remain_size , 0);
		if(read_size != remain_size)
			cout << "read_size != remain_size" << endl;

		memcpy(&Data[available_data_length], &buffer[0], remain_size);

		available_data_length += read_size;

		if(available_data_length != DATA_PACKAGE_SIZE)
			cout << "package size error!" << endl;
	}



	return available_data_length;
}



int TcpSocket::connectServer(char* Ip, int Port)
{

	 struct sockaddr_in server;
	 int ret;

	 server.sin_addr.s_addr = inet_addr(Ip);
	 server.sin_family = AF_INET;
	 server.sin_port = htons( Port );

	 gSocket = socket(AF_INET , SOCK_STREAM , 0);

	if (gSocket == FAIL)
	{
		printf("Could not create socket\n");
	}
	puts("Socket created");

	    //Connect to remote server
	ret = connect(gSocket , (struct sockaddr *)&server , sizeof(server));
	if ( ret == FAIL)
	{
		close(gSocket);
		gSocket = FAIL;
		printf("Server Connect is failed\n");
		return FAIL;
	}

	printf("Server Connect is Succesfull\n");



	return SUCCESS;

}



int TcpSocket::sendDatatoServer(unsigned char *Message)
{

    int ret;

	ret = send(gSocket,Message , DATA_PACKAGE_SIZE , 0);
	if(ret < FAIL)
	{
		printf("Data Package Send is failed and Socked is closed\n");
		close(gSocket);
		gSocket = FAIL;
		return FAIL;
	}
	else if(ret == 0)
	{
		printf("Data Package Send is failed and Socked is closed\n");
		close(gSocket);
		gSocket = FAIL;
		return FAIL;
	}
	else
	{
//		printf("Data Package Send is Succesful\n");
		return SUCCESS;
	}

}



int TcpSocket::listenServer()
{

	thread socket_tread(&TcpSocket::checkData, this, gSocket, DATA_PACKAGE_SIZE);
	socket_tread.detach();

	return 0;

}



void TcpSocket::checkData( int Socket, int Size )
{

	int ret;
	unsigned char server_reply[DATA_PACKAGE_SIZE];

	while(true)
	{
		ret = recv(Socket , server_reply , DATA_PACKAGE_SIZE , 0);
		if( ret == 0 )
		{
			printf("Server Listening is Failed And Socket Closed\n");
			close(gSocket);
			gSocket = FAIL;
			break;
		}
		printf("Server is repliying... \n");
		for (int i = 0; i<DATA_PACKAGE_SIZE; i++)
			printf("%02X-", server_reply[i]);
		printf("\n");
		acceptDataPackage(&server_reply[0]);

		memset(server_reply, NULL, Size);
	}

}



int TcpSocket::acceptDataPackage(unsigned char* Package)
{



	return SUCCESS;

}


int TcpSocket::recieveDatafromServer(unsigned char* Message)
{
	int ret;

	ret = recv(gSocket , Message , DATA_PACKAGE_SIZE , 0);
	if( ret == 0 )
	{
		printf("Server recieved is Failed And Socket Closed\n");
		close(gSocket);
		gSocket = FAIL;
		return FAIL;
	}
	else if (ret < 0)
	{
		printf("Server recieved is Failed And Socket Closed\n");
		close(gSocket);
		gSocket = FAIL;
		return FAIL;
	}
}


