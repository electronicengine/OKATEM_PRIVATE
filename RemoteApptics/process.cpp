#include "process.h"
#include "kalmanfilter.h"

Process::Process()
{

}

double Process::calculateMagnitude(const cv::Point &P)
{
    double magnitude;
    magnitude = (P.x * P.x) + (P.y * P.y);
    magnitude = sqrt(magnitude);

    return magnitude;
}

cv::Point Process::calculateCenter(std::vector<cv::Point> &Points)
{

    int size = Points.size();
    int x = 0, y = 0;

    if(size < 2)
        return cv::Point(0, 0);

    for(int i = 0; i<size; i++)
    {

        x +=(double) Points[i].x;
        y +=(double) Points[i].y;
    }

    x = (double)x / size;
    y = (double)y / size;

    return cv::Point(x, y);
}

cv::Point Process::findMidPoint(const cv::Point &P1, const cv::Point &P2)
{
    cv::Point m;
    m.x=((P1.x + P2.x) / 2);
    m.y=((P1.y + P2.y) / 2);

    return m;
}

void Process::eliminateColors(cv::Mat &Frame)
{

    //adding blur across noise
//    cv::medianBlur(Frame, Frame, 11);

    //converting brg to hsv
    cv::cvtColor(Frame, Frame, cv::COLOR_BGR2HSV);

    // Threshold the HSV image, keep only the red pixels
    cv::inRange(Frame, cv::Scalar(0, 0, 100), cv::Scalar(0, 0, 255), Frame);

//    cv::GaussianBlur(Frame, Frame, cv::Size(9, 9), 5, 5);

}



void Process::eliminateUnnecessaryPoints(std::vector<cv::Point> &Points)
{

    std::vector<double> magnitudes;

    for(size_t i=0; i<Points.size(); i++)
        magnitudes.push_back(calculateMagnitude(Points[i]));

    eliminateCloserPoints(Points, magnitudes);
//    eliminateUnshapedPoints(Points);


}



void Process::eliminateCloserPoints(std::vector<cv::Point> &Points, std::vector<double> &Magnitudes)
{
    for(size_t i=0; i<Points.size(); i++)
    {
        for(size_t k=0; k<Points.size(); k++)
        {
            if(k != i)
            {
                if(std::abs(Magnitudes[i] - Magnitudes[k]) < 20)
                {

                    Points.erase(Points.begin() + k, Points.begin() + k + 1);
                    Magnitudes.erase(Magnitudes.begin() + k, Magnitudes.begin() + k + 1);

                }
            }
        }
    }
}



void Process::eliminateUnshapedPoints(std::vector<cv::Point> &Points)
{


    std::vector<cv::Point> point_pair1;
    std::vector<cv::Point> point_pair2;

    for(size_t i = 0; i<Points.size(); i++)
        std::cout << std::to_string(i) << "- x:" << std::to_string(Points[i].x)
                                       << " y:" << std::to_string(Points [i].y) << std::endl;

    std::cout << "----" << std::endl;
    point_pair1 = findPointPair(Points);

    point_pair2 = findPointPair(Points);


    Points.clear();

    Points.push_back(point_pair1[0]);
    Points.push_back(point_pair1[1]);
    Points.push_back(point_pair2[0]);
    Points.push_back(point_pair2[1]);

    for(size_t i = 0; i<Points.size(); i++)
        std::cout << std::to_string(i) << "- x:" << std::to_string(Points[i].x)
                                       << " y:" << std::to_string(Points[i].y) << std::endl;

    std::cout << "****" << std::endl;



//    Points = points;
}

std::vector<cv::Point> Process::findPointPair(std::vector<cv::Point> &Points)
{


    std::vector<cv::Point> points;

    for(size_t i=0; i<Points.size(); i++)
    {
        for(size_t k=0; k<Points.size(); k++)
        {
            if(i != k)
            {
                if(std::abs(Points[i].x - Points[k].x) < 10 ||
                    std::abs(Points[i].y - Points[k].y) < 10)
                {
                    std::cout << "size: " << std::to_string(Points.size()) << std::endl;
                    std::cout << "xk:" << std::to_string(Points[k].x) << " yk:" << std::to_string(Points[k].y) << std::endl;
                    std::cout << "xi:" << std::to_string(Points[i].x) << " yi:" << std::to_string(Points[i].y) << std::endl;
                    std::cout << std::endl;

                    points.push_back(Points[i]);
                    points.push_back(Points[k]);

                    Points.erase(Points.begin() + i, Points.begin() + i + 1);
                    Points.erase(Points.begin() + k, Points.begin() + k + 1);

                    return points;
                }

            }
        }
    }
    return points;
}

std::vector<cv::Point> Process::detectContoursCenter(cv::Mat &Frame)
{


    int thresh = 100;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Point> points;
    cv::Mat canny_output;

    /// Detect edges using canny
    cv::Canny( Frame, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    cv::findContours(canny_output, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    /// Detect counter center
    for( size_t i = 0; i< contours.size(); i++ )
    {
        cv::Moments m = cv::moments(contours[i], true);
        points.push_back(cv::Point(m.m10/m.m00, m.m01/m.m00));
    }
    cv::Mat colorly;

    cv::cvtColor(canny_output, colorly, CV_GRAY2BGR);


    return points;

}


void Process::drawTarget(const cv::Mat &Frame)
{
    cv::Point p1, p2, p3, p4;

    p1 = cv::Point(0, 240);
    p2 = cv::Point(640, 240);

    p3 = cv::Point(320, 0);
    p4 = cv::Point(320, 480);

    cv::line(Frame, p1, p2,  cv::Scalar(0,0,255));
    cv::line(Frame, p3, p4,  cv::Scalar(0,0,255));

}

void Process::drawFSOFace(const std::vector<cv::Vec3f> &Circles)
{

    std::vector<cv::Point> points;
    cv::Scalar colors[4];
//    int radius;

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
//            radius = std::round(Circles[current_circle][2]);
//            cv::circle(gmScalarFrame, points[current_circle], radius, cv::Scalar(116, 100, 100), 5);
        }

        orderpoints(points);

//        calculatePerspective(points);

//        for(size_t i = 0; i < 4; ++i)
//        {
//            cv::circle(gmFrame, points[i], 10, colors[i], 5);
//        }

//        cv::fillConvexPoly(gmScalarFrame, points.data(), 4, cv::Scalar(116, 100, 100), cv::LINE_AA, 0);

//        cv::imshow("red_scaler_frame", gmScalarFrame);
//        cv::imshow("frame", gmFrame);

        points.clear();

    }
    else
    {
//        gmMutex.lock();
//        gmPerspective.diagonal_rate = 2;
//        gmPerspective.edge_rate = 2;
//        gmMutex.unlock();
    }
}

void Process::orderpoints(std::vector<cv::Point> &Points)
{
    int distance[LASER_POINTER_NUMBER];

    for(int i=0; i<4 ; i++)
        distance[i] = calculateMagnitude(Points[i]);


    for(int i=0; i<LASER_POINTER_NUMBER-1; i++)
    {
        for(int k=0; k<LASER_POINTER_NUMBER-i-1; k++)
        {
            if(distance[k] < distance[k+1])
            {
                std::swap(distance[k], distance[k+1]);
                std::swap(Points[k], Points[k+1]);
            }
        }
    }

    std::swap(Points[2], Points[3]);

}

int Process::calculatePerspective(std::vector<cv::Point> &Points)
{

    static float last_left_diagonal = 0, last_right_diagonal = 0;
    static float last_upper_edge = 0, last_bottom_edge = 0;

    float left_diagonal = 0, right_diagonal = 0;
    float upper_edge = 0, bottom_edge = 0;


    left_diagonal = ((std::abs(Points[0].x  - Points[2].x))^2) + ((std::abs(Points[0].y - Points[2].y))^2);
    left_diagonal = (float)sqrt(left_diagonal);

    upper_edge = ((std::abs(Points[2].x  - Points[1].x))^2) + ((std::abs(Points[2].y - Points[1].y))^2);
    upper_edge = (float)sqrt(upper_edge);

    if(last_left_diagonal != 0)
        last_left_diagonal = (last_left_diagonal + left_diagonal) / 2;

    if(last_upper_edge != 0)
        last_upper_edge = (last_upper_edge + upper_edge) / 2;


    right_diagonal = ((std::abs(Points[1].x  - Points[3].x))^2) + ((std::abs(Points[1].y - Points[3].y))^2);
    right_diagonal = (float)sqrt(right_diagonal);

    bottom_edge = ((std::abs(Points[3].x  - Points[0].x))^2) + ((std::abs(Points[3].y - Points[0].y))^2);
    bottom_edge = (float)sqrt(bottom_edge);


    if(last_right_diagonal != 0)
        last_right_diagonal = (last_right_diagonal + right_diagonal) / 2;
    if(last_bottom_edge != 0)
        last_bottom_edge = (last_bottom_edge + bottom_edge) / 2;

//    gmMutex.lock();
//    gmPerspective.diagonal_rate = left_diagonal / right_diagonal;
//    gmPerspective.edge_rate = upper_edge / bottom_edge;
//    gmMutex.unlock();

    last_left_diagonal = left_diagonal;
    last_right_diagonal = right_diagonal;

    last_bottom_edge = bottom_edge;
    last_upper_edge = upper_edge;

    return 0;

}

