#ifndef CAMERASETTINGSPANEL_H
#define CAMERASETTINGSPANEL_H

#include "camerasettingswindow.h"
#include "ui_camerasettingswindow.h"
#include "socketlistener.h"

class CameraSettingsPanel : public CameraSettingsWindow, public SocketListener
{

    Q_OBJECT

public:

    CameraSettingsPanel(CameraSettingsWindow *Window, UdpSocket *SocketListener);
    virtual ~CameraSettingsPanel();

    void deployPanel(const CAMERA_SETTINGS_FORMAT &CameraSettings);
    void socketDataCheckCall();

private:
    UdpSocket *gpSocket;
    void attachtoCameraWindow();
    CameraSettingsWindow *gpCameraSettingsWindow;

signals:
    void setBrightness(int Value);
    void setContrast(int Value);
    void setSaturation(int Value);
    void setHue(int Value);

    void setExposure(int Value);
    void setAutoExposure(bool Value);

    void setGain(int Value);
    void setAutoGain(bool Value);

    void setHorizontalFlip(bool Value);
    void setVerticalFlip(bool Value);

    void setPowerFrequency(int Value);
    void setSharpness(int Value);

    void setZoom(int Value);

};

#endif // CAMERASETTINGSPANEL_H
