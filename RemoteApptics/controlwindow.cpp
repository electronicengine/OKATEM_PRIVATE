
#include "controlwindow.h"
#include "QMessageBox"
#include "displaypanel.h"
#include "controlpanel.h"
#include "mainwindow.h"


ControlWindow::ControlWindow(ControlWindow *Window) : MainWindow(true)
{


    ui = Window->ui;

    gpControlWindow = Window->gpControlWindow;
    gpDisplaypanel = Window->gpDisplaypanel;
    gpCameraPanel = Window->gpCameraPanel;

    gpEnvironmentInfo = Window->gpEnvironmentInfo;
    gpControlInfo = Window->gpControlInfo;
    gpSfpInfo = Window->gpSfpInfo;

    gpIpAddress = Window->gpIpAddress;
    gpStreamPort = Window->gpStreamPort;
    gpControlPort = Window->gpControlPort;

    gpConnectionAvailable = Window->gpConnectionAvailable;
    gpMainWindow = Window->gpMainWindow;

}


ControlWindow::ControlWindow(MainWindow *Window) : MainWindow(Window)
{

    attachToWindow();
}

ControlWindow::~ControlWindow()
{

}

void ControlWindow::process()
{

    checkButtons();

    usleep(25000);


}



void ControlWindow::attachToWindow()
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

    connect(ui->step1_speed_slider, SIGNAL(valueChanged(int)), SLOT(on_step1_speed_slider_valueChanged(int)));
    connect(ui->step2_speed_slider, SIGNAL(valueChanged(int)), SLOT(on_step2_speed_slider_valueChanged(int)));


    connect(ui->servo1_slider, SIGNAL(valueChanged(int)), SLOT(on_servo1_slider_valueChanged(int)));
    connect(ui->servo2_slider, SIGNAL(valueChanged(int)), SLOT(on_servo2_slider_valueChanged(int)));

    connect(ui->increase1_button, SIGNAL(clicked(bool)), SLOT(on_increase1_button_clicked()));
    connect(ui->increase2_button, SIGNAL(clicked(bool)), SLOT(on_increase2_button_clicked()));
    connect(ui->decrease1_button, SIGNAL(clicked(bool)), SLOT(on_decrease1_button_clicked()));
    connect(ui->decrease2_button, SIGNAL(clicked(bool)), SLOT(on_decrease2_button_clicked()));

    connect(ui->toggle_button, SIGNAL(toggled(bool)), SLOT(on_toggle_button_toggled(bool)));


    gpControlPanel = new ControlPanel(this);

    gpControlPanel->deployPanel(false);

}



void ControlWindow::checkButtons()
{

    gpController->stop();


    if(gmUpButtonPressed)
    {
        gpController->turnUp();
    }

    if(gmDownButtonPressed)
    {
        gpController->turnDown();
    }

    if(gmLeftButtonPressed)
    {
        gpController->turnLeft();

    }

    if(gmRightButtonPressed)
    {
        gpController->turnRight();
    }

}

void ControlWindow::setPanelEnable(bool Value)
{

    gpControlPanel->deployPanel(Value);

}

void ControlWindow::setServoSliderInitialValues(int Servo1Value, int Servo2Value)
{


    gpControlPanel->setServoValues(Servo1Value, Servo2Value);

}




void ControlWindow::on_servo1_slider_valueChanged(int value)
{


    if(gpControlInfo->servo_motor1_bottom_degree < value && gpControlInfo->servo_motor1_top_degree > value)
    {
        ui->servo1_slider->setValue(value);
        ui->servo1_pos_label->setText(QString::number(value));

        gpController->servo1SetValue(value);

    }
    else
    {
        if(gpControlInfo->servo_motor1_bottom_degree >= value)
            value = gpControlInfo->servo_motor1_bottom_degree;
        if(gpControlInfo->servo_motor1_top_degree <= value)
            value = gpControlInfo->servo_motor1_top_degree;

        ui->servo1_slider->setValue(value);
        ui->servo1_pos_label->setText(QString::number(value));

    }

}



void ControlWindow::on_servo2_slider_valueChanged(int value)
{

    if(gpControlInfo->servo_motor2_bottom_degree < value && gpControlInfo->servo_motor2_top_degree > value)
    {
        ui->servo2_slider->setValue(value);
        ui->servo2_pos_label->setText(QString::number(value));

        gpController->servo2SetValue(value);

    }
    else
    {
        if(gpControlInfo->servo_motor2_bottom_degree >= value)
            value = gpControlInfo->servo_motor2_bottom_degree;
        if(gpControlInfo->servo_motor2_top_degree <= value)
            value = gpControlInfo->servo_motor2_top_degree;

        ui->servo2_slider->setValue(value);
        ui->servo2_pos_label->setText(QString::number(value));


    }
}



void ControlWindow::on_step1_speed_slider_valueChanged(int value)
{
    ui->step1_speed_label->setText("Up-Down Speed: " + QString::number(value));
    gpController->setStep1Speed(value, MAX_STEPMOTOR_SPEED);
}

void ControlWindow::on_step2_speed_slider_valueChanged(int value)
{
    ui->step2_speed_label->setText("Left-Right Speed: " + QString::number(value));
    gpController->setStep2Speed(value, MAX_STEPMOTOR_SPEED);
}



void ControlWindow::on_up_button_pressed()
{
    gmUpButtonPressed = 1;
}



void ControlWindow::on_up_button_released()
{
    if(gmKeepButtonsPressed == false)
        gmUpButtonPressed = 0;
    else
    {
        if(gmUpButtonCheckState == false)
            gmUpButtonPressed = 0;
    }

}


void ControlWindow::on_left_button_pressed() { gmLeftButtonPressed = 1; }



void ControlWindow::on_left_button_released()
{
    if(gmKeepButtonsPressed == false)
        gmLeftButtonPressed = 0;
    else
    {
        if(gmLeftButtonCheckState == false)
            gmLeftButtonPressed = 0;
    }
}



void ControlWindow::on_right_button_pressed() { gmRightButtonPressed = 1; }



void ControlWindow::on_right_button_released()
{
    if(gmKeepButtonsPressed == false)
        gmRightButtonPressed = 0;
    else
    {
        if(gmRightButtonCheckState == false)
            gmRightButtonPressed = 0;
    }
}



void ControlWindow::on_down_buttton_pressed() { gmDownButtonPressed = 1; }



void ControlWindow::on_down_buttton_released()
{
    if(gmKeepButtonsPressed == false)
        gmDownButtonPressed = 0;
    else
    {
        if(gmDownButtonCheckState == false)
            gmDownButtonPressed = 0;
    }
}







void ControlWindow::on_increase1_button_clicked()
{
    int value;

    value = ui->servo1_slider->value() + 1;

    ui->servo1_slider->setValue(value);

}



void ControlWindow::on_decrease1_button_clicked()
{

    int value;

    value = ui->servo1_slider->value() - 1;

    ui->servo1_slider->setValue(value);

}



void ControlWindow::on_increase2_button_clicked()
{

    int value;

    value = ui->servo2_slider->value() + 1;

    ui->servo2_slider->setValue(value);


}



void ControlWindow::on_decrease2_button_clicked()
{

    int value;

    value = ui->servo2_slider->value() - 1;

    ui->servo2_slider->setValue(value);


}



void ControlWindow::on_up_button_toggled(bool checked)
{
    gmUpButtonCheckState = checked;
}



void ControlWindow::on_left_button_toggled(bool checked)
{
    gmLeftButtonCheckState = checked;
}



void ControlWindow::on_down_buttton_toggled(bool checked)
{
    gmDownButtonCheckState = checked;
}



void ControlWindow::on_right_button_toggled(bool checked)
{
    gmRightButtonCheckState = checked;
}



void ControlWindow::on_toggle_button_toggled(bool checked)
{

    gmKeepButtonsPressed = checked;

    std::cout << "buttons setting checkable" << std::endl;

    ui->up_button->setCheckable(checked);
    ui->down_buttton->setCheckable(checked);
    ui->right_button->setCheckable(checked);
    ui->left_button->setCheckable(checked);


}



void ControlWindow::on_refresh_button_clicked()
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

