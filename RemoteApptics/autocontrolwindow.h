#ifndef AUTOCONTROLWINDOW_H
#define AUTOCONTROLWINDOW_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class AutoControlWindow;
}

class AutoControlPanel;

class AutoControlWindow : public MainWindow
{
    Q_OBJECT

public:
    AutoControlWindow(AutoControlWindow *Window);
    AutoControlWindow(MainWindow *Window);
    ~AutoControlWindow();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void startButtonPressed();
    void stopButtonPressed();

protected:
    AutoControlWindow *gpAutoControlWindow;
    Ui::AutoControlWindow *autocontrol_ui;



private:
    AutoControlPanel *gpAutoControlPanel;


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
