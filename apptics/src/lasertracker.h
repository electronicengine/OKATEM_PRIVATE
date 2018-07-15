﻿#ifndef LASERTRACKER_H
#define LASERTRACKER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Text properties which is printed on debug
#define TEXT_FONT cv::FONT_HERSHEY_COMPLEX_SMALL
#define TEXT_SCALE 2
#define TEXT_THICKNESS 2


#define CAPTURE_RATE 30

#define FRAME_WIDTH 320
#define FRAME_HEIGHT 240

#define FAIL -1
#define SUCCESS 0

#define LASER_POINTER_NUMBER 4

class LaserTracker
{
private:
        cv::Mat detectRed(cv::Mat &Frame);
        std::vector<cv::Vec3f> detectCircle(cv::Mat &Frame);
        cv::VideoCapture *mVideoCapture;

        cv::Mat gmFrame;
        cv::Mat gmScalarFrame;

        int drawFSOFace(const std::vector<cv::Vec3f>& Circles);
        int orderpoints(std::vector<cv::Point>& Points);
        int calculatePerspective(std::vector<cv::Point>& Points);
public:
        LaserTracker(const std::string VideoLocation);
        LaserTracker(int Camera);
        ~LaserTracker();
        int startTracking();
        int runTracking();
};

#endif // LASERTRACKER_H
