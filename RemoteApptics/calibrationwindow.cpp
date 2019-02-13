#include "ui_calibrationwindow.h"
#include "calibrationwindow.h"
#include "calibrationpanel.h"

CalibrationWindow::CalibrationWindow(CalibrationWindow *Window) : MainWindow(true)
{
    ui = Window->ui;
    calibration_ui = Window->calibration_ui;

    gpControlPanel = Window->gpControlPanel;
    gpDisplaypanel = Window->gpDisplaypanel;
    gpCameraPanel = Window->gpCameraPanel;

    gpEnvironmentInfo = Window->gpEnvironmentInfo;
    gpControlInfo = Window->gpControlInfo;
    gpSfpInfo = Window->gpSfpInfo;

    gpIpAddress = Window->gpIpAddress;
    gpStreamPort = Window->gpStreamPort;
    gpControlPort = Window->gpControlPort;

    gpConnectionAvailable = Window->gpConnectionAvailable;

    gpCalibrationWindow = Window->gpCalibrationWindow;

}



CalibrationWindow::CalibrationWindow(MainWindow *Window):
    MainWindow(Window),
    calibration_ui(new Ui::CalibrationWindow)
{
    calibration_ui->setupUi(this);

    gpCalibrationWindow = this;

    gpCalibrationPanel = new CalibrationPanel(this);



}



CalibrationWindow::~CalibrationWindow()
{
    delete gpCalibrationPanel;
    delete calibration_ui;
}



void CalibrationWindow::deployTextBoxes()
{

    calibration_ui->step1_current_step->setText(QString::number(gpControlInfo->step_motor1_step));
    calibration_ui->step1_max_step->setText(QString::number(gpControlInfo->step_motor1_max_step));

    calibration_ui->step2_current_step->setText(QString::number(gpControlInfo->step_motor2_step));
    calibration_ui->step2_max_step->setText(QString::number(gpControlInfo->step_motor2_max_step));

    calibration_ui->servo1_current_degree->setText(QString::number(gpControlInfo->servo_motor1_degree));
    calibration_ui->servo2_current_degree->setText(QString::number(gpControlInfo->servo_motor2_degree));

    calibration_ui->servo1_bottom_degree->setText(QString::number(gpControlInfo->servo_motor1_bottom_degree));
    calibration_ui->servo1_top_degree->setText(QString::number(gpControlInfo->servo_motor1_top_degree));

    calibration_ui->servo2_bottom_degree->setText(QString::number(gpControlInfo->servo_motor2_bottom_degree));
    calibration_ui->servo2_top_degree->setText(QString::number(gpControlInfo->servo_motor2_top_degree));

}

