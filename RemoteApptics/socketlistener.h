#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H

#include "udpsocket.h"
#include <iostream>


class SocketListener
{


public:
    SocketListener(UdpSocket *Socket)
    {
        gpSocket = Socket;

        gpSocket->attach(this);
    }

   virtual ~SocketListener(){}


    virtual void socketDataCheckCall() = 0;


protected:



    UdpSocket *getSocket(){
           return gpSocket;
       }

private:
    UdpSocket *gpSocket;






};

#endif // SOCKETOBSERVER_H
