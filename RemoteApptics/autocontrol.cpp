#include "autocontrol.h"
#include "ui_autocontrol.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

AutoControl::AutoControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutoControl)
{
    ui->setupUi(this);

    ui->comboBox->addItems(gmModeList);


}

AutoControl::~AutoControl()
{
    delete ui;
}


void AutoControl::on_comboBox_currentTextChanged(const QString &arg1)
{

    for(int i=0; i<gmModeList.size(); i++)
    {

        if(arg1 == gmModeList.at(i).toLocal8Bit().constData())
        {
            gmMode = (Modes)i;

            ui->stackedWidget->setCurrentIndex(gmMode);

            switch (gmMode)
            {
                case AutoControlMode:
                    deployAutoControlPanel();
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

void AutoControl::deployAutoControlPanel()
{
    sleep(1);
    std::cout << "deploying auto control panel" << std::endl;
}

void AutoControl::deployAutoLockingPanel()
{
    std::cout << "deploying auto locking panel" << std::endl;
}

void AutoControl::deployCalibrationPanel()
{
    std::cout << "deploying calibration panel" << std::endl;
}
