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
#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include "autocontrol.h"
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


private slots:
    void connectionAccepted(std::string IpAddress, int StreamPort, int ControlPort);
    void connectionRejected();
    void on_actionConnection_triggered();
    void on_actionUpdate_Firmware_triggered();
    void on_actionAuto_Control_Settings_triggered();
    void on_actionSet_Initial_Values_triggered();

signals:


public:
    MainWindow(MainWindow *Window);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;



protected:


    CONTROL_DATA_FORMAT *gpControlInfo;
    SFP_DATA_FORMAT *gpSfpInfo;
    ENVIRONMENT_DATA_FORMAT *gpEnvironmentInfo;

    RemoteController *gpController;
    VideoStream *gpStream;

    UdpSocket *gpControllerSocket;
    UdpSocket *gpVideoStreamSocket;

    std::string gmIpAddress;
    int gmStreamPort;
    int gmControlPort;

private:

    AutoControl *gpAutoControl;

    ConnectionDialog *gpConnectionBox;

    ControlPanel *gpControlPanel;
    DisplayPanel *gpDisplaypanel;
    CameraPanel *gpCameraPanel;



    std::string execCmd(const char* cmd) ;
    void setTitle();



    cv::Mat gmMat;
    bool gmConnectionEstablished = 0;

    void worker();



};


#endif // MAINWINDOW_H
