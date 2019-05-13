#ifndef AUTOLOCKINGPANEL_H
#define AUTOLOCKINGPANEL_H

#include "autocontrolwindow.h"
#include "pidcontroller.h"

#define FSO_POINTS                  4
#define ERROR_CORRECTION_TRESHOLD   50
#define MOTOR_DRIVE_DELAY           50
#define ERROR_CORRECTION_TIMEOUT    20

class AutoLockingPanel : public AutoControlWindow
{

    Q_OBJECT

public:
    AutoLockingPanel(AutoControlWindow *Window);

    void markFSOPoints(cv::Mat &Frame, const std::vector<cv::Point> &Points);
    void drawErrorVector(cv::Mat &Frame, const std::vector<cv::Point> &Points);
    void attachToAutoControlWindow();
    void executeCommands();
    void lockToTarget(const cv::Point &Target);
    void stopLocking();
    void startLocking();

private:
    cv::Point gmTarget;
    std::mutex gmMutex;
    cv::Point gmFSOCenter;
    std::vector<cv::Point> gmFSOPoints;

    volatile bool gmAutoLockingEnable = false;
    volatile bool gmAutoLockingProcessing = false;

    void applyPID(const std::vector<double> &ErrorVector, double &Speed1, double &Speed2);

    void searchFSO(const std::vector<double> &ErrorVector, double &Speed1, double &Speed2);
    int checkIfLedsInFrame();
    bool checkLedPositions();
    int checkError(double Error);
    void driveMotors(int Step1Speed, int Step2Speed);
    void drawDirectionLine(cv::Point Begin, cv::Point End);
    std::vector<double> calculateErrorVector(cv::Point Target, cv::Point Current);
    cv::Point gmErrorVector;

};

#endif // AUTOLOCKINGPANEL_H
