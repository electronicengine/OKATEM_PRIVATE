//#include "connectiondialog.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include "controlwindow.h"
#include "displaypanel.h"
#include "camerapanel.h"
#include "connectionwindow.h"
#include "calibrationwindow.h"
#include "autocontrolwindow.h"
#include "camerasettingswindow.h"

#include <thread>
#include <QMessageBox>



MainWindow::MainWindow(bool Constructed)
{
    std::cout << "MainWindow Constructed" << Constructed << std::endl;
}



MainWindow::MainWindow(MainWindow *Window)
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
    gpSfpConnectionAvailable = Window ->gpSfpConnectionAvailable;
    gpSfpLinkAvailable = Window->gpSfpLinkAvailable;

    gpController = Window->gpController;
    gpStream = Window->gpStream;

    gpVideoStreamSocket = Window->gpVideoStreamSocket;
    gpControllerSocket = Window->gpControllerSocket;

    gpMainWindow = Window->gpMainWindow;
    gpCameraSettingsWindow = Window->gpCameraSettingsWindow;
    gpAutoControlWindow = Window->gpAutoControlWindow;

}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QPixmap pix;

    ui->setupUi(this);

    gpSfpLinkAvailable = new bool;
    gpSfpConnectionAvailable = new bool;
    gpConnectionAvailable = new bool;

    *gpSfpConnectionAvailable = false;
    *gpSfpLinkAvailable = false;
    *gpConnectionAvailable = false;

    gpIpAddress = new std::string;
    gpStreamPort = new int;
    gpControlPort = new int;

    *gpConnectionAvailable = false;

    connect(ui->actionConnection, SIGNAL(triggered(bool)), this, SLOT(actionConnectionTriggered()));
    connect(ui->actionCalibration_Settings, SIGNAL(triggered(bool)), this, SLOT(on_actionCalibration_Settings_triggered()));
    connect(ui->actionAutoControl_Settings, SIGNAL(triggered(bool)), this, SLOT(on_actionAutoControl_Settings_triggered()));
    connect(ui->actionUpdate_Firmware, SIGNAL(triggered(bool)), this, SLOT(actionUpdateFirmwareTriggered()));
    connect(ui->referance_scale_slider, SIGNAL(valueChanged(int)), this, SLOT(scaleSliderChanged(int)));

    gpMainWindow = this;

    gpControlInfo = new CONTROL_DATA_FORMAT;
    gpEnvironmentInfo = new ENVIRONMENT_DATA_FORMAT;
    gpSfpInfo = new SFP_DATA_FORMAT;

    gpControllerSocket = new UdpSocket;
    gpVideoStreamSocket = new UdpSocket;


    gpController = new RemoteController(gpControllerSocket);
    gpStream = new VideoStream(gpVideoStreamSocket);

    gpAutoControlWindow = new AutoControlWindow(this);

    gpControlWindow = new ControlWindow(this);
    gpDisplaypanel = new DisplayPanel(this);
    gpCameraPanel = new CameraPanel(this);

    ui->toggle_button->setCheckable(true);
    pix.load("hyperion.jpg");
    ui->frame_label->setPixmap(pix);

    gpConnectionWindow = new ConnectionWindow(this);
    gpCalibrationWindow = new CalibrationWindow(this);
    gpCameraSettingsWindow = new CameraSettingsWindow(this);

    std::thread controlThread(&MainWindow::worker, this);
    controlThread.detach();


    gpControlWindow->setPanelEnable(false);

}



MainWindow::~MainWindow()
{

    terminateWorker();

    delete ui;

    delete gpControlInfo;
    delete gpSfpInfo;
    delete gpEnvironmentInfo;

    delete gpConnectionAvailable;
    delete gpIpAddress;
    delete gpControlPort;
    delete gpStreamPort;

}


void MainWindow::scaleSliderChanged(int Value)
{

    gpCameraPanel->scaleTarget(Value);

}


int MainWindow::showMessage(QWidget *Parent, QString Title, QString Message, MessageBoxType Type)
{

    std::cout << "MessageBox showing Type : " << Type << std::endl;
//    this->setStyleSheet("QMessageBox{background-color:rgb(46, 52, 54); } QMessageBox QPushButton { background-color: rgb(46, 52, 54); color: rgb(114, 159, 207);} QMessageBox QLabel{color:rgb(114, 159, 207);}");

    if(Type == MessageBoxType::information)
        QMessageBox::information(Parent, Title, Message);
    if(Type == MessageBoxType::error)
        QMessageBox::critical(Parent, Title, Message);

    return SUCCESS;

}


void MainWindow::worker()
{

    gmWorkerTerminated = false;

    while(1)
    {

        if(gmTerminateWorker == true)
            break;

        gpControlWindow->process();

        gpDisplaypanel->process();

        gpAutoControlWindow->process();


    }

    gmWorkerTerminated = true;

}

void MainWindow::terminateWorker()
{

    gmTerminateWorker = true;

    while(gmWorkerTerminated == false);

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



void MainWindow::setTitle(const std::string &IpAddress)
{

    char cmd[100];

    *gpIpAddress = IpAddress;

    snprintf(cmd, 100, "sudo sshpass -p \"hyperion\" ssh pi@%s hostname", gpIpAddress->c_str());

    std::cout << "running command: " << cmd << std::endl;
    std::string hostName = execCmd(cmd);

    std::cout << "hostname " << hostName << std::endl;
    gpMainWindow->setWindowTitle(QString(hostName.c_str()) + QString(" - ") + QString(gpIpAddress->c_str()));

}



void MainWindow::actionConnectionTriggered()
{
    gpConnectionWindow->show();
}



void MainWindow::actionUpdateFirmwareTriggered()
{

    std::string file;

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




void MainWindow::on_actionCalibration_Settings_triggered()
{
    gpCalibrationWindow->setDefaultCalibrationValues();
    gpCalibrationWindow->show();
}

void MainWindow::on_actionAutoControl_Settings_triggered()
{
    gpAutoControlWindow->show();
}

void MainWindow::on_actionCamera_Settings_triggered()
{

    CAMERA_SETTINGS_FORMAT CameraSettingsRequest;
    CameraSettingsRequest.write_enable = 0;

    gpController->sendCameraSettingsRequest(CameraSettingsRequest);
    gpCameraSettingsWindow->show();
}
