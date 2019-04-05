#ifndef CAMERASETTINGSWINDOW_H
#define CAMERASETTINGSWINDOW_H

#include <QWidget>
#include "mainwindow.h"

class CameraSettingsPanel;

namespace Ui {
class CameraSettingsWindow;
}

class CameraSettingsWindow : public MainWindow
{
    Q_OBJECT

public:

    CameraSettingsWindow(CameraSettingsWindow *Window);
    CameraSettingsWindow(MainWindow *Window);
    ~CameraSettingsWindow();


protected:
    Ui::CameraSettingsWindow *camera_settings_ui;
    CAMERA_SETTINGS_FORMAT *gpCameraSettingsData;

private slots:
    void cameraSettingsAccepted();

    void brighnessSliderChanged(int Value);
    void contrastSliderChanged(int Value);
    void saturationSliderChanged(int Value);
    void hueSliderChanged(int Value);

    void exposureSliderChanged(int Value);
    void autoExposureTriggered(bool Value);

    void gainSliderChanged(int Value);
    void autoGainTriggered(bool Value);

    void horizontalFlipTriggered(bool Value);
    void verticalFlipTriggered(bool Value);

    void powerFrequencySliderChanged(int Value);
    void sharpnessSliderChanged(int Value);

    void zoomSliderChanged(int Value);

private:

    CameraSettingsPanel *gpCameraSettingsPanel;

    void attachtoMainWindow();
    CAMERA_SETTINGS_FORMAT getOldSettings();

};

#endif // CAMERASETTINGSWINDOW_H
