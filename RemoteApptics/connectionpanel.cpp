#include "connectionpanel.h"
#include "QMessageBox"
#include "camerapanel.h"
#include "displaypanel.h"
#include "controlpanel.h"



ConnectionPanel::ConnectionPanel(ConnectionWindow *Window) : ConnectionWindow(Window)
{

    attachConnectionWindow();
    connection_ui->comboBox->addItems(gmConnectionList);
    gpConnectionWindow = Window;

}



void ConnectionPanel::attachConnectionWindow()
{

    connect(connection_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(connection_ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
    connect(connection_ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxIndexChanged(int)));

    connect(this, SIGNAL(setIpAddress(QString)), connection_ui->ip_address_text, SLOT(setText(QString)));
    connect(this, SIGNAL(setStreamPort(QString)), connection_ui->stream_port_text, SLOT(setText(QString)));
    connect(this, SIGNAL(setControlPort(QString)), connection_ui->control_port_text, SLOT(setText(QString)));

}



void ConnectionPanel::accepted()
{
    int ret;

    *gpIpAddress = connection_ui->ip_address_text->text().toStdString();
    *gpStreamPort = connection_ui->stream_port_text->text().toInt();
    *gpControlPort = connection_ui->control_port_text->text().toInt();

    std::cout << "Connection Ip: " << *gpIpAddress << " Stream Port: " << *gpStreamPort << " Control Port: " << *gpControlPort << std::endl;

    ret = gpDisplaypanel->startDisplayManager();

    if(ret == SUCCESS)
    {

        ret = gpCameraPanel->startCamera();

        if(ret == SUCCESS)
        {
            *gpConnectionAvailable = true;

            QMessageBox::information(gpConnectionWindow, "Info", "Connection Established");

            setTitle(*gpIpAddress);

            gpControlPanel->setPanelEnable(true);

            gpControlPanel->setServoSliderInitialValues(gpControlInfo->servo_motor1_degree, gpControlInfo->servo_motor2_degree);

            gpDisplaypanel->deployPanel();

            connection_ui->buttonBox->hide();

            gpConnectionWindow->hide();

        }
        else
        {
            *gpConnectionAvailable = false;

            QMessageBox::critical(gpConnectionWindow, "Error", "Connection can not be established");
        }


    }
    else
    {
        *gpConnectionAvailable = false;

        QMessageBox::critical(gpConnectionWindow, "Error", "Connection can not be established");
    }


}



void ConnectionPanel::rejected()
{

}



void ConnectionPanel::comboBoxIndexChanged(int Index)
{

    switch (Index) {
    case juliet:

        emit setIpAddress("10.100.93.62");
        emit setStreamPort("27000");
        emit setControlPort("25000");

        break;
    case romeo:

        emit setIpAddress("10.100.93.61");
        emit setStreamPort("26000");
        emit setControlPort("24000");

        break;
    default:
        break;
    }
}

void ConnectionPanel::closed()
{
    this->hide();
}
