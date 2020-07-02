#include "v4l2ctrl.h"


v4l2ctrl::v4l2ctrl()
{

}

int v4l2ctrl::openDevice(const std::string Device)
{
    if (gmFileDescriptor != -1)
        return FAIL;

    gmFileDescriptor = ::open(Device.c_str(), O_RDWR);

    if(gmFileDescriptor < 0)
        return FAIL;
    else
        return SUCCESS;

}

int v4l2ctrl::setControl(v4l2_control Control)
{
    struct v4l2_queryctrl queryctrl;

    int min, max;
    int err;

    if (isControl(Control.id, &queryctrl) < 0)
        return FAIL;

    min = queryctrl.minimum;
    max = queryctrl.maximum;

    if ((Control.value >= min) && (Control.value <= max))
    {
        if ((err = ioctl(gmFileDescriptor, VIDIOC_S_CTRL, &Control)) < 0)
        {
              printf("ioctl set control error\n");
              return FAIL;
        }
    }

    return SUCCESS;
}

int v4l2ctrl::getControl(v4l2_control Control)
{
    struct v4l2_queryctrl queryctrl;

    int err;
    if (isControl(Control.id, &queryctrl) < 0)
        return FAIL;


    if ((err = ioctl(gmFileDescriptor, VIDIOC_G_CTRL, &Control)) < 0)
    {
            printf("ioctl get control error\n");
            return FAIL;

    }

    return Control.value;
}

int v4l2ctrl::closeDevice()
{
    if (gmFileDescriptor == -1)
          return SUCCESS;

    int rv = ::close(gmFileDescriptor);
    gmFileDescriptor = -1;

    if(rv != -1)
        return SUCCESS;
    else
        return FAIL;

}

int v4l2ctrl::isControl(int ControlType, v4l2_queryctrl *Queryctrl)
{
    int err = 0;
    Queryctrl->id = ControlType;
    if ((err = ioctl(gmFileDescriptor, VIDIOC_QUERYCTRL, Queryctrl)) < 0)
    {
        printf("ioctl querycontrol error %d \n", errno);
        return FAIL;
    }
    else if (Queryctrl->flags & V4L2_CTRL_FLAG_DISABLED)
    {
        printf("control %s disabled \n", (char*) Queryctrl->name);
        return 2;
    }
    else if (Queryctrl->flags & V4L2_CTRL_TYPE_BOOLEAN)
        return 1;
    else if (Queryctrl->type & V4L2_CTRL_TYPE_INTEGER)
        return 0;
    else
    {
        printf("contol %s unsupported  \n", (char*) Queryctrl->name);
        return FAIL;
    }
}
