#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

//#include "QObject"
#include "mainwindow.h"
#include "ui_mainwindow.h"

//class MainWindow;


class ControlPanel : public MainWindow
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
    void on_speed_slider_valueChanged(int value);
    void on_servo1_slider_valueChanged(int value);
    void on_servo2_slider_valueChanged(int value);
    void on_increase1_button_clicked();
    void on_decrease1_button_clicked();
    void on_increase2_button_clicked();
    void on_decrease2_button_clicked();
    void on_refresh_button_clicked();

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
    void speedSliderSetEnable(bool);

    void refreshButtonSetEnable(bool);


public:
    ControlPanel(MainWindow *Window);

    virtual ~ControlPanel(){}

    void process();
    void setPanelEnable(bool Value);
    void setServoSliderInitialValues(int Servo1Value, int Servo2Value);

protected:
    bool *gpConnectionAvailable;

private:

    void attachToWindow();

    void checkButtons();
    void checkUpdateBar();
    void deployPanel();
    void preparePanelInfo();

    volatile bool gmKeepButtonsPressed = false;

    volatile bool gmUpButtonCheckState = false;
    volatile bool gmDownButtonCheckState = false;
    volatile bool gmLeftButtonCheckState = false;
    volatile bool gmRightButtonCheckState = false;

    volatile bool gmUpButtonPressed = 0;
    volatile bool gmDownButtonPressed = 0;
    volatile bool gmLeftButtonPressed = 0;
    volatile bool gmRightButtonPressed = 0;




};

#endif // PANEL_H
