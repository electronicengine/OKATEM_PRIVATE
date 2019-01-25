#include "initialvaluesettings.h"
#include "ui_initialvaluesettings.h"

InitialValueSettings::InitialValueSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitialValueSettings)
{
    ui->setupUi(this);
}

InitialValueSettings::~InitialValueSettings()
{
    delete ui;
}

void InitialValueSettings::setDefaultValues(const CONTROL_DATA_FORMAT &ControlData)
{

//    ui->step1_current_step->setText(QString::number(ControlData.step_motor1_step));
//    ui->step2_current_step->setText(QString::number(ControlData.step_motor2_step));

//    ui->step1_max_step->setText(QString::number(ControlData.ste));
//    ui->step2_max_step->setText(QString::number(ControlData.step_motor1_step));



}
