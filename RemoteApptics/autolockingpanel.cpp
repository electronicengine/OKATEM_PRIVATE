#include "ui_autocontrolwindow.h"
#include "autolockingpanel.h"
#include "process.h"
#include "pidcontroller.h"

AutoLockingPanel::AutoLockingPanel(AutoControlWindow *Window) :
    AutoControlWindow(Window)
{
    attachToAutoControlWindow();
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

        std::thread locking_thread(&AutoLockingPanel::lockToTarget, this, cv::Point(
                                       autocontrol_ui->position_x->text().toInt(),
                                       autocontrol_ui->position_y->text().toInt()));
        locking_thread.detach();
    }


}



void AutoLockingPanel::lockToTarget(const cv::Point &Target)
{


    std::cout << "Locking is starting..." << std::endl;
    std::cout << "Target x:" << std::to_string(Target.x) <<
                 " Target y:" << std::to_string(Target.y) << std::endl;

    std::vector<double> error_vector;

    double stepmotor1_speed = 0;
    double stepmotor2_speed = 0;

    int ret;

    cv::Point current_location;

    while(1)
    {

        gpMutex->lock();
        current_location = *gpFSOCenter;
        gpMutex->unlock();


        error_vector = calculateErrorVector(Target, current_location);

        applyPID(error_vector, stepmotor1_speed, stepmotor2_speed);

        ret = checkIfLedsInFrame();

        if(ret != SUCCESS)
            searchFSO(error_vector, stepmotor1_speed, stepmotor2_speed);


//        std::cout << "speed_x:" << std::to_string(stepmotor1_speed) <<
//                     " error_x:" << std::to_string(error_vector[1]) << std::endl;
//        std::cout << "speed_y:" << std::to_string(stepmotor2_speed) <<
//                     " error_y:" << std::to_string(error_vector[0]) << std::endl;

        driveMotors(stepmotor1_speed, stepmotor2_speed);

        ret = checkError(error_vector[2]);

        error_vector.clear();

        if(ret == SUCCESS)
        {

            std::cout << "locking is complited!" << std::endl;
            if(*gpSfpConnectionAvailable == true)
            {
                *gpSfpLinkAvailable = true;

                break;
            }
            else
            {

                *gpSfpLinkAvailable = false;

                std::cout << "Sfp link is not available" << std::endl;

                break;
            }


        }

    }

    gmAutoLockingProcessing = false;

}



void AutoLockingPanel::applyPID(const std::vector<double> &ErrorVector, double &Speed1, double &Speed2)
{
    static PIDController pid_controller_x(0.6, 0.0002, 9);
    static PIDController pid_controller_y(0.3, 0.0002, 15);

    Speed1 = pid_controller_y.applyPID(ErrorVector[1]);
    Speed2 = pid_controller_x.applyPID(ErrorVector[0]);

}

void AutoLockingPanel::searchFSO(const std::vector<double> &ErrorVector, double &Speed1, double &Speed2)
{
    std::cout <<"search FSO" << ErrorVector[1] << Speed1 << Speed2 << std::endl;

}





int AutoLockingPanel::checkIfLedsInFrame()
{

    if(*gpFSOPoints > 0)
        return SUCCESS;
    else
        return FAIL;

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


    if((Current.x > 0 || Current.x < 960) && (Current.y > 0 || Current.y < 720))
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


