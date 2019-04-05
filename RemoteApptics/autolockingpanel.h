#ifndef AUTOLOCKINGPANEL_H
#define AUTOLOCKINGPANEL_H

#include "autocontrolwindow.h"

#define ERROR_CORRECTION_TRESHOLD   50
#define MOTOR_DRIVE_DELAY           50
#define ERROR_CORRECTION_TIMEOUT    20

class AutoLockingPanel : public AutoControlWindow
{

    Q_OBJECT

public:
    AutoLockingPanel(AutoControlWindow *Window);

    void attachToAutoControlWindow();
    void executeCommands();
    void lockToTarget(const cv::Point &Target);

private:

    volatile bool gmAutoLockingTerminated = false;
    volatile bool gmAutoLockingProcessing = false;

    void applyPID(const std::vector<double> &ErrorVector, double &Speed1, double &Speed2);

    void searchFSO(const std::vector<double> &ErrorVector, double &Speed1, double &Speed2);
    int checkIfLedsInFrame();
    int checkError(double Error);
    void driveMotors(int Step1Speed, int Step2Speed);
    void drawDirectionLine(cv::Point Begin, cv::Point End);
    std::vector<double> calculateErrorVector(cv::Point Target, cv::Point Current);
    cv::Point gmErrorVector;

};

#endif // AUTOLOCKINGPANEL_H
