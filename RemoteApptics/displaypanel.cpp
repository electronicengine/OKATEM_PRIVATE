#include "displaypanel.h"
#include "QMessageBox"


DisplayPanel::DisplayPanel(MainWindow *Window) : MainWindow(Window)
{

    attachWindow();

}

void DisplayPanel::attachWindow()
{
    connect(this, SIGNAL(progressUpdateFile(int)), ui->progressBar, SLOT(setValue(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(setprogessbarvisibility(bool)), ui->progressBar, SLOT(setVisible(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(setupdatelabelvisibility(bool)), ui->update_label, SLOT(setVisible(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(showMessageBox(QString)), this, SLOT(showMessage(QString)), Qt::BlockingQueuedConnection);

    connect(this, SIGNAL(refreshStatusLabel(QString)), ui->status_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshTxPowerLabel(QString)), ui->tx_power_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshRxPowerLabel(QString)), ui->rx_power_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshTemperatureLabel(QString)), ui->temperature_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshPressureLabel(QString)), ui->pressure_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshAltitudeLabel(QString)), ui->altitude_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshCompassLabel(QString)), ui->compass_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshNMEALabel(QString)), ui->nmea_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshStep1PosLabel(QString)), ui->step1_pos_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshStep2PosLabel(QString)), ui->step2_pos_label, SLOT(setText(QString)), Qt::QueuedConnection);

    connect(this, SIGNAL(statusLabelClose()), ui->status_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(statusLabelShow()), ui->status_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(txPowerLabelClose()), ui->tx_power_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(txPowerLabelShow()), ui->tx_power_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(rxPowerLabelClose()), ui->rx_power_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(rxPowerLabelShow()), ui->rx_power_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(temperatureLabelClose()), ui->temperature_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(temperatureLabelShow()), ui->temperature_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(pressureLabelClose()), ui->pressure_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(pressureLabelShow()), ui->pressure_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(altitudeLabelClose()), ui->altitude_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(altitudeLabelClose()), ui->altitude_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(compassLabelClose()), ui->compass_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(compassLabelShow()), ui->compass_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(nmeaLabelClose()), ui->nmea_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(nmeaLabelShow()), ui->nmea_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(step1PosLabelClose()), ui->nmea_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(step1PosLabelShow()), ui->nmea_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(step2PosLabelClose()), ui->nmea_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(step2PosLabelShow()), ui->nmea_label, SLOT(show()), Qt::QueuedConnection);


    emit setprogessbarvisibility(false);
    emit setupdatelabelvisibility(false);


}


int DisplayPanel::checkFirmwareUpdateAvailable()
{
    int percent;

    static int update_done = true;

    percent = gpController->getUpdatePercentage();

    if(percent > 0 && percent < 100)
    {

        update_done = false;

         emit setprogessbarvisibility(true);
         emit setupdatelabelvisibility(true);

         emit progressUpdateFile(percent);

        return SUCCESS;

    }else if(percent >= 100 && update_done == false)
    {
        emit setprogessbarvisibility(false);
        emit setupdatelabelvisibility(false);

        emit progressUpdateFile(percent);

        update_done = true;

//            setPanelEnable(true);

        emit showMessageBox("The FirmWare Upgrading has been finished Succesfully!");

        gpController->resetUpdatePercentage();


        return FAIL;
    }
    else
    {
        emit setprogessbarvisibility(false);
        emit setupdatelabelvisibility(false);

        return FAIL;
    }



}

int DisplayPanel::showMessage(const QString &Str)
{

    this->setStyleSheet("QMessageBox{background-color:rgb(46, 52, 54); } QMessageBox QPushButton { background-color: rgb(46, 52, 54); color: rgb(114, 159, 207);} QMessageBox QLabel{color:rgb(114, 159, 207);}");
    return QMessageBox::information(this,"Upgrade Done",Str);

}

void DisplayPanel::deployPanel()
{

    static int counter = 0;

    counter++;

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


    emit refreshStatusLabel((gpSfpInfo->status == 1) ? "Connected":"Disconnected");
    emit refreshTxPowerLabel(QString::number(gpSfpInfo->tx_power));
    emit refreshRxPowerLabel(QString::number(gpSfpInfo->rx_power));
    emit refreshTemperatureLabel(QString::number(gpEnvironmentInfo->sensor_data.temperature));
    emit refreshPressureLabel(QString::number(gpEnvironmentInfo->sensor_data.pressure));
    emit refreshAltitudeLabel(QString::number(gpEnvironmentInfo->sensor_data.altitude));
    emit refreshCompassLabel(QString::number(gpEnvironmentInfo->sensor_data.compass_degree));
    emit refreshNMEALabel(QString(gpEnvironmentInfo->gps_string.c_str()));
    emit refreshStep1PosLabel(QString::number(gpEnvironmentInfo->step_motor1_step));
    emit refreshStep2PosLabel(QString::number(gpEnvironmentInfo->step_motor2_step));



}

void DisplayPanel::preparePanelInfo()
{

    int ret;



    ret = gpController->getFsoInformations(*gpControlInfo, *gpEnvironmentInfo, *gpSfpInfo);

        if(ret == SUCCESS)
            deployPanel();
        else
            std::cout << "Panel Data can not be received" << std::endl;




}





void DisplayPanel::process()
{

    static int counter = 0;
    int ret;

    counter++;

    if(counter >= 20)
    {
        counter = 0;

        ret = checkFirmwareUpdateAvailable();

        if(ret != SUCCESS)
            preparePanelInfo();

    }



}

