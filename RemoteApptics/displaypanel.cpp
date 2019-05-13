#include "displaypanel.h"
#include "QMessageBox"
#include "controlwindow.h"

DisplayPanel::DisplayPanel(MainWindow *Window) : MainWindow(Window)
{

    attachWindow();

}

DisplayPanel::~DisplayPanel()
{
    delete gpController;
}

void DisplayPanel::switchWifi()
{

    emit setSfpConnectionImageVisibilty(false);
    emit setWifiConnectionImageVisibilty(true);
    emit setConnectionTypeLabel("<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">WIFI </span></p><p align=\"center\"><span style=\" font-weight:600;\">CONNECTED</span></p></body></html>");


}

void DisplayPanel::switchSfp()
{
    emit setSfpConnectionImageVisibilty(true);
    emit setWifiConnectionImageVisibilty(false);
    emit setConnectionTypeLabel("<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">SFP </span></p><p align=\"center\"><span style=\" font-weight:600;\">CONNECTED</span></p></body></html>");

}

void DisplayPanel::attachWindow()
{
    connect(this, SIGNAL(setConnectionTypeLabel(QString)), ui->connection_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(setSfpConnectionImageVisibilty(bool)), ui->connection_image_sfp, SLOT(setVisible(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(setWifiConnectionImageVisibilty(bool)), ui->connection_image_wifi, SLOT(setVisible(bool)), Qt::QueuedConnection);

    connect(this, SIGNAL(progressUpdateFile(int)), ui->progressBar, SLOT(setValue(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(setprogessbarvisibility(bool)), ui->progressBar, SLOT(setVisible(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(setupdatelabelvisibility(bool)), ui->update_label, SLOT(setVisible(bool)), Qt::QueuedConnection);
    connect(this, SIGNAL(showMessageBox(QWidget*, QString, QString, MessageBoxType)), gpMainWindow, SLOT(showMessage(QWidget*,QString, QString , MessageBoxType)), Qt::BlockingQueuedConnection);

    connect(this, SIGNAL(refreshStatusLabel(QString)), ui->status_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshTxPowerLabel(QString)), ui->tx_power_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshRxPowerLabel(QString)), ui->rx_power_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshTemperatureLabel(QString)), ui->temperature_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshPressureLabel(QString)), ui->pressure_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshAltitudeLabel(QString)), ui->altitude_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshCompassLabel(QString)), ui->compass_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshNMEALabel(QString)), ui->nmea_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshStep1PosLabel(QString)), ui->step1_pos_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(setStyleSheetofStep1(QString)), ui->step1_pos_label, SLOT(setStyleSheet(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(refreshStep2PosLabel(QString)), ui->step2_pos_label, SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(setStyleSheetofStep2(QString)), ui->step2_pos_label, SLOT(setStyleSheet(QString)), Qt::QueuedConnection);

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



void DisplayPanel::upgradingFirmworkCallBack(int Percentage)
{

    std::cout << "percent: " << std::to_string(Percentage) << std::endl;

    if(Percentage > 0 && Percentage < 100)
    {
        gmUpgradingAvailable = true;
        gpControlWindow->setPanelEnable(false);

        std::cout << "%" << std::to_string(Percentage) << " upgraded" << std::endl;
        emit setprogessbarvisibility(true);
        emit setupdatelabelvisibility(true);

        emit progressUpdateFile(Percentage);


    }else if(Percentage >= 100)
    {

        std::cout << "Update is done Percent: " << std::to_string(Percentage)  << std::endl;

        emit progressUpdateFile(Percentage);

        emit setprogessbarvisibility(false);
        emit setupdatelabelvisibility(false);

        gpControlWindow->setPanelEnable(true);

        gmUpgradingAvailable = false;

        emit showMessageBox(gpMainWindow, "Firmware Update Done","The FirmWare Upgrading has been finished Succesfully!",
                            MessageBoxType::information);

        gpController->resetUpdatePercentage();


    }
    else
    {
        emit setprogessbarvisibility(false);
        emit setupdatelabelvisibility(false);

    }

}



void DisplayPanel::ethernetConnectionLostCallBack()
{

    if(*gpConnectionAvailable != false)
    {

        emit showMessageBox(gpMainWindow, "Connection Error","The Ethernet Connection has been lost! Program will be terminated.",
                            MessageBoxType::error);
        std::cout << "Ethernet connection has been lost" << std::endl;

        *gpConnectionAvailable = false;


        exit(0);


    }

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


    if((gpEnvironmentInfo->step_motor_breaks & 0x0f) == 0)
        emit setStyleSheetofStep1("color: rgb(255, 0, 0); background-color: transparent;");
    else
        emit setStyleSheetofStep1("color: rgb(114, 159, 207); background-color: transparent;");

    if((gpEnvironmentInfo->step_motor_breaks & 0xf0) >> 4 == 0)
        emit setStyleSheetofStep2("color: rgb(255, 0, 0); background-color: transparent;");
    else
        emit setStyleSheetofStep2("color: rgb(114, 159, 207); background-color: transparent;");


    *gpSfpConnectionAvailable = (gpSfpInfo->status == 1) ? true:false;

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

int DisplayPanel::startDisplayManager()
{

    int ret;

    ret = gpController->start(*gpIpAddress, *gpControlPort ,this);
    if(ret == FAIL)
    {
        std::cout << "Controller socket can not be opened:  "<< *gpIpAddress << std::endl;

        return FAIL;
    }

    return SUCCESS;
}



void DisplayPanel::panelInformationCallBack(const INFORMATION_DATA_FORMAT &InformationData)
{

    if(*gpConnectionAvailable != true)
    {

        std::cout << "connection established" << std::endl;
        *gpConnectionAvailable = true;

        *gpControlInfo = InformationData.control_data;
        *gpEnvironmentInfo = InformationData.environment_data;
        *gpSfpInfo = InformationData.sfp_data;

        gpControlWindow->setServoSliderInitialValues(gpControlInfo->servo_motor1_degree, gpControlInfo->servo_motor2_degree);

        deployPanel();

        emit showMessageBox(gpMainWindow, "Connection", "Connection Established", MessageBoxType::information);

    }
    else
    {

        *gpControlInfo = InformationData.control_data;
        *gpEnvironmentInfo = InformationData.environment_data;
        *gpSfpInfo = InformationData.sfp_data;

        deployPanel();

    }


}





void DisplayPanel::process()
{

    static int counter = 0;
    counter++;

    if(counter >= 20 && gmUpgradingAvailable == false)
    {
        counter = 0;


        gpController->sendInformationRequest();


    }



}

