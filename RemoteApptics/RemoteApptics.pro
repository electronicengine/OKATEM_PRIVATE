#-------------------------------------------------
#
# Project created by QtCreator 2018-11-09T10:12:24
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = RemoteApptics
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -pthread -lopencv_imgproc \
    -lopencv_calib3d -lopencv_dnn -lopencv_features2d -lopencv_flann -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape \
    -lopencv_stitching -lopencv_superres -lopencv_videoio -lopencv_video -lopencv_videostab

CONFIG += c++17


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        datatypes.cpp \
        udpsocket.cpp \
        queue.cpp \
        ethernetsocket.cpp \
        videostream.cpp \
        remotecontroller.cpp \
        socketlistener.cpp \
    controlpanel.cpp \
    displaypanel.cpp \
    camerapanel.cpp \
    connectionpanel.cpp \
    connectionwindow.cpp \
    calibrationwindow.cpp \
    calibrationpanel.cpp \
    positionadd.cpp \
    autocontrolwindow.cpp \
    autocontrolpanel.cpp \
    command.cpp

HEADERS += \
        mainwindow.h \
        datatypes.h \
        udpsocket.h \
        ethernetsocket.h \
        queue.h \
        videostream.h \
        remotecontroller.h \
        socketlistener.h \
    controlpanel.h \
    displaypanel.h \
    camerapanel.h \
    connectionpanel.h \
    connectionwindow.h \
    calibrationwindow.h \
    calibrationpanel.h \
    positionadd.h \
    autocontrolwindow.h \
    autocontrolpanel.h \
    command.h

FORMS += \
        mainwindow.ui \
    connectionwindow.ui \
    calibrationwindow.ui \
    positionadd.ui \
    autocontrolwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES +=
