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
    tracking.detach();

    return 0;
}

float LaserTracker::getDiagonalRate()
{
    float diagonal_rate;

    gmMutex.lock();
    diagonal_rate = gmPerspective.diagonal_rate;
    gmMutex.unlock();

    return diagonal_rate;

}

float LaserTracker::getEdgeRate()
{

    float edge_rate;

    gmMutex.lock();
    edge_rate = gmPerspective.edge_rate;
    gmMutex.unlock();

    return edge_rate;

}



int LaserTracker::startTracking()
{




    std::vector<cv::Vec3f> red_circles;

    while(true)
    {

        if(!mVideoCapture->read(gmFrame))
            break;

        gmScalarFrame = detectRed(gmFrame);

        red_circles = detectCircle(gmScalarFrame);

        drawFSOFace(red_circles);

        //show the frame
//        cv::imshow("frame", gmFrame);

        cv::waitKey(1); // needed

    }

    printf("The Source Connection has been faild.");
    return FAIL;

}


int LaserTracker::orderpoints(std::vector<cv::Point>& Points)
{
    int distance[4];

    for(int i=0; i<4 ; i++)
    {
        distance[i] = (Points[i].x * Points[i].x) + (Points[i].y * Points[i].y);
        distance[i] = sqrt(distance[i]);
    }

    for(int i=0; i<4-1; i++)
    {
        for(int k=0; k<4-i-1; k++)
        {
            if(distance[k] < distance[k+1])
            {
                std::swap(distance[k], distance[k+1]);
                std::swap(Points[k], Points[k+1]);
            }
        }
    }


    std::swap(Points[2], Points[3]);


    return 0;
}

int LaserTracker::calculatePerspective(std::vector<cv::Point> &Points)
{

    static float last_left_diagonal = 0, last_right_diagonal = 0;
    static float last_upper_edge = 0, last_bottom_edge = 0;

    float left_diagonal = 0, right_diagonal = 0;
    float upper_edge = 0, bottom_edge = 0;


    left_diagonal = std::abs(Points[0].x  - Points[2].x)^2 + std::abs(Points[0].y - Points[2].y)^2;
    left_diagonal = (float)sqrt(left_diagonal);

    upper_edge = std::abs(Points[2].x  - Points[1].x)^2 + std::abs(Points[2].y - Points[1].y)^2;
    upper_edge = (float)sqrt(upper_edge);

    if(last_left_diagonal != 0)
        last_left_diagonal = (last_left_diagonal + left_diagonal) / 2;

    if(last_upper_edge != 0)
        last_upper_edge = (last_upper_edge + upper_edge) / 2;


    right_diagonal = std::abs(Points[1].x  - Points[3].x)^2 + std::abs(Points[1].y - Points[3].y)^2;
    right_diagonal = (float)sqrt(right_diagonal);

    bottom_edge = std::abs(Points[3].x  - Points[0].x)^2 + std::abs(Points[3].y - Points[0].y)^2;
    bottom_edge = (float)sqrt(bottom_edge);


    if(last_right_diagonal != 0)
        last_right_diagonal = (last_right_diagonal + right_diagonal) / 2;
    if(last_bottom_edge != 0)
        last_bottom_edge = (last_bottom_edge + bottom_edge) / 2;


//    std::cout << "Diagonal Rate - " << left_diagonal / right_diagonal <<  std::endl;
//    std::cout << "Edge Rate - " << upper_edge / bottom_edge <<  std::endl;

    gmMutex.lock();
    gmPerspective.diagonal_rate = left_diagonal / right_diagonal;
    gmPerspective.edge_rate = upper_edge / bottom_edge;
    gmMutex.unlock();

    last_left_diagonal = left_diagonal;
    last_right_diagonal = right_diagonal;

    last_bottom_edge = bottom_edge;
    last_upper_edge = upper_edge;

    return 0;

}




cv::Mat LaserTracker::detectRed(cv::Mat &Frame)
{
    cv::Mat frame_hsv;
    cv::Mat frame_processed;

    //adding blur across noise
    cv::medianBlur(Frame, Frame, 5);

    //converting brg to hsv
    cv::cvtColor(Frame, frame_hsv, cv::COLOR_BGR2HSV);



    // Threshold the HSV image, keep only the red pixels
    cv::inRange(frame_hsv, cv::Scalar(0, 0, 254), cv::Scalar(0, 0, 255), frame_processed);

//      cv::imshow("frame1", frame_hsv);
//      cv::waitKey(1);

    cv::GaussianBlur(frame_processed, frame_processed, cv::Size(9, 9), 2, 2);

    return frame_processed;
}



std::vector<cv::Vec3f> LaserTracker::detectCircle(cv::Mat &Frame)
{

    std::vector<cv::Vec3f> circles;

   // Use the Hough transform to detect circles in the image
    cv::HoughCircles(Frame, circles, cv::HOUGH_GRADIENT, 1, 50, 100, 17, 5, 20); // change the last two parameters
//    cv::HoughCircles(Frame, circles, cv::HOUGH_GRADIENT, 1, Frame.rows/8);                                                                          // (min_radius & max_radius) to detect larger circles

    // Loop over all detected circles and outline them on the original image
     if( circles.size() == 0 )
     {

         gmMutex.lock();
         gmPerspective.diagonal_rate = 0;
         gmPerspective.edge_rate = 0;
         gmMutex.unlock();

         return circles;
     }
     else
         return circles;

}



int LaserTracker::drawFSOFace(const std::vector<cv::Vec3f>& Circles)
{

    std::vector<cv::Point> points;
    cv::Scalar colors[4];
    int radius;


    colors[0] = cv::Scalar(255,0,0);
    colors[1] = cv::Scalar(0,255,0);
    colors[2] = cv::Scalar(0,0,255);
    colors[3] = cv::Scalar(125,125,125);

    if(Circles.size() == LASER_POINTER_NUMBER)
    {
        for(size_t current_circle = 0; current_circle < Circles.size(); ++current_circle)
            points.push_back(cv::Point(std::round(Circles[current_circle][0]), std::round(Circles[current_circle][1])));

        for(size_t current_circle = 0; current_circle < Circles.size(); ++current_circle)
        {
            radius = std::round(Circles[current_circle][2]);
            cv::circle(gmScalarFrame, points[current_circle], 10, cv::Scalar(116, 100, 100), 5);
        }

        orderpoints(points);

        calculatePerspective(points);

        for(size_t i = 0; i < 4; ++i)
        {
            cv::circle(gmFrame, points[i], 10, colors[i], 5);
        }

        cv::fillConvexPoly(gmScalarFrame, points.data(), 4, cv::Scalar(116, 100, 100), cv::LINE_AA, 0);

//        cv::imshow("red_scaler_frame", gmScalarFrame);
//        cv::imshow("frame", gmFrame);

        points.clear();

    }
    else
    {
        gmMutex.lock();
        gmPerspective.diagonal_rate = 2;
        gmPerspective.edge_rate = 2;
        gmMutex.unlock();
    }

}



