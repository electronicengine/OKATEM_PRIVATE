#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

//#include <QTimer>
#include <thread>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPixmap pix;

    ui->setupUi(this);

    gpConnectionBox = new ConnectionDialog;

    connect(gpConnectionBox, SIGNAL(accepted(std::string, int, int)), this, SLOT(connectionAccepted(std::string, int, int)));
    connect(gpConnectionBox, SIGNAL(rejected()), this, SLOT(connectionRejected()));
    connect(this, SIGNAL(progressUpdateFile(int)), ui->progressBar, SLOT(setValue(int)));
    connect(this, SIGNAL(setprogessbarvisibility(bool)), ui->progressBar, SLOT(setVisible(bool)));
    connect(this, SIGNAL(setupdatelabelvisibility(bool)), ui->update_label, SLOT(setVisible(bool)));

    connect(this, SIGNAL(refreshScreen(QPixmap)), ui->frame_label, SLOT(setPixmap(QPixmap)));
    connect(this, SIGNAL(screenClose()), ui->frame_label, SLOT(close()));
    connect(this, SIGNAL(screenShow()), ui->frame_label, SLOT(show()));

    connect(this, SIGNAL(refreshStatusLabel(QString)), ui->status_label, SLOT(setText(QString)));
    connect(this, SIGNAL(refreshTxPowerLabel(QString)), ui->tx_power_label, SLOT(setText(QString)));
    connect(this, SIGNAL(refreshRxPowerLabel(QString)), ui->rx_power_label, SLOT(setText(QString)));
    connect(this, SIGNAL(refreshTemperatureLabel(QString)), ui->temperature_label, SLOT(setText(QString)));
    connect(this, SIGNAL(refreshPressureLabel(QString)), ui->pressure_label, SLOT(setText(QString)));
    connect(this, SIGNAL(refreshAltitudeLabel(QString)), ui->altitude_label, SLOT(setText(QString)));
    connect(this, SIGNAL(refreshCompassLabel(QString)), ui->compass_label, SLOT(setText(QString)));
    connect(this, SIGNAL(refreshNMEALabel(QString)), ui->nmea_label, SLOT(setText(QString)));
    connect(this, SIGNAL(refreshStep1PosLabel(QString)), ui->step1_pos_label, SLOT(setText(QString)));
    connect(this, SIGNAL(refreshStep2PosLabel(QString)), ui->step2_pos_label, SLOT(setText(QString)));


    connect(this, SIGNAL(statusLabelClose()), ui->status_label, SLOT(close()));
    connect(this, SIGNAL(statusLabelShow()), ui->status_label, SLOT(show()));
    connect(this, SIGNAL(txPowerLabelClose()), ui->tx_power_label, SLOT(close()));
    connect(this, SIGNAL(txPowerLabelShow()), ui->tx_power_label, SLOT(show()));
    connect(this, SIGNAL(rxPowerLabelClose()), ui->rx_power_label, SLOT(close()));
    connect(this, SIGNAL(rxPowerLabelShow()), ui->rx_power_label, SLOT(show()));
    connect(this, SIGNAL(temperatureLabelClose()), ui->temperature_label, SLOT(close()));
    connect(this, SIGNAL(temperatureLabelShow()), ui->temperature_label, SLOT(show()));
    connect(this, SIGNAL(pressureLabelClose()), ui->pressure_label, SLOT(close()));
    connect(this, SIGNAL(pressureLabelShow()), ui->pressure_label, SLOT(show()));
    connect(this, SIGNAL(altitudeLabelClose()), ui->altitude_label, SLOT(close()));
    connect(this, SIGNAL(altitudeLabelClose()), ui->altitude_label, SLOT(show()));
    connect(this, SIGNAL(compassLabelClose()), ui->compass_label, SLOT(close()));
    connect(this, SIGNAL(compassLabelShow()), ui->compass_label, SLOT(show()));
    connect(this, SIGNAL(nmeaLabelClose()), ui->nmea_label, SLOT(close()));
    connect(this, SIGNAL(nmeaLabelShow()), ui->nmea_label, SLOT(show()));
    connect(this, SIGNAL(step1PosLabelClose()), ui->nmea_label, SLOT(close()));
    connect(this, SIGNAL(step1PosLabelShow()), ui->nmea_label, SLOT(show()));
    connect(this, SIGNAL(step2PosLabelClose()), ui->nmea_label, SLOT(close()));
    connect(this, SIGNAL(step2PosLabelShow()), ui->nmea_label, SLOT(show()));

    pix.load("hyperion.jpg");
    ui->frame_label->setPixmap(pix);

    emit setprogessbarvisibility(false);
    emit setupdatelabelvisibility(false);

    std::thread controlThread(&MainWindow::controlThread, this);
    controlThread.detach();

    std::thread keepAlive(&MainWindow::keepAlive, this);
    keepAlive.detach();

    setControlPanel(false);

}



MainWindow::~MainWindow()
{
    delete ui;
    delete gpController;
    delete gpConnectionBox;

    gpStream->stop();
    delete gpStream;
}



void MainWindow::on_actionConnection_triggered()
{
    gpConnectionBox->show();
}



void MainWindow::on_actionUpdate_Firmware_triggered()
{

//    QString stdw;
    std::string file;
//    QFileDialog dialog(this);

    QString file_name = QFileDialog::getOpenFileName(this, "select binary", "/root/qt-workspace/OKATEM_PRIVATE/stm32f746_rtos/build");

    file = file_name.toStdString();

    if(file.size() != 0)
    {
        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "Upgrading FirmWare", "Are You Sure?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            gpController->updateFirmware(file_name.toStdString());
        }
        else
        {
            std::cout << "Upgrading cancelled" << std::endl;
            return;
        }
    }
}



void MainWindow::deployPanel()
{

    static int counter = 0;

    counter ++;

    if(counter >= 10)
    {
        counter = 0;

        emit statusLabelClose();
        emit txPowerLabelClose();
        emit rxPowerLabelClose();
        emit temperatureLabelClose();
        emit pressureLabelClose();
        emit altitudeLabelClose();
        emit compassLabelClose();
        emit nmeaLabelClose();
        emit step1PosLabelClose();
        emit step2PosLabelClose();

        usleep(1000);

        emit statusLabelShow();
        emit txPowerLabelShow();
        emit rxPowerLabelShow();
        emit temperatureLabelShow();
        emit pressureLabelShow();
        emit altitudeLabelShow();
        emit compassLabelShow();
        emit nmeaLabelShow();
        emit step1PosLabelShow();
        emit step2PosLabelShow();

        usleep(1000);

    }

    emit refreshStatusLabel((gmSfpInfo.status == 1) ? "Connected":"Disconnected");
    emit refreshTxPowerLabel(QString::number(gmSfpInfo.tx_power));
    emit refreshRxPowerLabel(QString::number(gmSfpInfo.rx_power));
    emit refreshTemperatureLabel(QString::number(gmEnvironmentInfo.sensor_data.temperature));
    emit refreshPressureLabel(QString::number(gmEnvironmentInfo.sensor_data.pressure));
    emit refreshAltitudeLabel(QString::number(gmEnvironmentInfo.sensor_data.altitude));
    emit refreshCompassLabel(QString::number(gmEnvironmentInfo.sensor_data.compass_degree));
    emit refreshNMEALabel(QString(gmEnvironmentInfo.gps_string.c_str()));
    emit refreshStep1PosLabel(QString::number(gmEnvironmentInfo.step_motor1_step));
    emit refreshStep2PosLabel(QString::number(gmEnvironmentInfo.step_motor2_step));


}



void MainWindow::setControlPanel(bool Value)
{

    ui->increase1_button->setEnabled(Value);
    ui->increase2_button->setEnabled(Value);
    ui->decrease1_button->setEnabled(Value);
    ui->decrease2_button->setEnabled(Value);

    ui->right_button->setEnabled(Value);
    ui->left_button->setEnabled(Value);
    ui->up_button->setEnabled(Value);
    ui->down_buttton->setEnabled(Value);

    ui->speed_slider->setEnabled(Value);
    ui->servo1_slider->setEnabled(Value);
    ui->servo2_slider->setEnabled(Value);
    ui->refresh_button->setEnabled(Value);

}



void MainWindow::controlThread()
{

    int ret;
    int counter = 0;
    int percent = 0;
    bool update_done = 0;


    while(1)
    {

        counter++;

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

        if(gmControllerConnectionEstablished == 1)
        {

            percent = gpController->getUpdatePercenrage();

            if(percent >= 0 && percent < 100)
            {
//                printf("%d\n", percent);

                update_done = false;

                if(percent == 1)
                {
                     emit setprogessbarvisibility(true);
                     emit setupdatelabelvisibility(true);
                     setControlPanel(false);


                }

                emit progressUpdateFile(percent);

            }else if(percent >= 100 && update_done == false)
            {
                emit setprogessbarvisibility(false);
                emit setupdatelabelvisibility(false);

                emit progressUpdateFile(percent);

                update_done = true;

                setControlPanel(true);

                QMessageBox::information(this,"Upgrade Done","The FirmWare Upgrading has been finished Succesfully!");
            }
            else
            {
//                ui->progressBar->setVisible(false);
            }

        }

        usleep(50000);

        if(counter >= 20)
        {
            counter = 0;

            if(gmControllerConnectionEstablished == 1)
            {

                ret = gpController->getFsoInformations(gmControlInfo, gmEnvironmentInfo, gmSfpInfo);

                if(ret == SUCCESS)
                    deployPanel();

            }

        }

    }

}



void MainWindow::keepAlive()
{
    while(1)
    {
        sleep(2);
        QCoreApplication::processEvents();

    }
}



void MainWindow::connectionAccepted(std::string IpAddress, int StreamPort, int ControlPort)
{

    int ret;

    gpController = new Controller;
    gpStream = new VideoStream;

    gmIpAddress = IpAddress;
    gmStreamPort = StreamPort;
    gmControlPort = ControlPort;

    ret = gpController->start(gmIpAddress, gmControlPort);
    if(ret == FAIL)
    {
        QMessageBox::critical(this, "Error", "Controller Connection Failed");
        std::cout << "Controller Connection Failed: "<< gmIpAddress << std::endl;
    }
    else
    {
        ret = gpController->getFsoInformations(gmControlInfo, gmEnvironmentInfo, gmSfpInfo);
        if(ret == FAIL)
        {

            QMessageBox::critical(this, "Error", "Connection Failed");
            std::cout << "Connection Failed"<<std::endl;

            delete gpController;

        }
        else
        {
            QMessageBox::information(this, "Info", "Connection Established");
            std::cout << "Connection Established "<<std::endl;

            ret = gpStream->start(gmIpAddress, gmStreamPort, this);
            if(ret == FAIL)
            {
                QMessageBox::critical(this, "Error", "Streaming Connection Failed");
                std::cout << "Streaming Connection Failed "<<std::endl;
            }

            setTitle();

            setControlPanel(true);

            gmControllerConnectionEstablished = 1;

            ui->servo1_pos_label->setText(QString::number(gmControlInfo.servo_motor1_degree));
            ui->servo2_pos_label->setText(QString::number(gmControlInfo.servo_motor2_degree));
            ui->step1_pos_label->setText(QString::number(gmControlInfo.step_motor1_direction));
            ui->step2_pos_label->setText(QString::number(gmControlInfo.step_motor2_direction));

            ui->servo1_slider->setValue(gmControlInfo.servo_motor1_degree);
            gmServo1SliderValue = gmControlInfo.servo_motor1_degree;

            ui->servo2_slider->setValue(gmControlInfo.servo_motor2_degree);
            gmServo2SliderValue = gmControlInfo.servo_motor2_degree;

            deployPanel();

            gpConnectionBox->ui->buttonBox->hide();

        }
    }
}



void MainWindow::connectionRejected()
{
    std::cout << "rejected" << std::endl;
}



void MainWindow::on_speed_slider_valueChanged(int value)
{

    ui->speed_label->setText("Speed : " + QString::number(value));
    gpController->setSpeed(value);

}



void MainWindow::on_up_button_pressed(){ gmUpButtonPressed = 1; }



void MainWindow::on_up_button_released(){ gmUpButtonPressed = 0; }



void MainWindow::on_left_button_pressed(){ gmLeftButtonPressed = 1; }



void MainWindow::on_left_button_released(){ gmLeftButtonPressed = 0; }



void MainWindow::on_right_button_pressed(){ gmRightButtonPressed = 1; }



void MainWindow::on_right_button_released(){ gmRightButtonPressed = 0;}



void MainWindow::on_down_buttton_pressed(){ gmDownButtonPressed = 1;}



void MainWindow::on_down_buttton_released(){ gmDownButtonPressed = 0;}



void MainWindow::on_servo1_slider_valueChanged(int value)
{

    std::cout << value << std::endl;

    ui->servo1_slider->setValue(value);
    ui->servo1_pos_label->setText(QString::number(value));
    gpController->servo1SetValue(value);

}



void MainWindow::on_servo2_slider_valueChanged(int value)
{
    std::cout << value << std::endl;

    ui->servo2_slider->setValue(value);
    ui->servo2_pos_label->setText(QString::number(value));
    gpController->servo2SetValue(value);
}



void MainWindow::on_increase1_button_clicked()
{
    int value;

    value = ui->servo1_slider->value() + 1;

    ui->servo1_slider->setValue(value);

//    ui->servo1_slider->setValue(++gmServo1SliderValue);

}



void MainWindow::on_decrease1_button_clicked()
{

    int value;

    value = ui->servo1_slider->value() - 1;

    ui->servo1_slider->setValue(value);

//     ui->servo1_slider->setValue(--gmServo1SliderValue);

}



void MainWindow::on_increase2_button_clicked()
{

    int value;

    value = ui->servo2_slider->value() + 1;

    ui->servo2_slider->setValue(value);

//     ui->servo2_slider->setValue(++gmServo2SliderValue);

}



void MainWindow::on_decrease2_button_clicked()
{

    int value;

    value = ui->servo2_slider->value() - 1;

    ui->servo2_slider->setValue(value);

//    ui->servo2_slider->setValue(--gmServo2SliderValue);

}



std::string MainWindow::execCmd(const char* cmd)  // replace popen and pclose with _popen _pclose for windows
{
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
            {
                result += buffer;
            }
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);

    result = result.substr(0, result.size() - 1);

    return result;
}



void MainWindow::setTitle()
{
    char cmd[100];

    snprintf(cmd, 100, "sudo sshpass -p \"hyperion\" ssh pi@%s hostname", gmIpAddress.c_str());

    std::string hostName = execCmd(cmd);

    MainWindow::setWindowTitle(QString(hostName.c_str()) + QString(" - ") + QString(gmIpAddress.c_str()));

}



void MainWindow::on_refresh_button_clicked()
{

    if(gmControllerConnectionEstablished == 1)
    {

        delete gpStream;

        sleep(1);

        emit clearScreen();

        usleep(1000);

        gpStream = new VideoStream;

        gpStream->start(gmIpAddress, gmStreamPort, this);

    }

}


