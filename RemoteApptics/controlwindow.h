#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

//#include "QObject"
#include "ui_mainwindow.h"
#include "mainwindow.h"


class ControlPanel;

class ControlWindow : public MainWindow
{

    Q_OBJECT


private slots:
    void on_toggle_button_toggled(bool checked);
    void on_up_button_toggled(bool checked);
    void on_left_button_toggled(bool checked);
    void on_down_buttton_toggled(bool checked);
    void on_right_button_toggled(bool checked);
    void on_up_button_pressed();
    void on_up_button_released();
    void on_left_button_pressed();
    void on_left_button_released();
    void on_right_button_pressed();
    void on_right_button_released();
    void on_down_buttton_pressed();
    void on_down_buttton_released();
    void on_step1_speed_slider_valueChanged(int value);
    void on_step2_speed_slider_valueChanged(int value);


    void on_servo1_slider_valueChanged(int value);
    void on_servo2_slider_valueChanged(int value);
    void on_increase1_button_clicked();
    void on_decrease1_button_clicked();
    void on_increase2_button_clicked();
    void on_decrease2_button_clicked();
    void on_refresh_button_clicked();


public:
    ControlWindow(ControlWindow *Window);
    ControlWindow(MainWindow *Window);
    virtual ~ControlWindow();

    void process();
    void setPanelEnable(bool Value);
    void setServoSliderInitialValues(int Servo1Value, int Servo2Value);


private:

    void attachToWindow();

    void checkButtons();

    volatile bool gmKeepButtonsPressed = false;

    volatile bool gmUpButtonCheckState = false;
    volatile bool gmDownButtonCheckState = false;
    volatile bool gmLeftButtonCheckState = false;
    volatile bool gmRightButtonCheckState = false;

    volatile bool gmUpButtonPressed = 0;
    volatile bool gmDownButtonPressed = 0;
    volatile bool gmLeftButtonPressed = 0;
    volatile bool gmRightButtonPressed = 0;

    ControlPanel *gpControlPanel;


};

#endif // PANEL_H
