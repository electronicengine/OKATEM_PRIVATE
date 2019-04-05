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

class ControlWindow;
class DisplayPanel;
class CameraPanel;
class ConnectionWindow;
class CalibrationWindow;
class AutoControlWindow;
class CameraSettingsWindow;

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
    void on_actionCalibration_Settings_triggered();
    void on_actionAutoControl_Settings_triggered();
    void on_actionCamera_Settings_triggered();
    void scaleSliderChanged(int Value);

public slots:
    int showMessage(QWidget*, QString, QString, MessageBoxType);

public:
    MainWindow(bool Constructed);
    MainWindow(MainWindow *Window);
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    Ui::MainWindow *ui;

    ControlWindow *gpControlWindow;
    DisplayPanel *gpDisplaypanel;
    CameraPanel *gpCameraPanel;

    CONTROL_DATA_FORMAT *gpControlInfo;
    SFP_DATA_FORMAT *gpSfpInfo;
    ENVIRONMENT_DATA_FORMAT *gpEnvironmentInfo;

    bool *gpConnectionAvailable;
    bool *gpSfpConnectionAvailable;
    bool *gpSfpLinkAvailable;

    std::string *gpIpAddress;
    int *gpStreamPort;
    int *gpControlPort;

protected:

    ConnectionWindow *gpConnectionWindow;
    CalibrationWindow *gpCalibrationWindow;
    CameraSettingsWindow *gpCameraSettingsWindow;
    AutoControlWindow *gpAutoControlWindow;

    RemoteController *gpController;
    VideoStream *gpStream;

    UdpSocket *gpControllerSocket;
    UdpSocket *gpVideoStreamSocket;

    void setTitle(const std::string &IpAddress);

    MainWindow *gpMainWindow;



private:

    std::string execCmd(const char* cmd) ;

    cv::Mat gmMat;

    volatile bool gmTerminateWorker = false;
    volatile bool gmWorkerTerminated = false;

    void worker();
    void terminateWorker();


};


#endif // MAINWINDOW_H
