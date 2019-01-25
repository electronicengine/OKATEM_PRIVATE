#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <iostream>
#include <string>
#include <QPixmap>
#include <functional>
#include "udpsocket.h"
#include "ui_mainwindow.h"
#include "socketlistener.h"

#include <QThread>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>



class MainWindow;

class VideoStream : public SocketListener
{
public:

    VideoStream(UdpSocket *Socket) : SocketListener(Socket){ gpSocket = Socket; }
    virtual ~VideoStream(){ gmStreamStop = true; }

    int start(const std::string &IpAddress, int Port, MainWindow* Window);
    void stop();

    void socketDataCheckCall();


private:

    UdpSocket *gpSocket;
    std::string gmIpAddress;
    int gmPort;

    MainWindow *gpWindow;

    volatile bool gmStreamStop = false;

    int putStreamDataIntoBuffer(std::vector<unsigned char> &DataBuffer, unsigned char *DataIn, int Size);
    int checkPackageAccuracy(STREAM_DATA_FORMAT &StreamData);
    int checkSocketCondition(clock_t &LastDataComming);
    int checkifStreamPacket(std::vector <unsigned char> &Package);
    int restartSocket(MainWindow *Window);
    int convertPackageToMat(std::vector<unsigned char> FrameData, cv::Mat &Frame);
    void showInScreen(cv::Mat &Frame, MainWindow *Window);
    void playStream(MainWindow *Window);
    QImage cvMatToQImage( const cv::Mat &inMat );
};



#endif // VIDEOSTREAM_H
