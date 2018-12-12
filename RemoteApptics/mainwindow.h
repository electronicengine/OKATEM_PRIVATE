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

    Ui::MainWindow *ui;

private slots:
    void connectionAccepted(std::string IpAddress, int StreamPort, int ControlPort);
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
    void on_refresh_button_clicked();

signals:
    void progressUpdateFile(int Percent);
    void refreshScreen(QPixmap Pix);
    void clearScreen();

    void statusLabelClose();
    void statusLabelShow();
    void refreshStatusLabel(const QString &Text);

    void txPowerLabelClose();
    void txPowerLabelShow();
    void refreshTxPowerLabel(const QString &Text);

    void rxPowerLabelClose();
    void rxPowerLabelShow();
    void refreshRxPowerLabel(const QString &Text);

    void temperatureLabelClose();
    void temperatureLabelShow();
    void refreshTemperatureLabel(const QString &Text);

    void pressureLabelClose();
    void pressureLabelShow();
    void refreshPressureLabel(const QString &Text);

    void altitudeLabelClose();
    void altitudeLabelShow();
    void refreshAltitudeLabel(const QString &Text);

    void compassLabelClose();
    void compassLabelShow();
    void refreshCompassLabel(const QString &Text);

    void nmeaLabelClose();
    void nmeaLabelShow();
    void refreshNMEALabel(const QString &Text);

    void screenClose();
    void screenShow();

private:


    Controller *gpController;
    VideoStream *gpStream;
    ConnectionDialog *gpConnectionBox;


    CONTROL_DATA_FORMAT gmControlInfo;
    SFP_DATA_FORMAT gmSfpInfo;
    ENVIRONMENT_DATA_FORMAT gmEnvironmentInfo;
    QTimer *timer;

    std::string execCmd(const char* cmd) ;
    void setTitle();

    cv::Mat gmMat;

    std::string gmIpAddress;
    int gmStreamPort;
    int gmControlPort;

    int gmServo1SliderValue = 0;
    int gmServo2SliderValue = 0;

    bool gmUpButtonPressed = 0;
    bool gmDownButtonPressed = 0;
    bool gmLeftButtonPressed = 0;
    bool gmRightButtonPressed = 0;
    bool gmControllerConnectionEstablished = 0;
    void controlThread();
    void keepAlive();
    void deployPanel();

    void setControlPanel(bool Value);

};


#endif // MAINWINDOW_H
