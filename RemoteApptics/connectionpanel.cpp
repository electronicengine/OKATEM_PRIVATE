#include "connectionpanel.h"
#include "QMessageBox"
#include "camerapanel.h"
#include "displaypanel.h"
#include "controlwindow.h"



ConnectionPanel::ConnectionPanel(ConnectionWindow *Window) : ConnectionWindow(Window)
{

    connection_ui->comboBox->addItems(gmConnectionList);
    gpConnectionWindow = Window;

    attachConnectionWindow();


}



void ConnectionPanel::attachConnectionWindow()
{

    connect(this, SIGNAL(setIpAddress(QString)), connection_ui->ip_address_text, SLOT(setText(QString)));
    connect(this, SIGNAL(setStreamPort(QString)), connection_ui->stream_port_text, SLOT(setText(QString)));
    connect(this, SIGNAL(setControlPort(QString)), connection_ui->control_port_text, SLOT(setText(QString)));
    connect(this, SIGNAL(hideConnectionWindow()), gpConnectionWindow, SLOT(hide()));
    connect(this, SIGNAL(hideButtonBox()), connection_ui->buttonBox, SLOT(hide()));
    connect(this, SIGNAL(showMessageBox(QWidget*, QString, QString, MessageBoxType)), gpMainWindow, SLOT(showMessage(QWidget*,QString, QString , MessageBoxType)), Qt::BlockingQueuedConnection);

}



int ConnectionPanel::startConnection()
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

            setTitle(*gpIpAddress);

            gpControlWindow->setPanelEnable(true);

            gpDisplaypanel->deployPanel();

            emit hideButtonBox();

            emit hideConnectionWindow();


            return SUCCESS;

        }
        else
        {
            *gpConnectionAvailable = false;

            showMessage(gpMainWindow, "Error", "Connection can not be established", MessageBoxType::error);

            return FAIL;
        }


    }
    else
    {
        *gpConnectionAvailable = false;

        showMessage(gpMainWindow, "Error", "Connection can not be established", MessageBoxType::error);

        return FAIL;
    }


}






void ConnectionPanel::deployPanel(int Index)
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


