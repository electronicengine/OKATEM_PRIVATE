#ifndef AUTOCONTROLWINDOW_H
#define AUTOCONTROLWINDOW_H

#include <QWidget>
#include "mainwindow.h"
#include "positionadd.h"


namespace Ui {
class AutoControlWindow;
}

class AutoControlPanel;
class AutoLockingPanel;

class AutoControlWindow : public MainWindow
{
    Q_OBJECT

public:
    AutoControlWindow(AutoControlWindow *Window);
    AutoControlWindow(MainWindow *Window);
    ~AutoControlWindow();

    void drawErrorVector(cv::Mat &Frame, cv::Point CurrentLoc);
    void startLockingOperation();
    void setFsoPoints(const cv::Point &Center, int Points);
    void process();


private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void startButtonPressed();
    void stopButtonPressed();

    void addButtonPressed();
    void deleteButtonPressed();
    void commandAddAccepted();
    void commandAddRejected();
    void addList(QString);
    void markRow(int Row);

protected:
    AutoControlWindow *gpAutoControlWindow;
    Ui::AutoControlWindow *autocontrol_ui;
    PositionAdd *gpAddingWindow;

    cv::Point *gpFSOCenter;
    int *gpFSOPoints;

    std::mutex *gpMutex;

private:

    cv::Point gmTarget;
    AutoControlPanel *gpAutoControlPanel;
    AutoLockingPanel *gpAutoLockingPanel;

    enum Modes
    {
        AutoControlMode,
        AutoLockingMode,
        CalibrationMode
    }gmMode;

    QStringList gmModeList = {"Auto Control", "Auto Locking", "Calibration"};

    volatile bool gmAutoLockingEnable = false;
    void deployAutoLockingPanel();
    void deployCalibrationPanel();
};

#endif // AUTOCONTROLWINDOW_H
