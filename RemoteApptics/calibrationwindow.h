#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include "mainwindow.h"


class CalibrationPanel;

namespace Ui {
class CalibrationWindow;
}

class CalibrationWindow : public MainWindow
{
    Q_OBJECT


public:

    CalibrationWindow(CalibrationWindow *Window);
   explicit CalibrationWindow(MainWindow *Window);
   virtual ~CalibrationWindow();
   void setDefaultCalibrationValues();

private slots:
    void accepted();
    void rejected();

private:
    CalibrationWindow *gpCalibrationWindow;
    CalibrationPanel *gpCalibrationPanel;

protected:
   Ui::CalibrationWindow *calibration_ui;

};



#endif // CALIBRATIONWINDOW_H
