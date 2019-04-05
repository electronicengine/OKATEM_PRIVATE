#include "ui_calibrationwindow.h"
#include "calibrationpanel.h"
#include "controlwindow.h"

#include "QMessageBox"

CalibrationPanel::CalibrationPanel(CalibrationWindow *Window) : CalibrationWindow(Window)
{
    attachCalibrationWindow();

    gpCalibrationWindow = Window;
}

CalibrationPanel::~CalibrationPanel()
{

}

void CalibrationPanel::deployPanel()
{
    emit setStep1Current(QString::number(gpControlInfo->step_motor1_step));
    emit setStep1Max(QString::number(gpControlInfo->step_motor1_max_step));

    emit setStep2Current(QString::number(gpControlInfo->step_motor2_step));
    emit setStep2Max(QString::number(gpControlInfo->step_motor2_max_step));

    emit setServo1Current(QString::number(gpControlInfo->servo_motor1_degree));
    emit setServo2Current(QString::number(gpControlInfo->servo_motor2_degree));

    emit setServo1Bottom(QString::number(gpControlInfo->servo_motor1_bottom_degree));
    emit setServo1Top(QString::number(gpControlInfo->servo_motor1_top_degree));

    emit setServo2Bottom(QString::number(gpControlInfo->servo_motor2_bottom_degree));
    emit setServo2Top(QString::number(gpControlInfo->servo_motor2_top_degree));

}

void CalibrationPanel::attachCalibrationWindow()
{
    connect(this, SIGNAL(setStep1Current(QString)), calibration_ui->step1_current_step, SLOT(setText(QString)));
    connect(this, SIGNAL(setStep2Current(QString)), calibration_ui->step2_current_step, SLOT(setText(QString)));

    connect(this, SIGNAL(setStep1Max(QString)), calibration_ui->step1_max_step, SLOT(setText(QString)));
    connect(this, SIGNAL(setStep2Max(QString)), calibration_ui->step2_max_step, SLOT(setText(QString)));

    connect(this, SIGNAL(setServo1Current(QString)), calibration_ui->servo1_current_degree, SLOT(setText(QString)));
    connect(this, SIGNAL(setServo2Current(QString)), calibration_ui->servo2_current_degree, SLOT(setText(QString)));

    connect(this, SIGNAL(setServo1Top(QString)), calibration_ui->servo1_top_degree, SLOT(setText(QString)));
    connect(this, SIGNAL(setServo1Top(QString)), calibration_ui->servo2_top_degree, SLOT(setText(QString)));

    connect(this, SIGNAL(setServo1Bottom(QString)), calibration_ui->servo1_bottom_degree, SLOT(setText(QString)));
    connect(this, SIGNAL(setServo1Bottom(QString)), calibration_ui->servo2_bottom_degree, SLOT(setText(QString)));

}



