#include "lasertracker.h"
#include <thread>
#include <pthread.h>

LaserTracker::LaserTracker(const std::string VideoLocation)
{
    mVideoCapture = new cv::VideoCapture(VideoLocation);

    mVideoCapture->set(CV_CAP_PROP_FPS, CAPTURE_RATE);
    if (!mVideoCapture->isOpened())
           printf("LaserTracker init is Failed\n");
}

LaserTracker::LaserTracker(int Camera)
{
    mVideoCapture = new cv::VideoCapture(Camera);

    mVideoCapture->set(CV_CAP_PROP_FPS, CAPTURE_RATE);
    if (!mVideoCapture->isOpened())
        printf("LaserTracker init is Failed\n");
}



LaserTracker::~LaserTracker()
{


}



int LaserTracker::runTracking()
{
    std::thread tracking(&LaserTracker::startTracking, this);
    tracking.join();

    return 0;
}


int LaserTracker::startTracking()
{

    cv::Mat bgr_frame;
    cv::Mat frame;
    cv::Mat red_scalar_frame;
    cv::Vec3f red_circle;

    while(true)
    {
        if(!mVideoCapture->read(frame))
            break;

        red_scalar_frame = detectRed(frame);
        red_circle = detectCircle(red_scalar_frame);

        //draw a point on red circle
        cv::circle(frame, cv::Point(red_circle[0], red_circle[1]), red_circle[3], cv::Scalar(9,255,0), 3, cv::LINE_AA);

        //show the frame
        cv::imshow("Debug_win", frame);
        cv::waitKey(1); // needed

//        for(int i=0; i<1000; i++)
//            printf("%02X-", frame.data[i]);
//        printf("\n");

    }

    printf("The Source Connection has been faild.");
    return FAIL;

}



cv::Mat LaserTracker::detectRed(cv::Mat &Frame)
{
    cv::Mat frame_hsv;
    cv::Mat frame_processed;

    //adding blur across noise
    cv::medianBlur(Frame, Frame, 3);

    //converting brg to hsv
    cv::cvtColor(Frame, frame_hsv, cv::COLOR_BGR2HSV);

    // Threshold the HSV image, keep only the red pixels
    cv::inRange(frame_hsv, cv::Scalar(0, 0, 250), cv::Scalar(1, 1, 255), frame_processed);

    cv::GaussianBlur(frame_processed, frame_processed, cv::Size(9, 9), 2, 2);



    return frame_processed;

}

cv::Vec3f LaserTracker::detectCircle(cv::Mat &Frame)
{

    std::vector<cv::Vec3f> circles;


    // Use the Hough transform to detect circles in the image
    cv::HoughCircles(Frame, circles, cv::HOUGH_GRADIENT, 1, 20, 100, 100, 3, 10); // change the last two parameters
//    cv::HoughCircles(Frame, circles, cv::HOUGH_GRADIENT, 1, Frame.rows/8);                                                                          // (min_radius & max_radius) to detect larger circles

    // Loop over all detected circles and outline them on the original image
     if(circles.size() == 0)
     {
         printf("Circle can not Find\n");
         return FAIL;
     }
     else
     {
         std::cout << "x= " << circles[0][0] << " y= " << circles[0][1] << "angle: " << circles[0][3] << std::endl;
         return circles[0];
     }


}
