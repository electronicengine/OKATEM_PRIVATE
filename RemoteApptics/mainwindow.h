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

#include "videostream.h"
#include "datatypes.h"
#include "controller.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void streamFrameCallBack(const cv::Mat &Frame);
    QImage cvMatToQImage( const cv::Mat &inMat );


private slots:
    void connectionAccepted(std::string IpAddress, int Port);

    void connectionRejected();

    void on_actionConnection_triggered();

    void on_actionUpdate_Firmware_triggered();

    void on_up_button_pressed();

    void on_up_button_released();

    void on_left_button_pressed();

    void on_left_button_released();

    void on_right_button_pressed();

    void on_right_button_released();

    void on_down_buttton_pressed();

    void on_down_buttton_released();

    void on_speed_slider_valueChanged(int value);

    void on_servo1_slider_valueChanged(int value);

    void on_servo2_slider_valueChanged(int value);

    void on_increase1_button_clicked();

    void on_decrease1_button_clicked();

    void on_increase2_button_clicked();

    void on_decrease2_button_clicked();

private:
    Ui::MainWindow *ui;


    Controller *gpController;
    VideoStream *gpStream;
    ConnectionDialog *gpConnectionBox;


    CONTROL_DATA_FORMAT gmControlInfo;
    SFP_DATA_FORMAT gmSfpInfo;
    ENVIRONMENT_DATA_FORMAT gmEnvironmentInfo;


    std::string execCmd(const char* cmd) ;
    void setTitle();

    cv::Mat gmMat;

    std::string gmIpAddress;
    int gmPort;

    int gmServo1SliderValue = 0;
    int gmServo2SliderValue = 0;

    bool gmUpButtonPressed = 0;
    bool gmDownButtonPressed = 0;
    bool gmLeftButtonPressed = 0;
    bool gmRightButtonPressed = 0;
    bool gmControllerConnectionEstablished = 0;

    void deployPanel();
    void buttonFlower();
};


#endif // MAINWINDOW_H
