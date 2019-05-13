#include "ui_autocontrolwindow.h"
#include "autolockingpanel.h"
#include "process.h"
#include "pidcontroller.h"
#include "kalmanfilter.h"

AutoLockingPanel::AutoLockingPanel(AutoControlWindow *Window) :
    AutoControlWindow(Window)
{
    attachToAutoControlWindow();
}

void AutoLockingPanel::markFSOPoints(cv::Mat &Frame, const std::vector<cv::Point> &Points)
{

    if(Points.size() == FSO_POINTS)
    {
        const cv::Scalar colors[Points.size()] = {cv::Scalar(0, 0, 255),
                                      cv::Scalar(0, 255, 0),
                                      cv::Scalar(255, 0, 0),
                                      cv::Scalar(255, 0, 255) };

        for(size_t i = 0; i < Points.size(); i++)
            cv::circle(Frame, Points[i], 5, colors[i], -1);
    }

}

void AutoLockingPanel::drawErrorVector(cv::Mat &Frame, const std::vector<cv::Point> &Points)
{

    std::vector<double> error_vector;

    cv::Point noisy_center;
    cv::Point clear_center;

    static KalmanFilter kalman_filter;

    if(Points.size() < FSO_POINTS)
    {
        error_vector = calculateErrorVector(gmTarget, gmFSOCenter);

        if(error_vector[2] < 20)
        {
            noisy_center = cv::Point(0, 0);
            std::cout << "closer" << std::endl;
        }
        else
        {
            noisy_center = Process::calculateCenter(Points);
        }

    }
    else
        noisy_center = Process::calculateCenter(Points);



    if(noisy_center.x > 0 && noisy_center.y > 0)
    {
        clear_center = kalman_filter.takeKalmanFilter(noisy_center);

        if((clear_center.x > 0 && clear_center.y > 0) && (clear_center.x < 1000 && clear_center.y < 1000))
        {

            gmMutex.lock();

                gmFSOCenter = clear_center;
                gmFSOPoints = Points;

            gmMutex.unlock();


            std::cout << "x:" << std::to_string(clear_center.x) <<
                         " y:" << std::to_string(clear_center.y) << std::endl;

            cv::line(Frame, clear_center, gmTarget, cv::Scalar(0,0,255)); // drawing Error Vector

            markFSOPoints(Frame, Points);
        }

    }


    cv::circle(Frame, gmFSOCenter, 5, cv::Scalar(255,255,255), -1); // Mark Center




}

void AutoLockingPanel::attachToAutoControlWindow()
{
}



void AutoLockingPanel::executeCommands()
{



    if(gmAutoLockingProcessing == false)
    {
        std::cout << "AutoLockingPanel::executeCommands()" << std::endl;

        gmAutoLockingProcessing = true;

        gmTarget = cv::Point(
                    autocontrol_ui->position_x->text().toInt(),
                    autocontrol_ui->position_y->text().toInt());

        std::thread locking_thread(&AutoLockingPanel::lockToTarget, this, gmTarget );
        locking_thread.detach();
    }


}



void AutoLockingPanel::lockToTarget(const cv::Point &Target)
{


    sleep(1);

    std::cout << "Locking is starting..." << std::endl;
    std::cout << "Target x:" << std::to_string(Target.x) <<
                 " Target y:" << std::to_string(Target.y) << std::endl;

    std::vector<double> error_vector;

    double stepmotor1_speed = 0;
    double stepmotor2_speed = 0;

    int ret;

    cv::Point current_location;

    gmMutex.lock();
    current_location = gmFSOCenter;
    gmMutex.unlock();

    error_vector = calculateErrorVector(Target, current_location);

    if(error_vector[2] < 8)
    {
        gmAutoLockingProcessing = false;
        std::cout << "locking is done" << std::endl;
        return;
    }

    while(1)
    {



        if(gmAutoLockingEnable == false)
        {
            std::cout << "Auto Locking is terminating..." << std::endl;

            break;
        }
        gmMutex.lock();
        current_location = gmFSOCenter;
        gmMutex.unlock();


        error_vector = calculateErrorVector(Target, current_location);

        applyPID(error_vector, stepmotor1_speed, stepmotor2_speed);

        ret = checkIfLedsInFrame();

        if(ret != SUCCESS)
            searchFSO(error_vector, stepmotor1_speed, stepmotor2_speed);


//        std::cout << "speed_x:" << std::to_string(stepmotor1_speed) <<
//                     " error_x:" << std::to_string(error_vector[1]) << std::endl;
//        std::cout << "speed_y:" << std::to_string(stepmotor2_speed) <<
//                     " error_y:" << std::to_string(error_vector[0]) << std::endl;

        ret = checkError(error_vector[2]);

        if(error_vector[2] > 3)
            driveMotors(stepmotor1_speed, stepmotor2_speed);
        else
            usleep(50000);



        if(ret == SUCCESS)
        {


            std::cout << "locking is complited!" << std::endl;


            *gpSfpLinkAvailable = true;

            break;
        }
        else
        {
            *gpSfpLinkAvailable = false;

        }

    }

    gmAutoLockingProcessing = false;

}

void AutoLockingPanel::stopLocking()
{
    gmAutoLockingEnable = false;
}

void AutoLockingPanel::startLocking()
{
    gmAutoLockingEnable = true;
}



void AutoLockingPanel::applyPID(const std::vector<double> &ErrorVector, double &Speed1, double &Speed2)
{
    static PIDController pid_controller_x(0.6, 0.0002, 9);
    static PIDController pid_controller_y(0.3, 0.0002, 15);


    Speed1 = pid_controller_y.applyPID(ErrorVector[1]);
    Speed2 = pid_controller_x.applyPID(ErrorVector[0]);


    if(ErrorVector[2] < 3)
    {
        pid_controller_x.clear();
        pid_controller_y.clear();
    }

}

void AutoLockingPanel::searchFSO(const std::vector<double> &ErrorVector, double &Speed1, double &Speed2)
{

    if(ErrorVector[2] > 10)
    {
        if(ErrorVector[0] > ErrorVector[1])
        {
            Speed2 = MAX_STEPMOTOR_SPEED;
            Speed1 = 0;
        }
        else if(ErrorVector[0] > ErrorVector[1])
        {
            Speed2 = 0;
            Speed1 = MAX_STEPMOTOR_SPEED - 20;
        }

    }
    else
    {
        Speed1 = 0;
        Speed2 = 0;
    }

    std::cout <<"search FSO : speed1:" << std::to_string(Speed1) <<
             " speed2:" << std::to_string(Speed2) << std::endl;
}





int AutoLockingPanel::checkIfLedsInFrame()
{


    if(gmFSOPoints.size() > 0)
        return SUCCESS;
    else
        return FAIL;

}

bool AutoLockingPanel::checkLedPositions()
{

    if(gmFSOPoints.size() < 4)
    {
        return false;
    }
    else
    {
        return true;
    }

}


int AutoLockingPanel::checkError(double Error)
{

    static int timeout_counter = 0;


    if(Error < 3)
    {
        timeout_counter++;
        std::cout << "timeout " << std::to_string(timeout_counter) << std::endl;

        if(timeout_counter >= ERROR_CORRECTION_TIMEOUT)
            return SUCCESS;

        return FAIL;
    }
    else
    {

        timeout_counter = 0;

        return FAIL;
    }

}

void AutoLockingPanel::driveMotors(int Step1Speed, int Step2Speed)
{

    Direction motor_direction;

    if(gmErrorVector.x > 0)
    {
        gpController->setStep2Speed(Step2Speed, MAX_STEPMOTOR_SPEED);
        motor_direction = Direction::Left;

    }
    else
    {
        gpController->setStep2Speed(Step2Speed, MAX_STEPMOTOR_SPEED);
        motor_direction = Direction::Right;
    }


    if(gmErrorVector.y > 0)
    {
        gpController->setStep1Speed(Step1Speed, MAX_STEPMOTOR_SPEED);

        if(motor_direction == Direction::Left)
            motor_direction = Direction::UpLeft;
        else
            motor_direction = Direction::UpRight;

    }
    else
    {
        gpController->setStep1Speed(Step1Speed, MAX_STEPMOTOR_SPEED);

        if(motor_direction == Direction::Left)
            motor_direction = Direction::DownLeft;
        else
            motor_direction = Direction::DownRight;
    }

    gpController->turntoDirection(motor_direction, MOTOR_DRIVE_DELAY);


}

//void AutoLockingPanel::drawDirectionLine(cv::Point Begin, cv::Point End)
//{
////    cv::line()
//}

//void AutoLockingPanel::drawDirectionLine(cv::Point Current)
//{

//}

std::vector<double> AutoLockingPanel::calculateErrorVector(cv::Point Target, cv::Point Current)
{

    std::vector<double> error_vector;


    if((Current.x > 0 || Current.x < FRAME_WIDTH) && (Current.y > 0 || Current.y < FRAME_HEIGHT))
    {

        error_vector.push_back(std::abs(Target.x - Current.x)); //x companent
        error_vector.push_back(std::abs(Target.y - Current.y)); //y companent
        error_vector.push_back(std::sqrt( std::pow(std::abs(Target.x - Current.x) ,2) +
                                          std::pow(std::abs(Target.y - Current.y), 2)
                                        )); // magnitude companent


        gmErrorVector = cv::Point(Target.x - Current.x, Target.y - Current.y);

    }


    return error_vector;

}


