#include "videostream.h"
#include <string.h>
#include <opencv2/opencv.hpp>

#include "mainwindow.h"
#include "camerapanel.h"



int VideoStream::start(const std::string &IpAddress, int Port, CameraPanel *Panel)
{

    int ret;

    gmIpAddress = IpAddress;
    gmPort = Port;


    ret = gpSocket->init(IpAddress, Port);

    if(ret == FAIL)
        return FAIL;
    else
    {
        gmStreamStop = false;

        gpSocket->listen();

        gpPanel = Panel;

    }

    return SUCCESS;


}



int VideoStream::terminate()
{

    return gpSocket->terminate();
    return SUCCESS;

}

void VideoStream::socketDataCheckCall()
{
    int ret;

    static std::vector<unsigned char> frame_data;

    STREAM_DATA_FORMAT stream;

    cv::Mat frame;

    stream = gpSocket->getStreamData();

    if(stream.is_available == true)
    {

        ret = checkPackageAccuracy(stream);

        if(ret == SUCCESS)
        {

            putStreamDataIntoBuffer(frame_data, stream.data, STREAM_DATA_SIZE);

            if(stream.current_pack == stream.total_pack)  //if the last frame package
            {

                ret = convertPackageToMat(frame_data, frame);
                if(ret != FAIL)
                    gpPanel->printScreen(QPixmap::fromImage(cvMatToQImage(frame)));

                frame_data.clear();

            }
        }
        else
        {
            frame_data.clear();
        }
    }

}



int VideoStream::putStreamDataIntoBuffer(std::vector<unsigned char> &DataBuffer, unsigned char *DataIn, int Size)
{

    for(int i = 0; i < Size; i++)
    {
        DataBuffer.push_back(DataIn[i]);
    }

    return SUCCESS;

}



int VideoStream::checkPackageAccuracy(STREAM_DATA_FORMAT &StreamData)
{

    uint32_t total_pack;
    uint32_t sequence_number;
    static uint32_t package_counter = 0;

    total_pack = StreamData.total_pack;
    sequence_number = StreamData.current_pack;

    package_counter++;


    if(sequence_number != package_counter)
    {

        std::cout << "wrong package sequence: " << std::to_string(sequence_number) << "/" << package_counter << std::endl;

        package_counter = 0;

        return FAIL;
    }

    if(total_pack > 1000  || sequence_number > total_pack)
    {
        std::cout << "wrong total size" << std::endl;

        package_counter = 0;

        return FAIL;
    }

    if(total_pack == sequence_number)
        package_counter = 0;


    return SUCCESS;

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

        if(Package[0] == 'S' && Package[1] == 'T')
        {
            return SUCCESS;
        }

        return FAIL;
    }

    return FAIL;

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








