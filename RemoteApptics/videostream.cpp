#include "videostream.h"
#include <string.h>
#include <opencv2/opencv.hpp>

#include "mainwindow.h"
#include "camerapanel.h"



VideoStream::VideoStream(UdpSocket *Socket) : SocketListener(Socket){ gpSocket = Socket; }

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

        gpCameraPanel = Panel;

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
                    gpCameraPanel->displayCallBack(frame);

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

        if (frame.size().width == 0)
        {
            std::cout << "decode failure!" << std::endl;
            return FAIL;
        }

        Frame = frame;

        return SUCCESS;
    }
    catch(cv::Exception &ex)
    {
        std::cout << "Decompressing Mat: " << ex.what() << std::endl;
        return FAIL;
    }


}











