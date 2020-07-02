/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnection;
    QAction *actionUpdate_Firmware;
    QAction *actionAuto_Control_Settings;
    QAction *actionCalibration_Settings;
    QAction *actionAutoControl_Settings;
    QAction *actionCamera_Settings;
    QWidget *centralWidget;
    QLabel *frame_label;
    QProgressBar *progressBar;
    QLabel *update_label;
    QWidget *gridLayoutWidget;
    QGridLayout *direction_layout;
    QPushButton *right_button;
    QPushButton *down_buttton;
    QPushButton *left_button;
    QPushButton *up_button;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *keep_press_layout;
    QPushButton *toggle_button;
    QLabel *label_25;
    QWidget *gridLayoutWidget_3;
    QGridLayout *sensor_layout;
    QLabel *label_12;
    QLabel *pressure_label;
    QLabel *label_22;
    QLabel *label_17;
    QLabel *label_11;
    QLabel *label_21;
    QLabel *compass_label;
    QLabel *label_23;
    QLabel *label_9;
    QLabel *nmea_label;
    QLabel *label_24;
    QLabel *temperature_label;
    QLabel *altitude_label;
    QLabel *label_10;
    QWidget *gridLayoutWidget_5;
    QGridLayout *servo_layout;
    QPushButton *increase1_button;
    QSlider *servo1_slider;
    QPushButton *increase2_button;
    QPushButton *decrease1_button;
    QSlider *servo2_slider;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *decrease2_button;
    QSlider *step1_speed_slider;
    QLabel *step2_speed_label;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout;
    QLabel *label_16;
    QLabel *servo2_pos_label;
    QLabel *label_7;
    QLabel *servo1_pos_label;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_19;
    QLabel *step2_pos_label;
    QLabel *label_20;
    QLabel *label_5;
    QLabel *label_18;
    QLabel *step1_pos_label;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_2;
    QLabel *tx_power_label;
    QLabel *label;
    QLabel *status_label;
    QLabel *label_8;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *rx_power_label;
    QLabel *label_15;
    QSlider *referance_scale_slider;
    QLabel *scale_label;
    QSlider *step2_speed_slider;
    QLabel *step1_speed_label;
    QLabel *connection_image_wifi;
    QLabel *connection_label;
    QLabel *connection_image_sfp;
    QMenuBar *menuBar;
    QMenu *menuas;
    QMenu *menuSettings;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(960, 1060);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color: rgb(114, 159, 207);\n"
"\n"
"Rectangle{\n"
"color:backgroundColor\n"
"GridLayout{backgroundColor: transparent;}\n"
"}"));
        actionConnection = new QAction(MainWindow);
        actionConnection->setObjectName(QString::fromUtf8("actionConnection"));
        actionUpdate_Firmware = new QAction(MainWindow);
        actionUpdate_Firmware->setObjectName(QString::fromUtf8("actionUpdate_Firmware"));
        actionAuto_Control_Settings = new QAction(MainWindow);
        actionAuto_Control_Settings->setObjectName(QString::fromUtf8("actionAuto_Control_Settings"));
        actionCalibration_Settings = new QAction(MainWindow);
        actionCalibration_Settings->setObjectName(QString::fromUtf8("actionCalibration_Settings"));
        actionAutoControl_Settings = new QAction(MainWindow);
        actionAutoControl_Settings->setObjectName(QString::fromUtf8("actionAutoControl_Settings"));
        actionCamera_Settings = new QAction(MainWindow);
        actionCamera_Settings->setObjectName(QString::fromUtf8("actionCamera_Settings"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frame_label = new QLabel(centralWidget);
        frame_label->setObjectName(QString::fromUtf8("frame_label"));
        frame_label->setEnabled(true);
        frame_label->setGeometry(QRect(0, 10, 960, 720));
        frame_label->setMouseTracking(true);
        frame_label->setTabletTracking(true);
        frame_label->setFrameShape(QFrame::Panel);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(330, 339, 321, 23));
        progressBar->setValue(0);
        update_label = new QLabel(centralWidget);
        update_label->setObjectName(QString::fromUtf8("update_label"));
        update_label->setGeometry(QRect(410, 319, 161, 19));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 800, 181, 181));
        direction_layout = new QGridLayout(gridLayoutWidget);
        direction_layout->setSpacing(8);
        direction_layout->setContentsMargins(11, 11, 11, 11);
        direction_layout->setObjectName(QString::fromUtf8("direction_layout"));
        direction_layout->setContentsMargins(0, 0, 0, 0);
        right_button = new QPushButton(gridLayoutWidget);
        right_button->setObjectName(QString::fromUtf8("right_button"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(right_button->sizePolicy().hasHeightForWidth());
        right_button->setSizePolicy(sizePolicy);
        right_button->setStyleSheet(QString::fromUtf8("#right_button\n"
"{\n"
"border-image: url(:/images/right_unpressed.png);\n"
"}\n"
"\n"
"#right_button:pressed\n"
"{\n"
"border-image: url(:/images/right_pressed.png);\n"
"}\n"
"#right_button:checked\n"
"{\n"
"border-image: url(:/images/right_pressed.png);\n"
"}"));

        direction_layout->addWidget(right_button, 1, 2, 1, 1);

        down_buttton = new QPushButton(gridLayoutWidget);
        down_buttton->setObjectName(QString::fromUtf8("down_buttton"));
        sizePolicy.setHeightForWidth(down_buttton->sizePolicy().hasHeightForWidth());
        down_buttton->setSizePolicy(sizePolicy);
        down_buttton->setStyleSheet(QString::fromUtf8("#down_buttton\n"
"{\n"
"border-image: url(:/images/down_unpressed.png);\n"
"}\n"
"\n"
"#down_buttton:pressed\n"
"{\n"
"border-image: url(:/images/down_pressed.png);\n"
"}\n"
"#down_buttton:checked\n"
"{\n"
"border-image: url(:/images/down_pressed.png);\n"
"}"));

        direction_layout->addWidget(down_buttton, 2, 1, 1, 1);

        left_button = new QPushButton(gridLayoutWidget);
        left_button->setObjectName(QString::fromUtf8("left_button"));
        sizePolicy.setHeightForWidth(left_button->sizePolicy().hasHeightForWidth());
        left_button->setSizePolicy(sizePolicy);
        left_button->setStyleSheet(QString::fromUtf8("#left_button\n"
"{\n"
"border-image: url(:/images/left_unpressed.png);\n"
"}\n"
"\n"
"#left_button:pressed\n"
"{\n"
"border-image: url(:/images/left_pressed.png);\n"
"}\n"
"#left_button:checked\n"
"{\n"
"border-image: url(:/images/left_pressed.png);\n"
"}"));
        left_button->setCheckable(false);
        left_button->setChecked(false);

        direction_layout->addWidget(left_button, 1, 0, 1, 1);

        up_button = new QPushButton(gridLayoutWidget);
        up_button->setObjectName(QString::fromUtf8("up_button"));
        sizePolicy.setHeightForWidth(up_button->sizePolicy().hasHeightForWidth());
        up_button->setSizePolicy(sizePolicy);
        up_button->setLayoutDirection(Qt::RightToLeft);
        up_button->setStyleSheet(QString::fromUtf8("#up_button\n"
"{\n"
"border-image: url(:/images/up_unpressed.png);\n"
"}\n"
"\n"
"#up_button:pressed\n"
"{\n"
"border-image: url(:/images/up_pressed.png);\n"
"}\n"
"\n"
"#up_button:checked\n"
"{\n"
"border-image: url(:/images/up_pressed.png);\n"
"}\n"
"\n"
"#up_button:checked\n"
"{\n"
"border-image: url(:/images/up_pressed.png);\n"
"}"));
        up_button->setCheckable(false);
        up_button->setChecked(false);

        direction_layout->addWidget(up_button, 0, 1, 1, 1);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 740, 61, 51));
        keep_press_layout = new QVBoxLayout(verticalLayoutWidget);
        keep_press_layout->setSpacing(6);
        keep_press_layout->setContentsMargins(11, 11, 11, 11);
        keep_press_layout->setObjectName(QString::fromUtf8("keep_press_layout"));
        keep_press_layout->setContentsMargins(0, 0, 0, 0);
        toggle_button = new QPushButton(verticalLayoutWidget);
        toggle_button->setObjectName(QString::fromUtf8("toggle_button"));
        sizePolicy.setHeightForWidth(toggle_button->sizePolicy().hasHeightForWidth());
        toggle_button->setSizePolicy(sizePolicy);
        toggle_button->setStyleSheet(QString::fromUtf8("#toggle_button\n"
"{\n"
"	border-image: url(:/images/toggle_button_off.png);\n"
"}\n"
"\n"
"#toggle_button:checked\n"
"{\n"
"border-image: url(:/images/toggle_button_on.png);\n"
"}"));
        toggle_button->setCheckable(true);
        toggle_button->setChecked(false);

        keep_press_layout->addWidget(toggle_button);

        label_25 = new QLabel(verticalLayoutWidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(7);
        label_25->setFont(font);
        label_25->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));

        keep_press_layout->addWidget(label_25);

        gridLayoutWidget_3 = new QWidget(centralWidget);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(640, 790, 301, 181));
        sensor_layout = new QGridLayout(gridLayoutWidget_3);
        sensor_layout->setSpacing(6);
        sensor_layout->setContentsMargins(11, 11, 11, 11);
        sensor_layout->setObjectName(QString::fromUtf8("sensor_layout"));
        sensor_layout->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(gridLayoutWidget_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));

        sensor_layout->addWidget(label_12, 3, 0, 1, 1);

        pressure_label = new QLabel(gridLayoutWidget_3);
        pressure_label->setObjectName(QString::fromUtf8("pressure_label"));
        pressure_label->setAutoFillBackground(false);
        pressure_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));
        pressure_label->setFrameShape(QFrame::Panel);
        pressure_label->setFrameShadow(QFrame::Plain);
        pressure_label->setAlignment(Qt::AlignCenter);

        sensor_layout->addWidget(pressure_label, 1, 1, 1, 1);

        label_22 = new QLabel(gridLayoutWidget_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));

        sensor_layout->addWidget(label_22, 1, 2, 1, 1);

        label_17 = new QLabel(gridLayoutWidget_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAcceptDrops(false);
        label_17->setLayoutDirection(Qt::LeftToRight);
        label_17->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_17->setAlignment(Qt::AlignCenter);

        sensor_layout->addWidget(label_17, 4, 0, 1, 3);

        label_11 = new QLabel(gridLayoutWidget_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));

        sensor_layout->addWidget(label_11, 2, 0, 1, 1);

        label_21 = new QLabel(gridLayoutWidget_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy2);
        label_21->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));

        sensor_layout->addWidget(label_21, 0, 2, 1, 1);

        compass_label = new QLabel(gridLayoutWidget_3);
        compass_label->setObjectName(QString::fromUtf8("compass_label"));
        compass_label->setAutoFillBackground(false);
        compass_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));
        compass_label->setFrameShape(QFrame::Panel);
        compass_label->setFrameShadow(QFrame::Plain);
        compass_label->setAlignment(Qt::AlignCenter);

        sensor_layout->addWidget(compass_label, 3, 1, 1, 1);

        label_23 = new QLabel(gridLayoutWidget_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));

        sensor_layout->addWidget(label_23, 2, 2, 1, 1);

        label_9 = new QLabel(gridLayoutWidget_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy2.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy2);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));

        sensor_layout->addWidget(label_9, 0, 0, 1, 1);

        nmea_label = new QLabel(gridLayoutWidget_3);
        nmea_label->setObjectName(QString::fromUtf8("nmea_label"));
        nmea_label->setAutoFillBackground(false);
        nmea_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        nmea_label->setFrameShape(QFrame::Panel);
        nmea_label->setFrameShadow(QFrame::Plain);
        nmea_label->setAlignment(Qt::AlignCenter);

        sensor_layout->addWidget(nmea_label, 5, 0, 1, 3);

        label_24 = new QLabel(gridLayoutWidget_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));

        sensor_layout->addWidget(label_24, 3, 2, 1, 1);

        temperature_label = new QLabel(gridLayoutWidget_3);
        temperature_label->setObjectName(QString::fromUtf8("temperature_label"));
        temperature_label->setAutoFillBackground(false);
        temperature_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));
        temperature_label->setFrameShape(QFrame::Panel);
        temperature_label->setFrameShadow(QFrame::Plain);
        temperature_label->setAlignment(Qt::AlignCenter);

        sensor_layout->addWidget(temperature_label, 0, 1, 1, 1);

        altitude_label = new QLabel(gridLayoutWidget_3);
        altitude_label->setObjectName(QString::fromUtf8("altitude_label"));
        altitude_label->setAutoFillBackground(false);
        altitude_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));
        altitude_label->setFrameShape(QFrame::Panel);
        altitude_label->setFrameShadow(QFrame::Plain);
        altitude_label->setAlignment(Qt::AlignCenter);

        sensor_layout->addWidget(altitude_label, 2, 1, 1, 1);

        label_10 = new QLabel(gridLayoutWidget_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));

        sensor_layout->addWidget(label_10, 1, 0, 1, 1);

        gridLayoutWidget_5 = new QWidget(centralWidget);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(240, 760, 41, 221));
        servo_layout = new QGridLayout(gridLayoutWidget_5);
        servo_layout->setSpacing(6);
        servo_layout->setContentsMargins(11, 11, 11, 11);
        servo_layout->setObjectName(QString::fromUtf8("servo_layout"));
        servo_layout->setContentsMargins(0, 0, 0, 0);
        increase1_button = new QPushButton(gridLayoutWidget_5);
        increase1_button->setObjectName(QString::fromUtf8("increase1_button"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(increase1_button->sizePolicy().hasHeightForWidth());
        increase1_button->setSizePolicy(sizePolicy3);
        increase1_button->setLayoutDirection(Qt::RightToLeft);
        increase1_button->setStyleSheet(QString::fromUtf8("#increase1_button\n"
"{\n"
"border-image: url(:/images/down_unpressed.png);\n"
"}\n"
"\n"
"#increase1_button:pressed\n"
"{\n"
"border-image: url(:/images/down_pressed.png);\n"
"}"));

        servo_layout->addWidget(increase1_button, 3, 0, 1, 1);

        servo1_slider = new QSlider(gridLayoutWidget_5);
        servo1_slider->setObjectName(QString::fromUtf8("servo1_slider"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(servo1_slider->sizePolicy().hasHeightForWidth());
        servo1_slider->setSizePolicy(sizePolicy4);
        servo1_slider->setMaximum(150);
        servo1_slider->setOrientation(Qt::Vertical);
        servo1_slider->setInvertedAppearance(true);
        servo1_slider->setInvertedControls(true);

        servo_layout->addWidget(servo1_slider, 2, 0, 1, 1);

        increase2_button = new QPushButton(gridLayoutWidget_5);
        increase2_button->setObjectName(QString::fromUtf8("increase2_button"));
        increase2_button->setLayoutDirection(Qt::RightToLeft);
        increase2_button->setStyleSheet(QString::fromUtf8("#increase2_button\n"
"{\n"
"border-image: url(:/images/down_unpressed.png);\n"
"}\n"
"\n"
"#increase2_button:pressed\n"
"{\n"
"border-image: url(:/images/down_pressed.png);\n"
"}"));

        servo_layout->addWidget(increase2_button, 3, 1, 1, 1);

        decrease1_button = new QPushButton(gridLayoutWidget_5);
        decrease1_button->setObjectName(QString::fromUtf8("decrease1_button"));
        sizePolicy3.setHeightForWidth(decrease1_button->sizePolicy().hasHeightForWidth());
        decrease1_button->setSizePolicy(sizePolicy3);
        decrease1_button->setLayoutDirection(Qt::RightToLeft);
        decrease1_button->setStyleSheet(QString::fromUtf8("#decrease1_button\n"
"{\n"
"border-image: url(:/images/up_unpressed.png);\n"
"}\n"
"\n"
"#decrease1_button:pressed\n"
"{\n"
"border-image: url(:/images/up_pressed.png);\n"
"}"));

        servo_layout->addWidget(decrease1_button, 1, 0, 1, 1);

        servo2_slider = new QSlider(gridLayoutWidget_5);
        servo2_slider->setObjectName(QString::fromUtf8("servo2_slider"));
        sizePolicy4.setHeightForWidth(servo2_slider->sizePolicy().hasHeightForWidth());
        servo2_slider->setSizePolicy(sizePolicy4);
        servo2_slider->setMaximum(150);
        servo2_slider->setOrientation(Qt::Vertical);
        servo2_slider->setInvertedAppearance(true);
        servo2_slider->setInvertedControls(true);

        servo_layout->addWidget(servo2_slider, 2, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));

        servo_layout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;\n"
""));

        servo_layout->addWidget(label_3, 0, 1, 1, 1);

        decrease2_button = new QPushButton(gridLayoutWidget_5);
        decrease2_button->setObjectName(QString::fromUtf8("decrease2_button"));
        decrease2_button->setLayoutDirection(Qt::RightToLeft);
        decrease2_button->setStyleSheet(QString::fromUtf8("#decrease2_button\n"
"{\n"
"border-image: url(:/images/up_unpressed.png);\n"
"}\n"
"\n"
"#decrease2_button:pressed\n"
"{\n"
"border-image: url(:/images/up_pressed.png);\n"
"}"));

        servo_layout->addWidget(decrease2_button, 1, 1, 1, 1);

        step1_speed_slider = new QSlider(centralWidget);
        step1_speed_slider->setObjectName(QString::fromUtf8("step1_speed_slider"));
        step1_speed_slider->setGeometry(QRect(500, 760, 131, 16));
        step1_speed_slider->setMaximum(60);
        step1_speed_slider->setValue(60);
        step1_speed_slider->setOrientation(Qt::Horizontal);
        step1_speed_slider->setInvertedAppearance(false);
        step1_speed_slider->setInvertedControls(false);
        step2_speed_label = new QLabel(centralWidget);
        step2_speed_label->setObjectName(QString::fromUtf8("step2_speed_label"));
        step2_speed_label->setGeometry(QRect(330, 740, 151, 19));
        step2_speed_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        step2_speed_label->setAlignment(Qt::AlignCenter);
        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(310, 790, 301, 100));
        gridLayout = new QGridLayout(gridLayoutWidget_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(gridLayoutWidget_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy2.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy2);
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout->addWidget(label_16, 0, 2, 1, 1);

        servo2_pos_label = new QLabel(gridLayoutWidget_2);
        servo2_pos_label->setObjectName(QString::fromUtf8("servo2_pos_label"));
        servo2_pos_label->setAutoFillBackground(false);
        servo2_pos_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        servo2_pos_label->setFrameShape(QFrame::Panel);
        servo2_pos_label->setFrameShadow(QFrame::Plain);
        servo2_pos_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo2_pos_label, 1, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        servo1_pos_label = new QLabel(gridLayoutWidget_2);
        servo1_pos_label->setObjectName(QString::fromUtf8("servo1_pos_label"));
        sizePolicy3.setHeightForWidth(servo1_pos_label->sizePolicy().hasHeightForWidth());
        servo1_pos_label->setSizePolicy(sizePolicy3);
        servo1_pos_label->setAutoFillBackground(false);
        servo1_pos_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        servo1_pos_label->setFrameShape(QFrame::Panel);
        servo1_pos_label->setFrameShadow(QFrame::Plain);
        servo1_pos_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo1_pos_label, 0, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        label_19 = new QLabel(gridLayoutWidget_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout->addWidget(label_19, 2, 2, 1, 1);

        step2_pos_label = new QLabel(gridLayoutWidget_2);
        step2_pos_label->setObjectName(QString::fromUtf8("step2_pos_label"));
        step2_pos_label->setAutoFillBackground(false);
        step2_pos_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        step2_pos_label->setFrameShape(QFrame::Panel);
        step2_pos_label->setFrameShadow(QFrame::Plain);
        step2_pos_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(step2_pos_label, 3, 1, 1, 1);

        label_20 = new QLabel(gridLayoutWidget_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout->addWidget(label_20, 3, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        label_18 = new QLabel(gridLayoutWidget_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout->addWidget(label_18, 1, 2, 1, 1);

        step1_pos_label = new QLabel(gridLayoutWidget_2);
        step1_pos_label->setObjectName(QString::fromUtf8("step1_pos_label"));
        step1_pos_label->setAutoFillBackground(false);
        step1_pos_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        step1_pos_label->setFrameShape(QFrame::Panel);
        step1_pos_label->setFrameShadow(QFrame::Plain);
        step1_pos_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(step1_pos_label, 2, 1, 1, 1);

        gridLayoutWidget_4 = new QWidget(centralWidget);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(310, 900, 301, 74));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tx_power_label = new QLabel(gridLayoutWidget_4);
        tx_power_label->setObjectName(QString::fromUtf8("tx_power_label"));
        tx_power_label->setAutoFillBackground(false);
        tx_power_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        tx_power_label->setFrameShape(QFrame::Panel);
        tx_power_label->setFrameShadow(QFrame::Plain);
        tx_power_label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(tx_power_label, 1, 1, 1, 1);

        label = new QLabel(gridLayoutWidget_4);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout_2->addWidget(label, 1, 2, 1, 1);

        status_label = new QLabel(gridLayoutWidget_4);
        status_label->setObjectName(QString::fromUtf8("status_label"));
        sizePolicy3.setHeightForWidth(status_label->sizePolicy().hasHeightForWidth());
        status_label->setSizePolicy(sizePolicy3);
        status_label->setAutoFillBackground(false);
        status_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        status_label->setFrameShape(QFrame::Panel);
        status_label->setFrameShadow(QFrame::Plain);
        status_label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(status_label, 0, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        label_13 = new QLabel(gridLayoutWidget_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy2.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy2);
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout_2->addWidget(label_13, 1, 0, 1, 1);

        label_14 = new QLabel(gridLayoutWidget_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout_2->addWidget(label_14, 2, 0, 1, 1);

        rx_power_label = new QLabel(gridLayoutWidget_4);
        rx_power_label->setObjectName(QString::fromUtf8("rx_power_label"));
        rx_power_label->setAutoFillBackground(false);
        rx_power_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        rx_power_label->setFrameShape(QFrame::Panel);
        rx_power_label->setFrameShadow(QFrame::Plain);
        rx_power_label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(rx_power_label, 2, 1, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));

        gridLayout_2->addWidget(label_15, 2, 2, 1, 1);

        referance_scale_slider = new QSlider(centralWidget);
        referance_scale_slider->setObjectName(QString::fromUtf8("referance_scale_slider"));
        referance_scale_slider->setGeometry(QRect(660, 760, 271, 16));
        referance_scale_slider->setMinimum(-40);
        referance_scale_slider->setMaximum(10);
        referance_scale_slider->setOrientation(Qt::Horizontal);
        scale_label = new QLabel(centralWidget);
        scale_label->setObjectName(QString::fromUtf8("scale_label"));
        scale_label->setGeometry(QRect(740, 740, 111, 19));
        scale_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        step2_speed_slider = new QSlider(centralWidget);
        step2_speed_slider->setObjectName(QString::fromUtf8("step2_speed_slider"));
        step2_speed_slider->setGeometry(QRect(340, 760, 131, 16));
        step2_speed_slider->setMaximum(60);
        step2_speed_slider->setValue(60);
        step2_speed_slider->setOrientation(Qt::Horizontal);
        step2_speed_slider->setInvertedAppearance(false);
        step2_speed_slider->setInvertedControls(false);
        step1_speed_label = new QLabel(centralWidget);
        step1_speed_label->setObjectName(QString::fromUtf8("step1_speed_label"));
        step1_speed_label->setGeometry(QRect(490, 740, 151, 19));
        step1_speed_label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        step1_speed_label->setAlignment(Qt::AlignCenter);
        connection_image_wifi = new QLabel(centralWidget);
        connection_image_wifi->setObjectName(QString::fromUtf8("connection_image_wifi"));
        connection_image_wifi->setGeometry(QRect(360, 20, 131, 121));
        connection_image_wifi->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        connection_image_wifi->setPixmap(QPixmap(QString::fromUtf8(":/images/wifi_locked.png")));
        connection_image_wifi->setScaledContents(true);
        connection_label = new QLabel(centralWidget);
        connection_label->setObjectName(QString::fromUtf8("connection_label"));
        connection_label->setGeometry(QRect(510, 50, 151, 71));
        connection_label->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        connection_label->setTextFormat(Qt::RichText);
        connection_label->setAlignment(Qt::AlignCenter);
        connection_image_sfp = new QLabel(centralWidget);
        connection_image_sfp->setObjectName(QString::fromUtf8("connection_image_sfp"));
        connection_image_sfp->setGeometry(QRect(360, 20, 131, 121));
        connection_image_sfp->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        connection_image_sfp->setPixmap(QPixmap(QString::fromUtf8(":/images/laser_locked.png")));
        connection_image_sfp->setScaledContents(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 24));
        menuBar->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        menuas = new QMenu(menuBar);
        menuas->setObjectName(QString::fromUtf8("menuas"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuas->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuas->addAction(actionConnection);
        menuas->addAction(actionUpdate_Firmware);
        menuSettings->addAction(actionCalibration_Settings);
        menuSettings->addAction(actionAutoControl_Settings);
        menuSettings->addAction(actionCamera_Settings);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "RemoteApptics", nullptr));
        actionConnection->setText(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        actionUpdate_Firmware->setText(QCoreApplication::translate("MainWindow", "Update Firmware", nullptr));
        actionAuto_Control_Settings->setText(QCoreApplication::translate("MainWindow", "Auto Control Settings", nullptr));
        actionCalibration_Settings->setText(QCoreApplication::translate("MainWindow", "Calibration Settings", nullptr));
        actionAutoControl_Settings->setText(QCoreApplication::translate("MainWindow", "AutoControl Settings", nullptr));
        actionCamera_Settings->setText(QCoreApplication::translate("MainWindow", "Camera Settings", nullptr));
        frame_label->setStyleSheet(QCoreApplication::translate("MainWindow", "color: rgb(114, 0, 0);\n"
"background-color: transparent;", nullptr));
        frame_label->setText(QString());
        update_label->setText(QCoreApplication::translate("MainWindow", "Firmware upgrading...", nullptr));
        right_button->setText(QString());
        down_buttton->setText(QString());
        left_button->setText(QString());
#if QT_CONFIG(shortcut)
        left_button->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        up_button->setText(QString());
#if QT_CONFIG(shortcut)
        up_button->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        toggle_button->setText(QString());
        label_25->setText(QCoreApplication::translate("MainWindow", " Keep Press", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Compass:", nullptr));
        pressure_label->setText(QString());
        label_22->setText(QCoreApplication::translate("MainWindow", "mhba", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "NMEA Output:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Altitude:", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        compass_label->setText(QString());
        label_23->setText(QCoreApplication::translate("MainWindow", "m", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Temperature:", nullptr));
        nmea_label->setText(QString());
        label_24->setText(QCoreApplication::translate("MainWindow", "Deg", nullptr));
        temperature_label->setText(QString());
        altitude_label->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "Pressure:", nullptr));
        increase1_button->setText(QString());
#if QT_CONFIG(shortcut)
        increase1_button->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        increase2_button->setText(QString());
#if QT_CONFIG(shortcut)
        increase2_button->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        decrease1_button->setText(QString());
#if QT_CONFIG(shortcut)
        decrease1_button->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        label_2->setText(QCoreApplication::translate("MainWindow", "S1", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "S2", nullptr));
        decrease2_button->setText(QString());
#if QT_CONFIG(shortcut)
        decrease2_button->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        step2_speed_label->setText(QCoreApplication::translate("MainWindow", "Left-Right Speed : 60", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Deg", nullptr));
        servo2_pos_label->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "Step Motor2 Pos:", nullptr));
        servo1_pos_label->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "Step Motor1 Pos:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Servo Motor1 Pos:", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Step", nullptr));
        step2_pos_label->setText(QString());
        label_20->setText(QCoreApplication::translate("MainWindow", "Step", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Servo Motor2 Pos:", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Deg", nullptr));
        step1_pos_label->setText(QString());
        tx_power_label->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "dbm", nullptr));
        status_label->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "Status:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "SFP Tx Power: ", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "SFP Rx Power: ", nullptr));
        rx_power_label->setText(QString());
        label_15->setText(QCoreApplication::translate("MainWindow", "dbm", nullptr));
        scale_label->setText(QCoreApplication::translate("MainWindow", "Target Scale: 0", nullptr));
        step1_speed_label->setText(QCoreApplication::translate("MainWindow", "Up-Down Speed : 60", nullptr));
        connection_image_wifi->setText(QString());
        connection_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
        connection_image_sfp->setText(QString());
        menuas->setTitle(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
