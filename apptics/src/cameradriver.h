#ifndef CAMERADRIVER_H
#define CAMERADRIVER_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>

#include "datatypes.h"
#include "v4l2ctrl.h"

class CameraDriver
{
public:
    CameraDriver();
    ~CameraDriver();

    int init();


    int setCameraControls(CAMERA_SETTINGS_FORMAT& CameraSettings);

    CAMERA_SETTINGS_FORMAT getCameraControls();

private:

    CAMERA_SETTINGS_FORMAT gmCameraSettings;
    v4l2ctrl gmCameraControl;

    int setBrightness(int Value);
    int setContrast(int Value);
    int setSaturation(int Value);
    int setHue(int Value);
    int setAutoExposure(bool Value);
    int setExposure(int Value);
    int setAutoGain(bool Value);
    int setGain(int Value);
    int setHorizontelFlip(bool Value);
    int setVerticalFlip(bool Value);
    int setSharpness(int Value);

    int getBrightness();
    int getContrast();
    int getSaturation();
    int getHue();
    int getAutoExposure();
    int getExposure();
    int getAutoGain();
    int getGain();
    int getHorizontalFlip();
    int getVerticalFlip();
    int getSharpness();












};

#endif // CAMERACONTROLLER_H
