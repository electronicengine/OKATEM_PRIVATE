#include "videostream.h"
#include <opencv2/opencv.hpp>
#include <string.h>

VideoStream::VideoStream()
{

}


void VideoStream::start(const std::string &IpAddress, int Port)
{
    gmSocket.openPort(Port, NORMAL_MODE);

    std::thread play(&VideoStream::playStream, this);
    play.detach();
}


void VideoStream::playStream()
{

    std::vector<unsigned char> socket_message; // Size of received message
    unsigned char *frame_data;

    clock_t last_cycle = clock();

    std::cout << "playing stream" << std::endl;

    while (1)
    {

        socket_message = gmSocket.receiveData();

        if(socket_message.size() == STREAM_SIZE)
        {

            int total_pack = socket_message[3] << 24 | socket_message[2] << 16 | socket_message[1] << 8 | socket_message[0];
            int sequence_number = socket_message[7] << 24 | socket_message[6] << 16 | socket_message[5] << 8 | socket_message[4];

//            std::cout << sequence_number << "/" << total_pack << std::endl;

            if(sequence_number == 1)
                frame_data = new unsigned char[(STREAM_SIZE -8) * total_pack];


            memcpy(&frame_data[(sequence_number - 1) * (STREAM_SIZE - 8)], &socket_message[8], STREAM_SIZE - 8);

            if(sequence_number == total_pack)
            {

               cv::Mat rawData = cv::Mat(1, (STREAM_SIZE -8) * total_pack, CV_8UC1, frame_data);
               cv::Mat frame = cv::imdecode(rawData, CV_LOAD_IMAGE_COLOR);
               if (frame.size().width == 0) {
                   std::cout << "decode failure!" << std::endl;
                   continue;
               }

               std::string as = "hello";

               cv::imshow(as.c_str(), frame);
               free(frame_data);

               cv::waitKey(1);

            }
        }

    }


}
