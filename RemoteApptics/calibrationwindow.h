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

    void deployTextBoxes();

private:
    CalibrationPanel *gpCalibrationPanel;
    CalibrationWindow *gpCalibrationWindow;

protected:
   Ui::CalibrationWindow *calibration_ui;

   bool *gpConnectionAvailable;

   std::string *gpIpAddress;
   int *gpStreamPort;
   int *gpControlPort;
};



#endif // CALIBRATIONWINDOW_H
