#include "controlpanel.h"



ControlPanel::ControlPanel(ControlWindow *Window) : ControlWindow(Window)
{

    attachToWindow();

}

void ControlPanel::deployPanel(bool Value)
{
    emit increase1ButtonSetEnable(Value);
    emit increase2ButtonSetEnable(Value);
    emit decrease1ButtonSetEnable(Value);
    emit decrease2ButtonSetEnable(Value);

    emit rigthButtonSetEnable(Value);
    emit leftButtonSetEnable(Value);
    emit upButtonSetEnable(Value);
    emit downButtonSetEnable(Value);

    emit step1SpeedSliderSetEnable(Value);
    emit step2SpeedSliderSetEnable(Value);

    emit servo1SliderSetEnable(Value);
    emit servo2SliderSetEnable(Value);
    emit refreshButtonSetEnable(Value);
}

void ControlPanel::setServoValues(int Servo1Value, int Servo2Value)
{
    emit setServo1SliderValue(Servo1Value);
    emit setServo1LabelText(QString::number(Servo1Value));

    emit setServo2SliderValue(Servo2Value);
    emit setServo2LabelText(QString::number(Servo2Value));
}

void ControlPanel::attachToWindow()
{

    connect(this, SIGNAL(increase1ButtonSetEnable(bool)), ui->increase1_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(increase2ButtonSetEnable(bool)), ui->increase2_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(decrease1ButtonSetEnable(bool)), ui->decrease1_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(decrease2ButtonSetEnable(bool)), ui->decrease2_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);

    connect(this, SIGNAL(rigthButtonSetEnable(bool)), ui->right_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(leftButtonSetEnable(bool)), ui->left_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(upButtonSetEnable(bool)), ui->up_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(downButtonSetEnable(bool)), ui->down_buttton, SLOT(setEnabled(bool)), Qt::QueuedConnection);

    connect(this, SIGNAL(step1SpeedSliderSetEnable(bool)), ui->step1_speed_slider, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(step2SpeedSliderSetEnable(bool)), ui->step2_speed_slider, SLOT(setEnabled(bool)), Qt::QueuedConnection);

    connect(this, SIGNAL(servo1SliderSetEnable(bool)), ui->servo1_slider, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(servo2SliderSetEnable(bool)), ui->servo2_slider, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(setServo1SliderValue(int)), ui->servo1_slider, SLOT(setValue(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(setServo2SliderValue(int)), ui->servo2_slider, SLOT(setValue(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(setServo1LabelText(QString)), ui->servo1_pos_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(setServo2LabelText(QString)), ui->servo2_pos_label, SLOT(setText(QString)), Qt::QueuedConnection);

}
