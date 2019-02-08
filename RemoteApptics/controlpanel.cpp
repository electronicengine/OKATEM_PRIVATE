
#include "controlpanel.h"
#include "QMessageBox"




ControlPanel::ControlPanel(MainWindow *Window) : MainWindow(Window)
{
    gpConnectionAvailable = &Window->gmConnectionAvailable;

    attachToWindow();
}

void ControlPanel::process()
{

    checkButtons();

    usleep(25000);


}



void ControlPanel::attachToWindow()
{

    connect(ui->up_button, SIGNAL(toggled(bool)), this, SLOT(on_up_button_toggled(bool)));
    connect(ui->up_button, SIGNAL(pressed()), this, SLOT(on_up_button_pressed()));
    connect(ui->up_button, SIGNAL(released()), this, SLOT(on_up_button_released()));

    connect(ui->down_buttton, SIGNAL(toggled(bool)), this, SLOT(on_down_buttton_toggled(bool)));
    connect(ui->down_buttton, SIGNAL(pressed()), this, SLOT(on_down_buttton_pressed()));
    connect(ui->down_buttton, SIGNAL(released()), this, SLOT(on_down_buttton_released()));

    connect(ui->right_button, SIGNAL(toggled(bool)), this, SLOT(on_right_button_toggled(bool)));
    connect(ui->right_button, SIGNAL(pressed()), this, SLOT(on_right_button_pressed()));
    connect(ui->right_button, SIGNAL(released()), this, SLOT(on_right_button_released()));

    connect(ui->left_button, SIGNAL(toggled(bool)), this, SLOT(on_left_button_toggled(bool)));
    connect(ui->left_button, SIGNAL(pressed()), this, SLOT(on_left_button_pressed()));
    connect(ui->left_button, SIGNAL(released()), this, SLOT(on_left_button_released()));

    connect(ui->speed_slider, SIGNAL(valueChanged(int)), SLOT(on_speed_slider_valueChanged(int)));
    connect(ui->servo1_slider, SIGNAL(valueChanged(int)), SLOT(on_servo1_slider_valueChanged(int)));
    connect(ui->servo2_slider, SIGNAL(valueChanged(int)), SLOT(on_servo2_slider_valueChanged(int)));

    connect(ui->increase1_button, SIGNAL(clicked(bool)), SLOT(on_increase1_button_clicked()));
    connect(ui->increase2_button, SIGNAL(clicked(bool)), SLOT(on_increase2_button_clicked()));
    connect(ui->decrease1_button, SIGNAL(clicked(bool)), SLOT(on_decrease1_button_clicked()));
    connect(ui->decrease2_button, SIGNAL(clicked(bool)), SLOT(on_decrease2_button_clicked()));

    connect(ui->toggle_button, SIGNAL(toggled(bool)), SLOT(on_toggle_button_toggled(bool)));
    connect(ui->refresh_button, SIGNAL(clicked(bool)), SLOT(on_refresh_button_clicked()));

    connect(this, SIGNAL(increase1ButtonSetEnable(bool)), ui->increase1_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(increase2ButtonSetEnable(bool)), ui->increase2_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(decrease1ButtonSetEnable(bool)), ui->decrease1_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(decrease2ButtonSetEnable(bool)), ui->decrease2_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);

    connect(this, SIGNAL(rigthButtonSetEnable(bool)), ui->right_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(leftButtonSetEnable(bool)), ui->left_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(upButtonSetEnable(bool)), ui->up_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(downButtonSetEnable(bool)), ui->down_buttton, SLOT(setEnabled(bool)), Qt::QueuedConnection);

    connect(this, SIGNAL(speedSliderSetEnable(bool)), ui->speed_slider, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(servo1SliderSetEnable(bool)), ui->servo1_slider, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(servo2SliderSetEnable(bool)), ui->servo2_slider, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshButtonSetEnable(bool)), ui->refresh_button, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(setServo1SliderValue(int)), ui->servo1_slider, SLOT(setValue(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(setServo2SliderValue(int)), ui->servo2_slider, SLOT(setValue(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(setServo1LabelText(QString)), ui->servo1_pos_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(setServo2LabelText(QString)), ui->servo2_pos_label, SLOT(setText(QString)), Qt::QueuedConnection);


    setPanelEnable(false);

}



void ControlPanel::checkButtons()
{

    if(gmUpButtonPressed)
    {
        gpController->turnUp();

    }else if(gmDownButtonPressed)
    {
        gpController->turnDown();

    }else if(gmLeftButtonPressed)
    {
        gpController->turnLeft();

    }else if(gmRightButtonPressed)
    {
        gpController->turnRight();
    }

}

void ControlPanel::setPanelEnable(bool Value)
{
    emit increase1ButtonSetEnable(Value);
    emit increase2ButtonSetEnable(Value);
    emit decrease1ButtonSetEnable(Value);
    emit decrease2ButtonSetEnable(Value);

    emit rigthButtonSetEnable(Value);
    emit leftButtonSetEnable(Value);
    emit upButtonSetEnable(Value);
    emit downButtonSetEnable(Value);

    emit speedSliderSetEnable(Value);
    emit servo1SliderSetEnable(Value);
    emit servo2SliderSetEnable(Value);
    emit refreshButtonSetEnable(Value);
}

void ControlPanel::setServoSliderInitialValues(int Servo1Value, int Servo2Value)
{

    emit setServo1SliderValue(Servo1Value);
    emit setServo1LabelText(QString::number(Servo1Value));

    emit setServo2SliderValue(Servo2Value);
    emit setServo2LabelText(QString::number(Servo2Value));

}

void ControlPanel::setCalibrationData(CONTROL_DATA_FORMAT &ControlData)
{
    gpController->setCalibrationValues(ControlData);
}



void ControlPanel::on_servo1_slider_valueChanged(int value)
{


    if(gpControlInfo->servo_motor1_bottom_degree < value && gpControlInfo->servo_motor1_top_degree > value)
    {
        emit setServo1SliderValue(value);
        emit setServo1LabelText(QString::number(value));

        gpController->servo1SetValue(value);

    }
    else
    {
        if(gpControlInfo->servo_motor1_bottom_degree >= value)
            value = gpControlInfo->servo_motor1_bottom_degree;
        if(gpControlInfo->servo_motor1_top_degree <= value)
            value = gpControlInfo->servo_motor1_top_degree;

        emit setServo1SliderValue(value);
        emit setServo1LabelText(QString::number(value));

    }

}



void ControlPanel::on_servo2_slider_valueChanged(int value)
{

    if(gpControlInfo->servo_motor2_bottom_degree < value && gpControlInfo->servo_motor2_top_degree > value)
    {
        emit setServo2SliderValue(value);
        emit setServo2LabelText(QString::number(value));

        gpController->servo2SetValue(value);

    }
    else
    {
        if(gpControlInfo->servo_motor2_bottom_degree >= value)
            value = gpControlInfo->servo_motor2_bottom_degree;
        if(gpControlInfo->servo_motor2_top_degree <= value)
            value = gpControlInfo->servo_motor2_top_degree;

        emit setServo2SliderValue(value);
        emit setServo2LabelText(QString::number(value));

    }
}



void ControlPanel::on_speed_slider_valueChanged(int value)
{
//    ui->speed_label->setText("Speed : " + QString::number(value));
    gpController->setSpeed(value);
}



void ControlPanel::on_up_button_pressed()
{
    gmUpButtonPressed = 1;
}



void ControlPanel::on_up_button_released()
{
    if(gmKeepButtonsPressed == false)
        gmUpButtonPressed = 0;
    else
    {
        if(gmUpButtonCheckState == false)
            gmUpButtonPressed = 0;
    }

}


void ControlPanel::on_left_button_pressed() { gmLeftButtonPressed = 1; }



void ControlPanel::on_left_button_released()
{
    if(gmKeepButtonsPressed == false)
        gmLeftButtonPressed = 0;
    else
    {
        if(gmLeftButtonCheckState == false)
            gmLeftButtonPressed = 0;
    }
}



void ControlPanel::on_right_button_pressed() { gmRightButtonPressed = 1; }



void ControlPanel::on_right_button_released()
{
    if(gmKeepButtonsPressed == false)
        gmRightButtonPressed = 0;
    else
    {
        if(gmRightButtonCheckState == false)
            gmRightButtonPressed = 0;
    }
}



void ControlPanel::on_down_buttton_pressed() { gmDownButtonPressed = 1; }



void ControlPanel::on_down_buttton_released()
{
    if(gmKeepButtonsPressed == false)
        gmDownButtonPressed = 0;
    else
    {
        if(gmDownButtonCheckState == false)
            gmDownButtonPressed = 0;
    }
}







void ControlPanel::on_increase1_button_clicked()
{
    int value;

    value = ui->servo1_slider->value() + 1;

    emit setServo1SliderValue(value);

}



void ControlPanel::on_decrease1_button_clicked()
{

    int value;

    value = ui->servo1_slider->value() - 1;

    emit setServo1SliderValue(value);

}



void ControlPanel::on_increase2_button_clicked()
{

    int value;

    value = ui->servo2_slider->value() + 1;

    emit setServo2SliderValue(value);

}



void ControlPanel::on_decrease2_button_clicked()
{

    int value;

    value = ui->servo2_slider->value() - 1;

    emit setServo2SliderValue(value);


}



void ControlPanel::on_up_button_toggled(bool checked)
{
    gmUpButtonCheckState = checked;
}



void ControlPanel::on_left_button_toggled(bool checked)
{
    gmLeftButtonCheckState = checked;
}



void ControlPanel::on_down_buttton_toggled(bool checked)
{
    gmDownButtonCheckState = checked;
}



void ControlPanel::on_right_button_toggled(bool checked)
{
    gmRightButtonCheckState = checked;
}



void ControlPanel::on_toggle_button_toggled(bool checked)
{

    gmKeepButtonsPressed = checked;

    std::cout << "buttons setting checkable" << std::endl;

    ui->up_button->setCheckable(checked);
    ui->down_buttton->setCheckable(checked);
    ui->right_button->setCheckable(checked);
    ui->left_button->setCheckable(checked);


}



void ControlPanel::on_refresh_button_clicked()
{

//    if(*gpControllerConnectionEstablished == 1)
//    {

//        delete gpStream;

//        sleep(1);

//        emit clearScreen();

//        usleep(1000);

//        gpStream = new VideoStream(&gmVideoStreamSocket);

//        gpStream->start(gmIpAddress, gmStreamPort, this);

//    }

}
