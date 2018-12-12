#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <iostream>
#include <string>
#include <QPixmap>
#include <functional>
#include "udpsocket.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>



class MainWindow;

class VideoStream
{
public:
    VideoStream();
    ~VideoStream();

    int start(const std::string &IpAddress, int Port, MainWindow* Window);
    void stop();

private:

    UdpSocket gmSocket;
    std::string gmIpAddress;
    int gmPort;

    MainWindow *gpWindow;

    volatile bool gmStreamStop = false;

    int putStreamDataIntoBuffer(std::vector<unsigned char> &DataBuffer, unsigned char *DataIn, int Size);
    STREAM_DATA_FORMAT checkPackageAccuracy(std::vector <unsigned char> &Package);
    int checkSocketCondition(clock_t &LastDataComming);
    int checkifStreamPacket(std::vector <unsigned char> &Package);
    int restartSocket(MainWindow *Window);
    int convertPackageToMat(std::vector<unsigned char> FrameData, cv::Mat &Frame);
    void showInScreen(cv::Mat &Frame, MainWindow *Window);
    void playStream(MainWindow *Window);
    QImage cvMatToQImage( const cv::Mat &inMat );
};



#endif // VIDEOSTREAM_H
