#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include "controlpanel.h"
#include "displaypanel.h"
#include "camerapanel.h"

//#include <QTimer>
#include <thread>
#include <QMessageBox>



MainWindow::MainWindow(MainWindow *Window)
{

    ui = Window->ui;
    gpController = Window->gpController;

    gpControlInfo = Window->gpControlInfo;
    gpEnvironmentInfo = Window->gpEnvironmentInfo;
    gpSfpInfo = Window->gpSfpInfo;

}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPixmap pix;

    ui->setupUi(this);


    gpControlInfo = new CONTROL_DATA_FORMAT;
    gpEnvironmentInfo = new ENVIRONMENT_DATA_FORMAT;
    gpSfpInfo = new SFP_DATA_FORMAT;

    gpControllerSocket = new UdpSocket;
    gpVideoStreamSocket = new UdpSocket;

    gpConnectionBox = new ConnectionDialog;
    gpAutoControl = new AutoControl;
    gpController = new RemoteController(gpControllerSocket);


    gpControlPanel = new ControlPanel(this);
    gpDisplaypanel = new DisplayPanel(this);
    gpCameraPanel = new CameraPanel(this);

    connect(gpConnectionBox, SIGNAL(accepted(std::string, int, int)), this, SLOT(connectionAccepted(std::string, int, int)));
    connect(gpConnectionBox, SIGNAL(rejected()), this, SLOT(connectionRejected()));

    ui->toggle_button->setCheckable(true);
    pix.load("hyperion.jpg");
    ui->frame_label->setPixmap(pix);

    std::thread controlThread(&MainWindow::worker, this);
    controlThread.detach();



    gpControlPanel->setPanelEnable(false);

}



MainWindow::~MainWindow()
{
    delete ui;
    delete gpController;
    delete gpConnectionBox;

    gpStream->stop();
    delete gpStream;
}



void MainWindow::worker()
{


    while(1)
    {

        if(gmConnectionEstablished == true)
        {

            gpControlPanel->process();

            gpDisplaypanel->process();

        }



    }

}



void MainWindow::connectionAccepted(std::string IpAddress, int StreamPort, int ControlPort)
{

    int ret;

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
        std::cout << "Controller Connection Succesfull " << std::endl;

        ret = gpController->getFsoInformations(*gpControlInfo, *gpEnvironmentInfo, *gpSfpInfo);
        if(ret == FAIL)
        {

            QMessageBox::critical(this, "Error", "Connection Failed");
            std::cout << "FSO Information request has not been answered"<<std::endl;

            delete gpController;

        }
        else
        {
            QMessageBox::information(this, "Info", "Connection Established");
            std::cout << "Connection Established "<<std::endl;

            gpCameraPanel->startCamera();

            setTitle();

            gpControlPanel->setPanelEnable(true);


            gpControlPanel->setServoSliderInitialValues(gpControlInfo->servo_motor1_degree, gpControlInfo->servo_motor2_degree);
            std::cout << std::to_string(gpSfpInfo->status) << std::endl;
            std::cout << std::to_string(gpSfpInfo->tx_power) << std::endl;
            std::cout << std::to_string(gpSfpInfo->rx_power) << std::endl;

            std::cout << "step1: " << std::to_string(gpEnvironmentInfo->step_motor1_step) << std::endl;
            std::cout << "step2: " << std::to_string(gpEnvironmentInfo->step_motor2_step) << std::endl;

            std::cout << "servo1: " << std::to_string(gpEnvironmentInfo->servo_motor1_degree) << std::endl;
            std::cout << "servo2: " << std::to_string(gpEnvironmentInfo->servo_motor1_degree) << std::endl;

            gpDisplaypanel->deployPanel();

            gmConnectionEstablished = true;

            gpConnectionBox->ui->buttonBox->hide();

        }
    }
}



void MainWindow::connectionRejected()
{
    std::cout << "rejected" << std::endl;
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



void MainWindow::on_actionAuto_Control_Settings_triggered()
{
    gpAutoControl->show();
}



void MainWindow::on_actionSet_Initial_Values_triggered()
{
//    gpInitialValueSettings->setDefaultValues(gmControlInfo);
    //    gpInitialValueSettings->show();
}




