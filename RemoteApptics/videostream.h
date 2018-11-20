#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <iostream>
#include <string>
#include <QPixmap>
#include <functional>
#include "udpsocket.h"

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

    template<typename OBJ>
    int start(const std::string &IpAddress, int Port, OBJ* Window)
    {

        int ret;

        ret = gmSocket.openPort(Port, NORMAL_MODE);
        gmIpAddress = IpAddress;

        if(ret == FAIL)
            return FAIL;
        else
        {
            std::thread play(&VideoStream::playStream<OBJ>, this, Window);
            play.detach();
        }

        return SUCCESS;
    }


private:

    UdpSocket gmSocket;
    std::string gmIpAddress;
    UDP_DATA_FORMAT udp_data;
    STREAM_DATA_FORMAT stream_data;


    QImage  cvMatToQImage( const cv::Mat &inMat );

    template<typename OBJ>
    void playStream(OBJ *Window)
    {

        std::vector<unsigned char> socket_message; // Size of received message
        unsigned char *frame_data;
        int total_pack;
        int sequence_number;

        bool allocated = 0;

            std::cout << "playing stream" << std::endl;

        while (1)
        {

            socket_message = gmSocket.receiveData();

            if(socket_message.size() == ETHERNET_TRANSFER_SIZE)
            {
                if(socket_message[0] == 'S' && socket_message[1] == 'T')
                {

                    udp_data = socket_message.data();

                    stream_data = udp_data;

                    total_pack = stream_data.total_pack;
                    sequence_number = stream_data.current_pack;

                    if((total_pack > 1000 && total_pack < -1) || (sequence_number > 1000 && total_pack < -1 ))
                        continue;

                    if(sequence_number == 1)
                    {
                        frame_data = new unsigned char[(STREAM_DATA_SIZE) * total_pack];
                        allocated = 1;
                    }

                    if(allocated == 1)
                        memcpy(&frame_data[(sequence_number - 1) * (STREAM_DATA_SIZE)], stream_data.data, STREAM_DATA_SIZE);
                    else
                        continue;

                    if(sequence_number == total_pack)
                    {

                        allocated = 0;
                       cv::Mat rawData = cv::Mat(1, (STREAM_DATA_SIZE -8) * total_pack, CV_8UC1, frame_data);
                       cv::Mat frame = cv::imdecode(rawData, CV_LOAD_IMAGE_COLOR);
                       if (frame.size().width == 0) {
                           std::cout << "decode failure!" << std::endl;
                           continue;
                       }



                       Window->streamFrameCallBack(frame);

                       free(frame_data);

                    }
                }

            }




        }
    }

};



#endif // VIDEOSTREAM_H
