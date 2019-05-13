#ifndef DISPLAYPANEL_H
#define DISPLAYPANEL_H


#include "QMessageBox"
#include "ui_mainwindow.h"
#include "mainwindow.h"




class DisplayPanel : public MainWindow
{

    Q_OBJECT

public:
    DisplayPanel(MainWindow *Window);
    virtual ~DisplayPanel();

    void switchWifi();
    void switchSfp();

    void process();
    void deployPanel();
    int startDisplayManager();

    void panelInformationCallBack(const INFORMATION_DATA_FORMAT& InformationData);
    void upgradingFirmworkCallBack(int UpdatePercentage);
    void ethernetConnectionLostCallBack();

private:

    volatile bool gmUpgradingAvailable = false;

    void attachWindow();

signals:

    void setConnectionTypeLabel(QString);
    void setSfpConnectionImageVisibilty(bool);
    void setWifiConnectionImageVisibilty(bool);

    int showMessageBox(QWidget *, QString, QString, MessageBoxType);
    void progressUpdateFile(int);
    void setprogessbarvisibility(bool);
    void setupdatelabelvisibility(bool);
    void statusLabelClose();
    void statusLabelShow();
    void refreshStatusLabel(const QString &Text);
    void txPowerLabelClose();
    void txPowerLabelShow();
    void refreshTxPowerLabel(const QString &Text);
    void rxPowerLabelClose();
    void rxPowerLabelShow();
    void refreshRxPowerLabel(const QString &Text);
    void temperatureLabelClose();
    void temperatureLabelShow();
    void refreshTemperatureLabel(const QString &Text);
    void pressureLabelClose();
    void pressureLabelShow();
    void refreshPressureLabel(const QString &Text);
    void altitudeLabelClose();
    void altitudeLabelShow();
    void refreshAltitudeLabel(const QString &Text);
    void compassLabelClose();
    void compassLabelShow();
    void refreshCompassLabel(const QString &Text);
    void step1PosLabelClose();
    void step1PosLabelShow();
    void refreshStep1PosLabel(const QString &Text);
    void setStyleSheetofStep1(const QString &Text);
    void step2PosLabelClose();
    void step2PosLabelShow();
    void refreshStep2PosLabel(const QString &Text);
    void setStyleSheetofStep2(const QString &Text);
    void nmeaLabelClose();
    void nmeaLabelShow();
    void refreshNMEALabel(const QString &Text);

};

#endif // DISPLAYPANEL_H
