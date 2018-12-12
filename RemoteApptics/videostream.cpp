#include "videostream.h"
#include <string.h>
#include <opencv2/opencv.hpp>

#include "mainwindow.h"



VideoStream::VideoStream()
{

}



VideoStream::~VideoStream()
{
    gmStreamStop = true;
    gmSocket.closePort();
}



int VideoStream::start(const std::string &IpAddress, int Port, MainWindow *Window)
{

    int ret;

    ret = gmSocket.openPort(Port, NORMAL_MODE);
    gmIpAddress = IpAddress;
    gmPort = Port;

    if(ret == FAIL)
        return FAIL;
    else
    {
        gmStreamStop = false;

        std::thread play(&VideoStream::playStream, this, Window);
        play.detach();
    }

    return SUCCESS;


}



void VideoStream::stop()
{

    gmStreamStop = true;
    gmSocket.closePort();

}



int VideoStream::putStreamDataIntoBuffer(std::vector<unsigned char> &DataBuffer, unsigned char *DataIn, int Size)
{

    for(int i = 0; i < Size; i++)
    {
        DataBuffer.push_back(DataIn[i]);
    }

    return SUCCESS;

}



STREAM_DATA_FORMAT VideoStream::checkPackageAccuracy(std::vector<unsigned char> &Package)
{

    int total_pack;
    int sequence_number;
    static int package_counter = 0;

    UDP_DATA_FORMAT udp_data;
    STREAM_DATA_FORMAT stream_data;

//    std::cout << "st in" << std::endl;
    udp_data = Package.data();

    stream_data = udp_data;

    total_pack = stream_data.total_pack;
    sequence_number = stream_data.current_pack;

    package_counter++;

    if(sequence_number != package_counter)
    {
        package_counter = 0;

        stream_data.data_correct = false;
    }

    if(total_pack > 1000  || sequence_number > total_pack || total_pack < -1 )
    {
        package_counter = 0;

        stream_data.data_correct = false;
    }

    stream_data.data_correct = true;

    return stream_data;

}



int VideoStream::checkSocketCondition(clock_t &LastDataComming)
{
    clock_t now = 0;

    now = clock();

    if(now - LastDataComming >= 2000000 && LastDataComming != 0)
    {
        LastDataComming = now;


        std::cout << "stream timeout" << std::endl;
        return FAIL;
    }

    if(gmStreamStop == true)
    {

        std::cout << "Streamstop true" << std::endl;

        return FAIL;
    }

    return SUCCESS;

}



int VideoStream::checkifStreamPacket(std::vector<unsigned char> &Package)
{

    if(Package.size() != 0)
    {
//        std::cout << "pack in" << std::endl;

        if(Package[0] == 'S' && Package[1] == 'T')
        {
            return SUCCESS;
        }

        return FAIL;
    }

    return FAIL;

}



int VideoStream::restartSocket(MainWindow *Window)
{

    int ret;

    stop();

    usleep(1000);

    ret = start(gmIpAddress, gmPort, Window);

    return ret;

}



int VideoStream::convertPackageToMat(std::vector<unsigned char> FrameData, cv::Mat &Frame)
{

    try
    {
        cv::Mat rawData = cv::Mat(1, FrameData.size(), CV_8UC1, FrameData.data());
        cv::Mat frame = cv::imdecode(rawData, CV_LOAD_IMAGE_COLOR);
        cv::Mat scaled;

        if (frame.size().width == 0)
        {
            std::cout << "decode failure!" << std::endl;
            return FAIL;
        }

        cv::resize(frame, scaled, cv::Size(1024, 768));

        Frame = scaled;

        return SUCCESS;
    }
    catch(cv::Exception &ex)
    {
        std::cout << "Decompressing Mat: " << ex.what() << std::endl;
        return FAIL;
    }


}



void VideoStream::showInScreen(cv::Mat &Frame, MainWindow *Window)
{
    static int count = 0;

    count ++;

    if(count >= 50)
    {
        emit Window->screenClose();
        usleep(1000);
        count = 0;
        emit Window->screenShow();
        usleep(1000);
    }

    emit Window->refreshScreen(QPixmap::fromImage(cvMatToQImage(Frame)));

//    std::cout << "Comming Stream Packets: " << std::to_string(count) << std::endl;
}



void VideoStream::playStream(MainWindow *Window)
{

    int ret;

    clock_t last_time_data_comming = 0;

    std::vector<unsigned char> socket_message; // Size of received message
    std::vector<unsigned char> frame_data;
    STREAM_DATA_FORMAT stream;

    std::cout << "playing stream" << std::endl;

    cv::Mat frame;

    while(1)
    {

        ret = checkSocketCondition(last_time_data_comming);

        if(ret != SUCCESS)
        {
            restartSocket(Window);

            break;
        }

        socket_message = gmSocket.receiveData();

        ret = checkifStreamPacket(socket_message);

        if(ret == SUCCESS)
        {
            stream = checkPackageAccuracy(socket_message);

            if(stream.data_correct == true)
            {

                putStreamDataIntoBuffer(frame_data, stream.data, STREAM_DATA_SIZE);

                if(stream.current_pack == stream.total_pack)  //if the last frame package
                {
                    last_time_data_comming = clock();

                    ret = convertPackageToMat(frame_data, frame);
                    if(ret != FAIL)
                        showInScreen(frame, Window);

                    frame_data.clear();

                }
            }
            else
            {
                frame_data.clear();
                continue;
            }
        }
    }

}



QImage  VideoStream::cvMatToQImage( const cv::Mat &inMat )
{

    switch ( inMat.type() )
    {
     // 8-bit, 4 channel
     case CV_8UC4:
     {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
     }

     // 8-bit, 3 channel
     case CV_8UC3:
     {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
     }

     // 8-bit, 1 channel
     case CV_8UC1:
     {
    #if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Grayscale8 );
    #else
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if ( sColorTable.isEmpty() )
        {
           sColorTable.resize( 256 );

           for ( int i = 0; i < 256; ++i )
           {
              sColorTable[i] = qRgb( i, i, i );
           }
        }

        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );
    #endif

        return image;
     }

     default:
       std::cout << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type() << std::endl;
        break;
    }

    return QImage();
}








