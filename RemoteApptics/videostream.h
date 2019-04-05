#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <iostream>
#include <string>
#include <QPixmap>
#include <functional>
#include "udpsocket.h"
#include "socketlistener.h"

#include <QThread>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>



class MainWindow;
class CameraPanel;

class VideoStream : public SocketListener
{
public:

    VideoStream(UdpSocket *Socket);
    virtual ~VideoStream()
    {
        gpSocket->terminate();
    }

    int start(const std::string &IpAddress, int Port, CameraPanel* Panel);
    int terminate();

    void socketDataCheckCall();

private:

    UdpSocket *gpSocket;
    std::string gmIpAddress;
    int gmPort;

    CameraPanel *gpCameraPanel;

    volatile bool gmStreamStop = false;

    int putStreamDataIntoBuffer(std::vector<unsigned char> &DataBuffer, unsigned char *DataIn, int Size);
    int checkPackageAccuracy(STREAM_DATA_FORMAT &StreamData);
    int checkSocketCondition(clock_t &LastDataComming);
    int checkifStreamPacket(std::vector <unsigned char> &Package);
    int convertPackageToMat(std::vector<unsigned char> FrameData, cv::Mat &Frame);
};



#endif // VIDEOSTREAM_H
