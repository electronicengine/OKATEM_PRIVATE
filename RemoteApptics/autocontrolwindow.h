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

    void startLockingOperation();
    void setFsoPoints(cv::Mat &Frame, std::vector<cv::Point> &Points);
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



private:

    AutoControlPanel *gpAutoControlPanel;
    AutoLockingPanel *gpAutoLockingPanel;

    enum Modes
    {
        AutoControlMode,
        AutoLockingMode,
        CalibrationMode
    }gmMode;

    QStringList gmModeList = {"Auto Control", "Auto Locking", "Calibration"};

    void deployAutoLockingPanel();
    void deployCalibrationPanel();
};

#endif // AUTOCONTROLWINDOW_H
