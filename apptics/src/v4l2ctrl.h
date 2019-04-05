#ifndef V4L2CTRL_H
#define V4L2CTRL_H

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

class v4l2ctrl
{

public:
    v4l2ctrl();

    int openDevice(const std::string Device);
    int setControl(v4l2_control Control);
    int getControl(v4l2_control Control);
    int closeDevice();

private:

    int gmFileDescriptor = -1;

    int isControl(int ControlType, struct v4l2_queryctrl* queryctrl);

};

#endif // V4L2CTRL_H
