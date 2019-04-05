#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "ui_mainwindow.h"
#include "controlwindow.h"

class ControlPanel : public ControlWindow
{

    Q_OBJECT

public:
    ControlPanel(ControlWindow *Window);
    void deployPanel(bool Value);
    void setServoValues(int Servo1Value, int Servo2Value);

private:
    void attachToWindow();

signals:
    void setServo1SliderValue(int);
    void setServo2SliderValue(int);
    void setServo1LabelText(QString);
    void setServo2LabelText(QString);
    void servo1SliderSetEnable(bool);
    void servo2SliderSetEnable(bool);
    void increase1ButtonSetEnable(bool);
    void increase2ButtonSetEnable(bool);
    void decrease1ButtonSetEnable(bool);
    void decrease2ButtonSetEnable(bool);
    void rigthButtonSetEnable(bool);
    void leftButtonSetEnable(bool);
    void upButtonSetEnable(bool);
    void downButtonSetEnable(bool);
    void step1SpeedSliderSetEnable(bool);
    void step2SpeedSliderSetEnable(bool);

    void refreshButtonSetEnable(bool);

};

#endif // CONTROLPANEL_H
