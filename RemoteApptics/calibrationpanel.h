#ifndef CALIBRATIONPANEL_H
#define CALIBRATIONPANEL_H


#include "calibrationwindow.h"

class CalibrationPanel : public CalibrationWindow
{
    Q_OBJECT

public:
    CalibrationPanel(CalibrationWindow *Window);
    virtual ~CalibrationPanel();
    void deployPanel();

signals:
    void setStep1Current(QString);
    void setStep2Current(QString);

    void setStep1Max(QString);
    void setStep2Max(QString);

    void setServo1Current(QString);
    void setServo2Current(QString);

    void setServo1Top(QString);
    void setServo2Top(QString);

    void setServo1Bottom(QString);
    void setServo2Bottom(QString);

private:
    CalibrationWindow *gpCalibrationWindow;

    void attachCalibrationWindow();


};

#endif // CALIBRATIONPANEL_H
