#ifndef AUTOCONTROL_H
#define AUTOCONTROL_H

#include <QDialog>
#include <iostream>

namespace Ui {
class AutoControl;
}

class AutoControl : public QDialog
{
    Q_OBJECT


public:
    explicit AutoControl(QWidget *parent = nullptr);
    ~AutoControl();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::AutoControl *ui;

    enum Modes
    {
        AutoControlMode,
        AutoLockingMode,
        CalibrationMode
    }gmMode;

    QStringList gmModeList = {"Auto Control", "Auto Locking", "Calibration"};

    void deployAutoControlPanel();

    void deployAutoLockingPanel();

    void deployCalibrationPanel();

};

#endif // AUTOCONTROL_H
