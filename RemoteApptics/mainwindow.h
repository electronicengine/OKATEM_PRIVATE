#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "QFileDialog"
#include "QString"
#include "QPixmap"
#include <string>

#include <iostream>

#include "videostream.h"

#include "datatypes.h"
#include "remotecontroller.h"


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"

class ControlPanel;
class DisplayPanel;
class CameraPanel;
class ConnectionWindow;
class CalibrationWindow;
class AutoControlWindow;

namespace Ui {
class MainWindow;
}

enum MessageBoxType
{
    information,
    error
};


class MainWindow : public QMainWindow
{
    Q_OBJECT


private slots:

    void actionConnectionTriggered();
    void actionUpdateFirmwareTriggered();
    void on_actionSet_Initial_Values_triggered();
    void on_actionAuto_Control_Settings_triggered();

public:
    MainWindow(bool Constructed);
    MainWindow(MainWindow *Window);
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    Ui::MainWindow *ui;

    ControlPanel *gpControlPanel;
    DisplayPanel *gpDisplaypanel;
    CameraPanel *gpCameraPanel;

    CONTROL_DATA_FORMAT *gpControlInfo;
    SFP_DATA_FORMAT *gpSfpInfo;
    ENVIRONMENT_DATA_FORMAT *gpEnvironmentInfo;

    bool *gpConnectionAvailable;

    std::string *gpIpAddress;
    int *gpStreamPort;
    int *gpControlPort;

protected:

    ConnectionWindow *gpConnectionWindow;
    CalibrationWindow *gpCalibrationWindow;


    RemoteController *gpController;
    VideoStream *gpStream;


    UdpSocket *gpControllerSocket;
    UdpSocket *gpVideoStreamSocket;

    void setTitle(const std::string &IpAddress);

    MainWindow *gpMainWindow;



private:

    AutoControlWindow *gpAutoControlWindow;

    std::string execCmd(const char* cmd) ;

    cv::Mat gmMat;

    volatile bool gmTerminateWorker = false;
    volatile bool gmWorkerTerminated = false;

    void worker();
    void terminateWorker();



};


#endif // MAINWINDOW_H
