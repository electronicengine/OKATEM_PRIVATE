#include "ui_calibrationwindow.h"
#include "calibrationwindow.h"
#include "controlwindow.h"
#include "calibrationpanel.h"

#include "QMessageBox"

CalibrationWindow::CalibrationWindow(CalibrationWindow *Window) : MainWindow(true)
{
    ui = Window->ui;
    calibration_ui = Window->calibration_ui;

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

    gpCalibrationWindow = Window->gpCalibrationWindow;

}



CalibrationWindow::CalibrationWindow(MainWindow *Window):
    MainWindow(Window),
    calibration_ui(new Ui::CalibrationWindow)
{
    calibration_ui->setupUi(this);

    gpCalibrationWindow = this;


    connect(calibration_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(calibration_ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
    gpCalibrationPanel = new CalibrationPanel(this);

}



CalibrationWindow::~CalibrationWindow()
{
    delete calibration_ui;
}



void CalibrationWindow::setDefaultCalibrationValues()
{

    gpCalibrationPanel->deployPanel();
}



void CalibrationWindow::accepted()
{

    if(QMessageBox::question(gpCalibrationWindow, "Warning", "These values will be set. Are you sure?") == QMessageBox::Yes)
    {
        std::cout << "clicked yes" << std::endl;

        CONTROL_DATA_FORMAT calibration_data;

        calibration_data.setting_enable = 0xff;
        calibration_data.step_motor1_step = calibration_ui->step1_current_step->text().toInt();
        calibration_data.step_motor1_max_step = calibration_ui->step1_max_step->text().toInt();

        calibration_data.step_motor2_step = calibration_ui->step2_current_step->text().toInt();
        calibration_data.step_motor2_max_step = calibration_ui->step2_max_step->text().toInt();

        calibration_data.servo_motor1_degree = calibration_ui->servo1_current_degree->text().toInt();
        calibration_data.servo_motor2_degree = calibration_ui->servo2_current_degree->text().toInt();

        calibration_data.servo_motor1_bottom_degree = calibration_ui->servo1_bottom_degree->text().toInt();
        calibration_data.servo_motor1_top_degree = calibration_ui->servo1_top_degree->text().toInt();

        calibration_data.servo_motor2_bottom_degree = calibration_ui->servo2_bottom_degree->text().toInt();
        calibration_data.servo_motor2_top_degree = calibration_ui->servo2_top_degree->text().toInt();

        std::cout << "step_motor1_step: " << std::to_string(calibration_data.step_motor1_step) << std::endl;
        std::cout << "step_motor1_max_step: " << std::to_string(calibration_data.step_motor1_max_step) << std::endl;

        std::cout << "step_motor2_step: " << std::to_string(calibration_data.step_motor2_step) << std::endl;
        std::cout << "step_motor2_max_step: " << std::to_string(calibration_data.step_motor2_max_step) << std::endl;

        std::cout << "servo_motor1_degree: " << std::to_string(calibration_data.servo_motor1_degree) << std::endl;
        std::cout << "servo_motor2_degree: " << std::to_string(calibration_data.servo_motor2_degree) << std::endl;

        std::cout << "servo_motor1_bottom_degree: " << std::to_string(calibration_data.servo_motor1_bottom_degree) << std::endl;
        std::cout << "servo_motor1_top_degree: " << std::to_string(calibration_data.servo_motor1_top_degree) << std::endl;

        std::cout << "servo_motor2_bottom_degree: " << std::to_string(calibration_data.servo_motor2_bottom_degree) << std::endl;
        std::cout << "servo_motor2_top_degree: " << std::to_string(calibration_data.servo_motor2_top_degree) << std::endl;

        gpController->setCalibrationValues(calibration_data);

        gpCalibrationWindow->hide();
    }
    else
    {
        std::cout << "clicked no" << std::endl;
        gpCalibrationWindow->hide();


    }
}

void CalibrationWindow::rejected()
{
    gpCalibrationWindow->hide();
}

