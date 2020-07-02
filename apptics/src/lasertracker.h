#ifndef LASERTRACKER_H
#define LASERTRACKER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mutex>

#include "globals.h"
#include "queue.h"
#include "udpsocket.h"
#include "mainoperation.h"

// Text properties which is printed on debug
#define TEXT_FONT cv::FONT_HERSHEY_COMPLEX_SMALL
#define TEXT_SCALE 2
#define TEXT_THICKNESS 2


#define CAPTURE_RATE 30

#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480

#define ENCODE_QUALITY 80

#define LASER_POINTER_NUMBER 4


struct PERSPECTIVE_RATE
{
  float diagonal_rate;    // left/right
  float edge_rate;        // upper/bottom
};


class LaserTracker : public MainOperation
{

public:

    LaserTracker(MainOperation *Operation);
    ~LaserTracker();
    int startTracking();
    int runTracking();
    float getDiagonalRate();  // left/right
    float getEdgeRate();      //upper/bottom

    void streamFrame(cv::Mat Frame);

    int init(int Camera, const std::string &StreamIp, int StreamPort);

private:

    PERSPECTIVE_RATE gmPerspective;
    UdpSocket gmStreamSocket;

    std::mutex gmMutex;
    cv::Mat detectRed(cv::Mat &Frame);
    std::vector<cv::Vec3f> detectCircle(cv::Mat &Frame);
    cv::VideoCapture *mVideoCapture;

    cv::Mat gmFrame;
    cv::Mat gmScalarFrame;

    int setCameraGain();
    int drawTarget(const cv::Mat &Frame);
    int drawFSOFace(const std::vector<cv::Vec3f>& Circles);
    int orderpoints(std::vector<cv::Point>& Points);
    int calculatePerspective(std::vector<cv::Point>& Points);

};

#endif // LASERTRACKER_H
