#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <iostream>
#include <string>

#include "udpsocket.h"

class VideoStream
{
public:
    VideoStream();

    void start(const std::string &IpAddress, int Port);


private:

    UdpSocket gmSocket;

    void playStream();
};

#endif // VIDEOSTREAM_H
