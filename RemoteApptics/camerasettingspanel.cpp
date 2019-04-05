#include "camerasettingspanel.h"
#include "remotecontroller.h"


CameraSettingsPanel::CameraSettingsPanel(CameraSettingsWindow *Window, UdpSocket *Socket) :
    CameraSettingsWindow(Window), SocketListener(Socket)
{
    gpSocket = Socket;
    attachtoCameraWindow();
}

CameraSettingsPanel::~CameraSettingsPanel()
{

}

void CameraSettingsPanel::deployPanel(const CAMERA_SETTINGS_FORMAT &CameraSettings)
{

    emit setBrightness(CameraSettings.brighness);
    emit setContrast(CameraSettings.contrast);
    emit setSaturation(CameraSettings.saturation);
    emit setHue(CameraSettings.hue);

    emit setExposure(CameraSettings.exposure);
    emit setAutoExposure(CameraSettings.auto_exposure);

    emit setGain(CameraSettings.gain);
    emit setAutoGain(CameraSettings.auto_gain);

    emit setHorizontalFlip(CameraSettings.horizontal_flip);
    emit setVerticalFlip(CameraSettings.vertical_flip);

    emit setPowerFrequency(CameraSettings.horizontal_flip);
    emit setSharpness(CameraSettings.vertical_flip);

    emit setZoom(CameraSettings.zoom);

}

void CameraSettingsPanel::socketDataCheckCall()
{

    if(gpSocket->isEthernetConnected() == true)
    {

        *gpCameraSettingsData = gpControllerSocket->getCameraSettings();

        if(gpCameraSettingsData->available == true)
        {

            deployPanel(*gpCameraSettingsData);

        }

    }

}


void CameraSettingsPanel::attachtoCameraWindow()
{

    connect(this, SIGNAL(setBrightness(int)), camera_settings_ui->brightness_slider, SLOT(setValue(int)));
    connect(this, SIGNAL(setContrast(int)), camera_settings_ui->contrast_slider, SLOT(setValue(int)));
    connect(this, SIGNAL(setSaturation(int)), camera_settings_ui->saturation_slider, SLOT(setValue(int)));
    connect(this, SIGNAL(setHue(int)), camera_settings_ui->hue_slider, SLOT(setValue(int)));

    connect(this, SIGNAL(setAutoExposure(bool)), camera_settings_ui->auto_exposure_enable, SLOT(setChecked(bool)));
    connect(this, SIGNAL(setExposure(int)), camera_settings_ui->exposure_slider, SLOT(setValue(int)));

    connect(this, SIGNAL(setAutoGain(bool)), camera_settings_ui->auto_gain_enable, SLOT(setChecked(bool)));
    connect(this, SIGNAL(setGain(int)), camera_settings_ui->gain_slider, SLOT(setValue(int)));

    connect(this, SIGNAL(setHorizontalFlip(bool)), camera_settings_ui->horizontal_flip_enable, SLOT(setChecked(bool)));
    connect(this, SIGNAL(setVerticalFlip(bool)), camera_settings_ui->vertical_flip_enable, SLOT(setChecked(bool)));

    connect(this, SIGNAL(setPowerFrequency(int)), camera_settings_ui->power_frequency_slider, SLOT(setValue(int)));
    connect(this, SIGNAL(setSharpness(int)), camera_settings_ui->sharpness_slider, SLOT(setValue(int)));

    connect(this, SIGNAL(setZoom(int)), camera_settings_ui->zoom_slider, SLOT(setValue(int)));

}

