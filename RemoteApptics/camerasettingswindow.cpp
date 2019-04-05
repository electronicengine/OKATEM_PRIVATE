#include "camerasettingswindow.h"
#include "ui_camerasettingswindow.h"
#include "camerasettingspanel.h"


CameraSettingsWindow::CameraSettingsWindow(CameraSettingsWindow *Window) : MainWindow(true)
{

    ui = Window->ui;
    camera_settings_ui = Window->camera_settings_ui;

    gpControlWindow = Window->gpControlWindow;

    gpIpAddress = Window->gpIpAddress;
    gpStreamPort = Window->gpStreamPort;
    gpControlPort = Window->gpControlPort;
    gpControllerSocket = Window->gpControllerSocket;

    gpConnectionAvailable = Window->gpConnectionAvailable;
    gpCameraSettingsWindow = Window->gpCameraSettingsWindow;

    gpCameraSettingsData = Window->gpCameraSettingsData;

}



CameraSettingsWindow::CameraSettingsWindow(MainWindow *Window) :
    MainWindow(Window),
    camera_settings_ui(new Ui::CameraSettingsWindow)
{
    camera_settings_ui->setupUi(this);

    gpCameraSettingsWindow = this;

    attachtoMainWindow();

    gpCameraSettingsData = new CAMERA_SETTINGS_FORMAT;
    gpCameraSettingsPanel = new CameraSettingsPanel(this, gpControllerSocket);

}



CameraSettingsWindow::~CameraSettingsWindow()
{
    delete camera_settings_ui;
}

void CameraSettingsWindow::cameraSettingsAccepted()
{
    std::cout << "gpCameraSettingsWindow hiding" << std::endl;
    gpCameraSettingsWindow->hide();
}




void CameraSettingsWindow::brighnessSliderChanged(int Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;


    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.brighness = Value;
        camera_settings.write_enable = 0xff;
        camera_settings_ui->brignes_value->setText(QString::number(Value));

        gpControllerSocket->sendData(camera_settings);
    }

}

void CameraSettingsWindow::contrastSliderChanged(int Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.contrast = Value;
        camera_settings.write_enable = 0xff;
        camera_settings_ui->contrast_value->setText(QString::number(Value));

        gpControllerSocket->sendData(camera_settings);
    }
}

void CameraSettingsWindow::saturationSliderChanged(int Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.saturation = Value;
        camera_settings.write_enable = 0xff;
        camera_settings_ui->saturation_value->setText(QString::number(Value));

        gpControllerSocket->sendData(camera_settings);
    }
}

void CameraSettingsWindow::hueSliderChanged(int Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.hue = Value;
        camera_settings.write_enable = 0xff;
        camera_settings_ui->hue_value->setText(QString::number(Value));

        gpControllerSocket->sendData(camera_settings);
    }
}

void CameraSettingsWindow::exposureSliderChanged(int Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.exposure = Value;
        camera_settings.write_enable = 0xff;
        camera_settings_ui->exposure_value->setText(QString::number(Value));

        gpControllerSocket->sendData(camera_settings);
    }
}

void CameraSettingsWindow::autoExposureTriggered(bool Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.auto_exposure = Value;
        camera_settings.write_enable = 0xff;

        gpControllerSocket->sendData(camera_settings);
    }
}

void CameraSettingsWindow::gainSliderChanged(int Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.gain = Value;
        camera_settings.write_enable = 0xff;
        camera_settings_ui->gain_value->setText(QString::number(Value));

        gpControllerSocket->sendData(camera_settings);
    }
}

void CameraSettingsWindow::autoGainTriggered(bool Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.auto_gain = Value;
        camera_settings.write_enable = 0xff;

        gpControllerSocket->sendData(camera_settings);
    }
}

void CameraSettingsWindow::horizontalFlipTriggered(bool Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.horizontal_flip = Value;
        camera_settings.write_enable = 0xff;

        gpControllerSocket->sendData(camera_settings);
    }
}

void CameraSettingsWindow::verticalFlipTriggered(bool Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.vertical_flip = Value;
        camera_settings.write_enable = 0xff;

        gpControllerSocket->sendData(camera_settings);

    }
}

void CameraSettingsWindow::powerFrequencySliderChanged(int Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.power_frequency = Value;
        camera_settings.write_enable = 0xff;
        camera_settings_ui->frequency_value->setText(QString::number(Value));

        gpControllerSocket->sendData(camera_settings);
    }


}

void CameraSettingsWindow::sharpnessSliderChanged(int Value)
{
    CAMERA_SETTINGS_FORMAT camera_settings;
    static bool initial_set = true;

    if(initial_set == true)
    {
        initial_set = false;
    }
    else
    {
        camera_settings = getOldSettings();
        camera_settings.sharpness = Value;
        camera_settings.write_enable = 0xff;
        camera_settings_ui->sharpness_value->setText(QString::number(Value));

        gpControllerSocket->sendData(camera_settings);
    }
}

void CameraSettingsWindow::zoomSliderChanged(int Value)
{
    std::cout << Value << std::endl;
    camera_settings_ui->zoom_value->setText(QString::number(Value));
}

void CameraSettingsWindow::attachtoMainWindow()
{

    connect(camera_settings_ui->buttonBox, SIGNAL(accepted()), this, SLOT(cameraSettingsAccepted()));

    connect(camera_settings_ui->brightness_slider, SIGNAL(valueChanged(int)), this, SLOT(brighnessSliderChanged(int)));
    connect(camera_settings_ui->contrast_slider, SIGNAL(valueChanged(int)), this, SLOT(contrastSliderChanged(int)));
    connect(camera_settings_ui->saturation_slider, SIGNAL(valueChanged(int)), this, SLOT(saturationSliderChanged(int)));
    connect(camera_settings_ui->hue_slider, SIGNAL(valueChanged(int)), this, SLOT(hueSliderChanged(int)));

    connect(camera_settings_ui->exposure_slider, SIGNAL(valueChanged(int)), this, SLOT(exposureSliderChanged(int)));
    connect(camera_settings_ui->auto_exposure_enable, SIGNAL(toggled(bool)), this, SLOT(autoExposureTriggered(bool)));

    connect(camera_settings_ui->gain_slider, SIGNAL(valueChanged(int)), this, SLOT(gainSliderChanged(int)));
    connect(camera_settings_ui->auto_gain_enable, SIGNAL(toggled(bool)), this, SLOT(autoGainTriggered(bool)));

    connect(camera_settings_ui->horizontal_flip_enable, SIGNAL(toggled(bool)), this, SLOT(horizontalFlipTriggered(bool)));
    connect(camera_settings_ui->vertical_flip_enable, SIGNAL(toggled(bool)), this, SLOT(verticalFlipTriggered(bool)));
    connect(camera_settings_ui->sharpness_slider, SIGNAL(valueChanged(int)), this, SLOT(sharpnessSliderChanged(int)));
    connect(camera_settings_ui->zoom_slider, SIGNAL(valueChanged(int)), this, SLOT(zoomSliderChanged(int)));

}

CAMERA_SETTINGS_FORMAT CameraSettingsWindow::getOldSettings()
{
    CAMERA_SETTINGS_FORMAT camera_settings;

    camera_settings.write_enable = 0xff;

    camera_settings.brighness = camera_settings_ui->brightness_slider->value();
    camera_settings.contrast = camera_settings_ui->contrast_slider->value();
    camera_settings.saturation = camera_settings_ui->saturation_slider->value();
    camera_settings.hue = camera_settings_ui->hue_slider->value();

    camera_settings.auto_gain = ((uint8_t)camera_settings_ui->auto_gain_enable->checkState()) ? 1:0;
    camera_settings.gain = camera_settings_ui->gain_slider->value();

    camera_settings.auto_exposure = ((uint8_t)camera_settings_ui->auto_exposure_enable->checkState()) ? 1:0;
    camera_settings.exposure = camera_settings_ui->exposure_slider->value();

    camera_settings.horizontal_flip = ((uint8_t)camera_settings_ui->horizontal_flip_enable->checkState()) ? 1:0;
    camera_settings.vertical_flip = ((uint8_t)camera_settings_ui->vertical_flip_enable->checkState()) ? 1:0;

    camera_settings.power_frequency = (uint8_t)camera_settings_ui->power_frequency_slider->value();
    camera_settings.sharpness = (uint8_t)camera_settings_ui->sharpness_slider->value();

    std::cout << "brighness: " << std::to_string(camera_settings.brighness) << std::endl;
    std::cout << "contrast: " << std::to_string(camera_settings.contrast) << std::endl;
    std::cout << "saturation: " << std::to_string(camera_settings.saturation) << std::endl;
    std::cout << "hue: " << std::to_string(camera_settings.hue) << std::endl;
    std::cout << "gain: " << std::to_string(camera_settings.gain) << std::endl;
    std::cout << "auto_gain: " << std::to_string(camera_settings.auto_gain) << std::endl;
    std::cout << "exposure: " << std::to_string(camera_settings.exposure) << std::endl;
    std::cout << "auto_exposure: " << std::to_string(camera_settings.auto_exposure) << std::endl;
    std::cout << std::endl;

    return camera_settings;
}


