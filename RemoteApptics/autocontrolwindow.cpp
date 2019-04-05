#include "ui_positionadd.h"
#include "autocontrolwindow.h"
#include "ui_autocontrolwindow.h"
#include "autocontrolpanel.h"
#include "autolockingpanel.h"

AutoControlWindow::AutoControlWindow(AutoControlWindow *Window) : MainWindow(true)
{

    ui = Window->ui;
    autocontrol_ui = Window->autocontrol_ui;

    gpControlWindow = Window->gpControlWindow;
    gpDisplaypanel = Window->gpDisplaypanel;
    gpCameraPanel = Window->gpCameraPanel;

    gpEnvironmentInfo = Window->gpEnvironmentInfo;
    gpControlInfo = Window->gpControlInfo;
    gpSfpInfo = Window->gpSfpInfo;

    gpController = Window->gpController;

    gpAutoControlWindow = Window->gpAutoControlWindow;
    gpAddingWindow = Window->gpAddingWindow;

    gpMutex = Window->gpMutex;
    gpFSOCenter = Window->gpFSOCenter;
    gpFSOPoints = Window->gpFSOPoints;

    gpSfpLinkAvailable = Window->gpSfpLinkAvailable;
    gpSfpConnectionAvailable = Window->gpSfpConnectionAvailable;
    gpConnectionAvailable = Window->gpConnectionAvailable;
    gpMainWindow = Window->gpMainWindow;

}



AutoControlWindow::AutoControlWindow(MainWindow *Window) :
    MainWindow(Window),
    autocontrol_ui(new Ui::AutoControlWindow)
{

    autocontrol_ui->setupUi(this);

    gpMutex = new std::mutex;
    gpFSOCenter = new cv::Point;
    gpFSOPoints = new int;

    gpAutoControlWindow = this;
    gpAddingWindow = new PositionAdd(this);

    gpAutoControlPanel = new AutoControlPanel(this);
    gpAutoLockingPanel = new AutoLockingPanel(this);

    connect(autocontrol_ui->add_button, SIGNAL(pressed()), this, SLOT(addButtonPressed()));
    connect(autocontrol_ui->delete_button, SIGNAL(pressed()), this, SLOT(deleteButtonPressed()));

    connect(autocontrol_ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged(QString)));
    connect(autocontrol_ui->start_button, SIGNAL(pressed()), this, SLOT(startButtonPressed()));
    connect(autocontrol_ui->stop_button, SIGNAL(pressed()), this, SLOT(stopButtonPressed()));
    connect(gpAddingWindow->ui->buttonBox, SIGNAL(accepted()), this, SLOT(commandAddAccepted()));
    connect(gpAddingWindow->ui->buttonBox, SIGNAL(rejected()), this, SLOT(commandAddRejected()));

    autocontrol_ui->comboBox->addItems(gmModeList);

}

void AutoControlWindow::markRow(int Row)
{

    autocontrol_ui->command_list->setCurrentItem(autocontrol_ui->command_list->item(Row));

}


void AutoControlWindow::deleteButtonPressed()
{
    gpAutoControlPanel->deleteCommand();
}



void AutoControlWindow::addButtonPressed()
{

    if(gpAddingWindow->ui->x_position->text() == NULL)
        gpAddingWindow->ui->x_position->setText(QString::number(gpEnvironmentInfo->step_motor2_step));

    if(gpAddingWindow->ui->y_position->text() == NULL)
        gpAddingWindow->ui->y_position->setText(QString::number(gpEnvironmentInfo->step_motor1_step));

    gpAddingWindow->show();
}


void AutoControlWindow::commandAddRejected()
{
    gpAddingWindow->hide();
}

void AutoControlWindow::addList(QString Str)
{
    autocontrol_ui->command_list->addItem(Str);
}

void AutoControlWindow::commandAddAccepted()
{

    std::cout << "commandAddAccepted" << std::endl;
    gpAddingWindow->hide();

    int command_type = gpAddingWindow->ui->stackedWidget->currentIndex();

    switch (command_type)
    {
        case position:

            gpAutoControlPanel->putPositionCommand();

            break;

        case direction:

            gpAutoControlPanel->putDirectionCommand();

            break;
    }

}



AutoControlWindow::~AutoControlWindow()
{
    delete autocontrol_ui;
    delete gpAutoControlPanel;
}

void AutoControlWindow::drawErrorVector(cv::Mat &Frame, cv::Point CurrentLoc)
{
    cv::line(Frame, CurrentLoc, gmTarget, cv::Scalar(0,0,255));
}

void AutoControlWindow::startLockingOperation()
{
    gpAutoLockingPanel->executeCommands();
}

void AutoControlWindow::setFsoPoints(const cv::Point &Center, int Points)
{
    gpMutex->lock();
    *gpFSOCenter = Center;
    *gpFSOPoints = Points;
    gpMutex->unlock();
}

void AutoControlWindow::process()
{


    if(*gpConnectionAvailable == true && gmAutoLockingEnable == true)
    {

        if(*gpSfpConnectionAvailable == false)
            gpAutoLockingPanel->executeCommands();

        if(*gpSfpConnectionAvailable == false &&
                *gpSfpLinkAvailable == true)
        {
            std::cout << "link broken" << std::endl;
        }


    }
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
            gmAutoLockingEnable = true;

            gpMutex->lock();
            gmTarget = cv::Point(
                        autocontrol_ui->position_x->text().toInt(),
                        autocontrol_ui->position_y->text().toInt());
            gpMutex->unlock();

            gpAutoLockingPanel->executeCommands();
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
