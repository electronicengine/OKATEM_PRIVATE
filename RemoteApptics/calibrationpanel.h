#ifndef CALIBRATIONPANEL_H
#define CALIBRATIONPANEL_H


#include "calibrationwindow.h"

class CalibrationPanel : public CalibrationWindow
{
    Q_OBJECT

public:
    CalibrationPanel(CalibrationWindow *Window);
    virtual ~CalibrationPanel();


signals:


private:
    CalibrationWindow *gpCalibrationWindow;

    void attachCalibrationWindow();

private slots:
    void accepted();
    void rejected();

};

#endif // CALIBRATIONPANEL_H
