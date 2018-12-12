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
        controller.cpp \
        datatypes.cpp \
        udpsocket.cpp \
        videostream.cpp \
    connectiondialog.cpp

HEADERS += \
        mainwindow.h \
        controller.h \
        datatypes.h \
        udpsocket.h \
        videostream.h \
    connectiondialog.h

FORMS += \
        mainwindow.ui \
    connectiondialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
