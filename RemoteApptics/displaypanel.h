#ifndef DISPLAYPANEL_H
#define DISPLAYPANEL_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

class DisplayPanel : public MainWindow
{

    Q_OBJECT

public:
    DisplayPanel(MainWindow *Window);

    void process();
    void deployPanel();



private:
    void attachWindow();
    void preparePanelInfo();
    int checkFirmwareUpdateAvailable();

    bool *gpConnectionEstablished;

private slots:
    int showMessage(const QString &Str);

signals:


    int showMessageBox(QString);
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
    void step2PosLabelClose();
    void step2PosLabelShow();
    void refreshStep2PosLabel(const QString &Text);
    void nmeaLabelClose();
    void nmeaLabelShow();
    void refreshNMEALabel(const QString &Text);



};

#endif // DISPLAYPANEL_H
