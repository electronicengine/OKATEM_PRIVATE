//#include "connectiondialog.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include "controlpanel.h"
#include "displaypanel.h"
#include "camerapanel.h"
#include "connectionwindow.h"
#include "calibrationwindow.h"

#include <thread>
#include <QMessageBox>



MainWindow::MainWindow(bool Constructed)
{
    std::cout << "MainWindow Constructed" << Constructed << std::endl;
}



MainWindow::MainWindow(MainWindow *Window)
{

    ui = Window->ui;
    gpController = Window->gpController;
    gpStream = Window->gpStream;


    gpVideoStreamSocket = Window->gpVideoStreamSocket;

    gpControlInfo = Window->gpControlInfo;
    gpEnvironmentInfo = Window->gpEnvironmentInfo;
    gpSfpInfo = Window->gpSfpInfo;

    gpMainWindow = Window->gpMainWindow;

}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QPixmap pix;

    ui->setupUi(this);

    connect(ui->actionConnection, SIGNAL(triggered(bool)), this, SLOT(actionConnectionTriggered()));
    connect(ui->actionAuto_Control_Settings, SIGNAL(triggered(bool)), this, SLOT(on_actionAuto_Control_Settings_triggered()));
    connect(ui->actionSet_Initial_Values, SIGNAL(triggered(bool)), this, SLOT(on_actionSet_Initial_Values_triggered()));
    connect(ui->actionUpdate_Firmware, SIGNAL(triggered(bool)), this, SLOT(actionUpdateFirmwareTriggered()));

    gpMainWindow = this;

    gpControlInfo = new CONTROL_DATA_FORMAT;
    gpEnvironmentInfo = new ENVIRONMENT_DATA_FORMAT;
    gpSfpInfo = new SFP_DATA_FORMAT;

    gpControllerSocket = new UdpSocket;
    gpVideoStreamSocket = new UdpSocket;

    gpAutoControl = new AutoControl;

    gpController = new RemoteController(gpControllerSocket);
    gpStream = new VideoStream(gpVideoStreamSocket);


    gpControlPanel = new ControlPanel(this);
    gpDisplaypanel = new DisplayPanel(this);
    gpCameraPanel = new CameraPanel(this);


    ui->toggle_button->setCheckable(true);
    pix.load("hyperion.jpg");
    ui->frame_label->setPixmap(pix);

    gpConnectionWindow = new ConnectionWindow(this);
    gpCalibrationWindow = new CalibrationWindow(this);

    std::thread controlThread(&MainWindow::worker, this);
    controlThread.detach();



    gpControlPanel->setPanelEnable(false);

}



MainWindow::~MainWindow()
{

    gpVideoStreamSocket->terminate();
    gpController->terminate();

    delete ui;    
    delete gpAutoControl;


}



void MainWindow::worker()
{

    static int connection_established = false;

    while(1)
    {

        if(gmConnectionAvailable == true)
        {

            connection_established = true;

            gpControlPanel->process();

            gpDisplaypanel->process();

        }
        else
        {

            if(connection_established != false)
                emit gpDisplaypanel->showMessageBox("Connection Error", "Ethernet Connection has been lost", MessageBoxType::error);

            connection_established = false;
        }



    }

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

    gmIpAddress = IpAddress;


    snprintf(cmd, 100, "sudo sshpass -p \"hyperion\" ssh pi@%s hostname", gmIpAddress.c_str());

    std::cout << "running command: " << cmd << std::endl;
    std::string hostName = execCmd(cmd);

    std::cout << "hostname " << hostName << std::endl;

    gpMainWindow->setWindowTitle(QString(hostName.c_str()) + QString(" - ") + QString(gmIpAddress.c_str()));
//    MainWindow::setWindowTitle(QString(hostName.c_str()) + QString(" - ") + QString(gmIpAddress.c_str()));

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





void MainWindow::on_actionSet_Initial_Values_triggered()
{
    gpCalibrationWindow->deployTextBoxes();
    gpCalibrationWindow->show();
}



void MainWindow::on_actionAuto_Control_Settings_triggered()
{
    gpAutoControl->show();

}
