#include "cameradriver.h"
#include "globals.h"

CameraDriver::CameraDriver()
{

}

CameraDriver::~CameraDriver()
{
    gmCameraControl.closeDevice();
}

int CameraDriver::init()
{
    int ret = gmCameraControl.openDevice(CAMERA);

    return ret;

}


int CameraDriver::setCameraControls(const CAMERA_SETTINGS_FORMAT &CameraSettings)
{


    if(CameraSettings.brighness != gmCameraSettings.brighness)
    {
        if(setBrightness(CameraSettings.brighness) == FAIL)
        {
            printAll("Camera Brighness can not be set!");
            return FAIL;
        }
    }

    if(CameraSettings.contrast != gmCameraSettings.contrast)
    {
        if(setContrast(CameraSettings.contrast) == FAIL)
        {
            printAll("Camera contrast can not be set!");
            return FAIL;
        }
    }

    if(CameraSettings.saturation != gmCameraSettings.saturation)
    {
        if(setSaturation(CameraSettings.saturation) == FAIL)
        {
            printAll("Camera saturation can not be set!");
            return FAIL;
        }
    }


    if(CameraSettings.hue != gmCameraSettings.hue)
    {
        if(setHue(CameraSettings.hue) == FAIL)
        {
            printAll("Camera hue can not be set!");
            return FAIL;
        }
    }


    if(CameraSettings.auto_exposure != gmCameraSettings.auto_exposure)
    {
        if(setAutoExposure(CameraSettings.auto_exposure) == FAIL)
        {
            printAll("Camera auto_exposure can not be set!");
            return FAIL;
        }
    }


    if(CameraSettings.exposure != gmCameraSettings.exposure)
    {
        if(setExposure(CameraSettings.exposure) == FAIL)
        {
            printAll("Camera exposure can not be set!");
            return FAIL;
        }
    }

    if(CameraSettings.auto_gain != gmCameraSettings.auto_gain)
    {
        if(setAutoGain(CameraSettings.auto_gain) == FAIL)
        {
            printAll("Camera auto_gain can not be set!");
            return FAIL;
        }
    }


    if(CameraSettings.gain != gmCameraSettings.gain)
    {
        if(setGain(CameraSettings.gain) == FAIL)
        {
            printAll("Camera gain can not be set!");
            return FAIL;
        }
    }

//    if(CameraSettings.horizontal_flip != gmCameraSettings.horizontal_flip)
//    {
//        if(setHorizontelFlip(CameraSettings.horizontal_flip) == FAIL)
//        {
//            printAll("Camera horizontal_flip can not be set!");
//            return FAIL;
//        }
//    }

//    if(CameraSettings.vertical_flip != gmCameraSettings.vertical_flip)
//    {
//        if(setVerticalFlip(CameraSettings.vertical_flip) == FAIL)
//        {
//            printAll("Camera vertical_flip can not be set!");
//            return FAIL;
//        }
//    }

    if(CameraSettings.sharpness != gmCameraSettings.sharpness)
    {
        if(setSharpness(CameraSettings.sharpness) == FAIL)
        {
            printAll("Camera sharpness can not be set!");
            return FAIL;
        }
    }

    return SUCCESS;


}

CAMERA_SETTINGS_FORMAT CameraDriver::getCameraControls()
{

    CAMERA_SETTINGS_FORMAT camera_settings;

    camera_settings.brighness = getBrightness();
    camera_settings.contrast = getContrast();
    camera_settings.saturation = getSaturation();
    camera_settings.hue = getHue();
    camera_settings.auto_exposure = getAutoExposure();
    camera_settings.exposure = getExposure();
    camera_settings.auto_gain = getAutoGain();
    camera_settings.gain = getAutoGain();
    camera_settings.horizontal_flip = getHorizontalFlip();
    camera_settings.vertical_flip = getVerticalFlip();
    camera_settings.sharpness = getSharpness();

    return camera_settings;

}

int CameraDriver::setBrightness(int Value)
{
    v4l2_control control;
    int ret;

    printAll("Brighness: ", std::to_string(Value));

    control.id = V4L2_CID_BRIGHTNESS;
    control.value = Value;

    ret = gmCameraControl.setControl(control);
    gmCameraSettings.brighness = Value;

    if(ret == FAIL)
        return FAIL;
    else
    {
        return SUCCESS;
    }

}

int CameraDriver::setContrast(int Value)
{
    v4l2_control control;
    int ret;

    printAll("contrast: ", std::to_string(Value));

    control.id = V4L2_CID_CONTRAST;
    control.value = Value;

    ret = gmCameraControl.setControl(control);
    gmCameraSettings.contrast = Value;

    if(ret == FAIL)
        return FAIL;
    else
    {
        return SUCCESS;
    }
}



int CameraDriver::setSaturation(int Value)
{
    v4l2_control control;
    int ret;

    printAll("saturation: ", std::to_string(Value));

    control.id = V4L2_CID_SATURATION;
    control.value = Value;

    ret = gmCameraControl.setControl(control);
    gmCameraSettings.saturation = Value;

    if(ret == FAIL)
        return FAIL;
    else
    {
        return SUCCESS;
    }
}



int CameraDriver::setHue(int Value)
{
    v4l2_control control;
    int ret;

    printAll("hue: ", std::to_string(Value));

    control.id = V4L2_CID_HUE;
    control.value = Value;

    ret = gmCameraControl.setControl(control);
    gmCameraSettings.hue = Value;

    if(ret == FAIL)
        return FAIL;
    else
    {
        return SUCCESS;
    }
}

int CameraDriver::setAutoExposure(bool Value)
{
    v4l2_control control;
    int ret;

    printAll("auto_exposure: ", std::to_string(Value));

    control.id = V4L2_CID_EXPOSURE_AUTO;
    control.value = Value ? 0:1;

    ret = gmCameraControl.setControl(control);
    gmCameraSettings.auto_exposure = (int)Value;

    if(ret == FAIL)
        return FAIL;
    else
        return SUCCESS;
}

int CameraDriver::setExposure(int Value)
{
    v4l2_control control;
    int ret;

    printAll("exposure: ", std::to_string(Value));

    control.id = V4L2_CID_EXPOSURE;
    control.value = Value;

    ret = gmCameraControl.setControl(control);
    gmCameraSettings.exposure = Value;

    if(ret == FAIL)
        return FAIL;
    else
    {
        return SUCCESS;
    }
}

int CameraDriver::setAutoGain(bool Value)
{
    v4l2_control control;
    int ret;

    printAll("auto_gain: ", std::to_string(Value));

//    control.id = V4L2_CID_AUTOGAIN;
//    control.value = Value;

//    ret = gmCameraControl.setControl(control);
    gmCameraSettings.auto_gain = Value;

    std::string cmd ="sudo v4l2-ctl --set-ctrl=gain_automatic=" + std::to_string(Value);

    system(cmd.c_str());

//    if(ret == FAIL)
//        return FAIL;
//    else
//    {
        return SUCCESS;
//    }
}

int CameraDriver::setGain(int Value)
{
    v4l2_control control;
    int ret;

    printAll("gain: ", std::to_string(Value));

    control.id = V4L2_CID_GAIN;
    control.value = Value;

    ret = gmCameraControl.setControl(control);
    gmCameraSettings.gain = Value;

    if(ret == FAIL)
        return FAIL;
    else
    {
        return SUCCESS;
    }
}

int CameraDriver::setHorizontelFlip(bool Value)
{
    v4l2_control control;
    int ret;

    printAll("horizontal_flip: ", std::to_string(Value));

    control.id = V4L2_CID_HFLIP;
    control.value = Value;

    ret = gmCameraControl.setControl(control);
    gmCameraSettings.horizontal_flip = Value;

    if(ret == FAIL)
        return FAIL;
    else
    {
        return SUCCESS;
    }
}

int CameraDriver::setVerticalFlip(bool Value)
{
    v4l2_control control;
    int ret;

    printAll("vertical_flip: ", std::to_string(Value));

    control.id = V4L2_CID_VFLIP;
    control.value = Value;

    ret = gmCameraControl.setControl(control);
    gmCameraSettings.vertical_flip = Value;

    if(ret == FAIL)
        return FAIL;
    else
    {
        return SUCCESS;
    }
}

int CameraDriver::setSharpness(int Value)
{
    v4l2_control control;
    int ret;

    printAll("sharpness: ", std::to_string(Value));


    control.id = V4L2_CID_SHARPNESS;
    control.value = Value;

    ret = gmCameraControl.setControl(control);
    gmCameraSettings.sharpness = Value;

    if(ret == FAIL)
        return FAIL;
    else
    {
        return SUCCESS;
    }
}

int CameraDriver::getBrightness()
{
    v4l2_control control;

    control.id = V4L2_CID_BRIGHTNESS;
    gmCameraSettings.brighness = gmCameraControl.getControl(control);

    return gmCameraSettings.brighness;

}

int CameraDriver::getContrast()
{
    v4l2_control control;

    control.id = V4L2_CID_CONTRAST;
    gmCameraSettings.contrast = gmCameraControl.getControl(control);

    return gmCameraSettings.contrast;
}

int CameraDriver::getSaturation()
{
    v4l2_control control;

    control.id = V4L2_CID_SATURATION;
    gmCameraSettings.saturation = gmCameraControl.getControl(control);

    return gmCameraSettings.saturation;
}

int CameraDriver::getHue()
{
    v4l2_control control;

    control.id = V4L2_CID_HUE;
    gmCameraSettings.hue = gmCameraControl.getControl(control);

    return gmCameraSettings.hue;
}

int CameraDriver::getAutoExposure()
{
    v4l2_control control;

    control.id = V4L2_CID_EXPOSURE_AUTO;
    gmCameraSettings.auto_exposure = gmCameraControl.getControl(control);

    return gmCameraSettings.auto_exposure ? 0:1;
}

int CameraDriver::getExposure()
{
    v4l2_control control;

    control.id = V4L2_CID_EXPOSURE;
    gmCameraSettings.exposure = gmCameraControl.getControl(control);

    return gmCameraSettings.exposure;
}

int CameraDriver::getAutoGain()
{
    v4l2_control control;

    control.id = V4L2_CID_AUTOGAIN;
    gmCameraSettings.auto_gain = gmCameraControl.getControl(control);

    return gmCameraSettings.auto_gain;
}

int CameraDriver::getGain()
{
    v4l2_control control;

    control.id = V4L2_CID_GAIN;
    gmCameraSettings.gain = gmCameraControl.getControl(control);

    return gmCameraSettings.gain;
}

int CameraDriver::getHorizontalFlip()
{
    v4l2_control control;

    control.id = V4L2_CID_HFLIP;
    gmCameraSettings.horizontal_flip = gmCameraControl.getControl(control);

    return gmCameraSettings.horizontal_flip;
}

int CameraDriver::getVerticalFlip()
{
    v4l2_control control;

    control.id = V4L2_CID_VFLIP;
    gmCameraSettings.vertical_flip = gmCameraControl.getControl(control);

    return gmCameraSettings.vertical_flip;
}

int CameraDriver::getSharpness()
{
    v4l2_control control;

    control.id = V4L2_CID_SHARPNESS;
    gmCameraSettings.sharpness = gmCameraControl.getControl(control);

    return gmCameraSettings.sharpness;
}

