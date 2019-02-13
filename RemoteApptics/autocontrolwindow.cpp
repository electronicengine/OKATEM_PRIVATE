#include "autocontrolwindow.h"
#include "ui_autocontrolwindow.h"
#include "autocontrolpanel.h"

AutoControlWindow::AutoControlWindow(AutoControlWindow *Window) : MainWindow(true)
{
    ui = Window->ui;
    autocontrol_ui = Window->autocontrol_ui;

    gpControlPanel = Window->gpControlPanel;
    gpDisplaypanel = Window->gpDisplaypanel;
    gpCameraPanel = Window->gpCameraPanel;

    gpEnvironmentInfo = Window->gpEnvironmentInfo;
    gpControlInfo = Window->gpControlInfo;
    gpSfpInfo = Window->gpSfpInfo;

    gpController = Window->gpController;

    gpAutoControlWindow = Window->gpAutoControlWindow;

    gpConnectionAvailable = Window->gpConnectionAvailable;

}



AutoControlWindow::AutoControlWindow(MainWindow *Window) :
    MainWindow(Window),
    autocontrol_ui(new Ui::AutoControlWindow)
{
    autocontrol_ui->setupUi(this);

    connect(autocontrol_ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged(QString)));
    connect(autocontrol_ui->start_button, SIGNAL(pressed()), this, SLOT(startButtonPressed()));
    connect(autocontrol_ui->stop_button, SIGNAL(pressed()), this, SLOT(stopButtonPressed()));

    autocontrol_ui->comboBox->addItems(gmModeList);

    gpAutoControlWindow = this;
    gpAutoControlPanel = new AutoControlPanel(this);


}



AutoControlWindow::~AutoControlWindow()
{
    delete autocontrol_ui;
    delete gpAutoControlPanel;
}



void AutoControlWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{

    for(int i=0; i<gmModeList.size(); i++)
    {

        if(arg1 == gmModeList.at(i).toLocal8Bit().constData())
        {
            gmMode = (Modes)i;

            autocontrol_ui->stackedWidget->setCurrentIndex(gmMode);

            switch (gmMode)
            {
                case AutoControlMode:
                    gpAutoControlPanel->deployPanel();
                    break;
                case AutoLockingMode:
                    deployAutoLockingPanel();
                    break;
                case CalibrationMode:
                    deployCalibrationPanel();
                    break;

                default:
                    break;
            }
        }
    }
}

void AutoControlWindow::startButtonPressed()
{

    std::cout << "start button pressed" << std::endl;
    switch (gmMode)
    {
        case AutoControlMode:
            gpAutoControlPanel->executeCommands();
            break;
        case AutoLockingMode:
//            deployAutoLockingPanel();
            break;
        case CalibrationMode:
//            deployCalibrationPanel();
            break;

        default:
            break;
    }

}

void AutoControlWindow::stopButtonPressed()
{
    std::cout << "stop button pressed" << std::endl;
    switch (gmMode)
    {
        case AutoControlMode:
            gpAutoControlPanel->stopExecution();
            break;
        case AutoLockingMode:
//            deployAutoLockingPanel();
            break;
        case CalibrationMode:
//            deployCalibrationPanel();
            break;

        default:
            break;
    }
}



void AutoControlWindow::deployAutoLockingPanel()
{
    std::cout << "deploying auto locking panel" << std::endl;
}

void AutoControlWindow::deployCalibrationPanel()
{
    std::cout << "deploying calibration panel" << std::endl;
}
