#ifndef Process_H
#define Process_H

#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mutex>

#include "queue.h"
#include "udpsocket.h"
#include "camerapanel.h"

// Text properties which is printed on debug
#define TEXT_FONT cv::FONT_HERSHEY_COMPLEX_SMALL
#define TEXT_SCALE 2
#define TEXT_THICKNESS 2


#define CAPTURE_RATE 30

#define FRAME_WIDTH 960
#define FRAME_HEIGHT 720

#define ENCODE_QUALITY 80

#define LASER_POINTER_NUMBER 4
#define DISTANCE_TRESHOLD   10

class Process
{
public:
    Process();


private:


    std::mutex gmMutex;

    cv::Mat gmFrame;
    cv::Mat gmScalarFrame;
    static double calculateMagnitude(const cv::Point &P);
    static cv::Point findMidPoint(const cv::Point &P1, const cv::Point &P2);

public:
    static void eliminateColors(cv::Mat &Frame);
    static void eliminateUnnecessaryPoints(std::vector<cv::Point>& Points);
    static void eliminateCloserPoints(std::vector<cv::Point> &Points, std::vector<double> &Magnitudes);
    static void eliminateUnshapedPoints(std::vector<cv::Point> &Points);
    static std::vector<cv::Point> findPointPair(std::vector<cv::Point> &Points);
    static cv::Point calculateCenter(const std::vector<cv::Point> &Points);
    static void drawTarget(const cv::Mat &Frame);
    static void drawFSOFace(const std::vector<cv::Vec3f>& Circles);
    static void orderpoints(std::vector<cv::Point>& Points);
    int calculatePerspective(std::vector<cv::Point>& Points);
    static std::vector<cv::Point> detectContoursCenter(cv::Mat &Frame);
};
#endif // Process_H
