/********************************************************************************
** Form generated from reading UI file 'camerasettingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASETTINGSWINDOW_H
#define UI_CAMERASETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraSettingsWindow
{
public:
    QSlider *brightness_slider;
    QSlider *contrast_slider;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSlider *gain_slider;
    QLabel *label_7;
    QSlider *exposure_slider;
    QCheckBox *auto_gain_enable;
    QCheckBox *auto_exposure_enable;
    QLabel *label_8;
    QLabel *label_9;
    QSlider *zoom_slider;
    QLabel *label_10;
    QLabel *label_11;
    QSlider *hue_slider;
    QLabel *label_12;
    QSlider *saturation_slider;
    QLabel *label_13;
    QSlider *power_frequency_slider;
    QLabel *label_14;
    QSlider *sharpness_slider;
    QCheckBox *horizontal_flip_enable;
    QCheckBox *vertical_flip_enable;
    QLabel *contrast_value;
    QLabel *saturation_value;
    QLabel *hue_value;
    QLabel *exposure_value;
    QLabel *brignes_value;
    QLabel *gain_value;
    QLabel *frequency_value;
    QLabel *sharpness_value;
    QLabel *zoom_value;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *CameraSettingsWindow)
    {
        if (CameraSettingsWindow->objectName().isEmpty())
            CameraSettingsWindow->setObjectName(QString::fromUtf8("CameraSettingsWindow"));
        CameraSettingsWindow->resize(341, 492);
        CameraSettingsWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color: rgb(114, 159, 207);\n"
""));
        brightness_slider = new QSlider(CameraSettingsWindow);
        brightness_slider->setObjectName(QString::fromUtf8("brightness_slider"));
        brightness_slider->setGeometry(QRect(30, 50, 251, 16));
        brightness_slider->setMinimum(0);
        brightness_slider->setMaximum(255);
        brightness_slider->setOrientation(Qt::Horizontal);
        contrast_slider = new QSlider(CameraSettingsWindow);
        contrast_slider->setObjectName(QString::fromUtf8("contrast_slider"));
        contrast_slider->setGeometry(QRect(30, 90, 251, 16));
        contrast_slider->setMinimum(0);
        contrast_slider->setMaximum(255);
        contrast_slider->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(CameraSettingsWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(110, 30, 81, 20));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(CameraSettingsWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(110, 70, 81, 20));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(CameraSettingsWindow);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(110, 230, 81, 20));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_6->setAlignment(Qt::AlignCenter);
        gain_slider = new QSlider(CameraSettingsWindow);
        gain_slider->setObjectName(QString::fromUtf8("gain_slider"));
        gain_slider->setGeometry(QRect(30, 250, 251, 16));
        gain_slider->setMinimum(0);
        gain_slider->setMaximum(63);
        gain_slider->setOrientation(Qt::Horizontal);
        label_7 = new QLabel(CameraSettingsWindow);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(110, 190, 81, 20));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_7->setAlignment(Qt::AlignCenter);
        exposure_slider = new QSlider(CameraSettingsWindow);
        exposure_slider->setObjectName(QString::fromUtf8("exposure_slider"));
        exposure_slider->setGeometry(QRect(30, 210, 251, 16));
        exposure_slider->setMinimum(0);
        exposure_slider->setMaximum(255);
        exposure_slider->setOrientation(Qt::Horizontal);
        auto_gain_enable = new QCheckBox(CameraSettingsWindow);
        auto_gain_enable->setObjectName(QString::fromUtf8("auto_gain_enable"));
        auto_gain_enable->setGeometry(QRect(310, 250, 21, 25));
        auto_exposure_enable = new QCheckBox(CameraSettingsWindow);
        auto_exposure_enable->setObjectName(QString::fromUtf8("auto_exposure_enable"));
        auto_exposure_enable->setGeometry(QRect(310, 210, 21, 25));
        label_8 = new QLabel(CameraSettingsWindow);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(300, 230, 31, 20));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(CameraSettingsWindow);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(300, 190, 31, 20));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_9->setAlignment(Qt::AlignCenter);
        zoom_slider = new QSlider(CameraSettingsWindow);
        zoom_slider->setObjectName(QString::fromUtf8("zoom_slider"));
        zoom_slider->setGeometry(QRect(30, 370, 251, 16));
        zoom_slider->setMinimum(0);
        zoom_slider->setMaximum(10);
        zoom_slider->setOrientation(Qt::Horizontal);
        label_10 = new QLabel(CameraSettingsWindow);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(110, 350, 81, 20));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_10->setAlignment(Qt::AlignCenter);
        label_11 = new QLabel(CameraSettingsWindow);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(110, 150, 81, 20));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_11->setAlignment(Qt::AlignCenter);
        hue_slider = new QSlider(CameraSettingsWindow);
        hue_slider->setObjectName(QString::fromUtf8("hue_slider"));
        hue_slider->setGeometry(QRect(30, 170, 251, 16));
        hue_slider->setMinimum(-90);
        hue_slider->setMaximum(90);
        hue_slider->setOrientation(Qt::Horizontal);
        label_12 = new QLabel(CameraSettingsWindow);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(110, 110, 81, 20));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_12->setAlignment(Qt::AlignCenter);
        saturation_slider = new QSlider(CameraSettingsWindow);
        saturation_slider->setObjectName(QString::fromUtf8("saturation_slider"));
        saturation_slider->setGeometry(QRect(30, 130, 251, 16));
        saturation_slider->setMinimum(0);
        saturation_slider->setMaximum(255);
        saturation_slider->setOrientation(Qt::Horizontal);
        label_13 = new QLabel(CameraSettingsWindow);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(80, 270, 141, 20));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_13->setAlignment(Qt::AlignCenter);
        power_frequency_slider = new QSlider(CameraSettingsWindow);
        power_frequency_slider->setObjectName(QString::fromUtf8("power_frequency_slider"));
        power_frequency_slider->setGeometry(QRect(30, 290, 251, 16));
        power_frequency_slider->setMinimum(0);
        power_frequency_slider->setMaximum(1);
        power_frequency_slider->setOrientation(Qt::Horizontal);
        label_14 = new QLabel(CameraSettingsWindow);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(100, 310, 101, 20));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        label_14->setAlignment(Qt::AlignCenter);
        sharpness_slider = new QSlider(CameraSettingsWindow);
        sharpness_slider->setObjectName(QString::fromUtf8("sharpness_slider"));
        sharpness_slider->setGeometry(QRect(30, 330, 251, 16));
        sharpness_slider->setMinimum(0);
        sharpness_slider->setMaximum(255);
        sharpness_slider->setOrientation(Qt::Horizontal);
        horizontal_flip_enable = new QCheckBox(CameraSettingsWindow);
        horizontal_flip_enable->setObjectName(QString::fromUtf8("horizontal_flip_enable"));
        horizontal_flip_enable->setGeometry(QRect(30, 400, 121, 25));
        vertical_flip_enable = new QCheckBox(CameraSettingsWindow);
        vertical_flip_enable->setObjectName(QString::fromUtf8("vertical_flip_enable"));
        vertical_flip_enable->setGeometry(QRect(170, 400, 121, 25));
        contrast_value = new QLabel(CameraSettingsWindow);
        contrast_value->setObjectName(QString::fromUtf8("contrast_value"));
        contrast_value->setGeometry(QRect(0, 70, 31, 20));
        sizePolicy.setHeightForWidth(contrast_value->sizePolicy().hasHeightForWidth());
        contrast_value->setSizePolicy(sizePolicy);
        contrast_value->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        contrast_value->setAlignment(Qt::AlignCenter);
        saturation_value = new QLabel(CameraSettingsWindow);
        saturation_value->setObjectName(QString::fromUtf8("saturation_value"));
        saturation_value->setGeometry(QRect(0, 110, 31, 20));
        sizePolicy.setHeightForWidth(saturation_value->sizePolicy().hasHeightForWidth());
        saturation_value->setSizePolicy(sizePolicy);
        saturation_value->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        saturation_value->setAlignment(Qt::AlignCenter);
        hue_value = new QLabel(CameraSettingsWindow);
        hue_value->setObjectName(QString::fromUtf8("hue_value"));
        hue_value->setGeometry(QRect(0, 150, 31, 20));
        sizePolicy.setHeightForWidth(hue_value->sizePolicy().hasHeightForWidth());
        hue_value->setSizePolicy(sizePolicy);
        hue_value->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        hue_value->setAlignment(Qt::AlignCenter);
        exposure_value = new QLabel(CameraSettingsWindow);
        exposure_value->setObjectName(QString::fromUtf8("exposure_value"));
        exposure_value->setGeometry(QRect(0, 190, 31, 20));
        sizePolicy.setHeightForWidth(exposure_value->sizePolicy().hasHeightForWidth());
        exposure_value->setSizePolicy(sizePolicy);
        exposure_value->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        exposure_value->setAlignment(Qt::AlignCenter);
        brignes_value = new QLabel(CameraSettingsWindow);
        brignes_value->setObjectName(QString::fromUtf8("brignes_value"));
        brignes_value->setGeometry(QRect(0, 30, 31, 20));
        sizePolicy.setHeightForWidth(brignes_value->sizePolicy().hasHeightForWidth());
        brignes_value->setSizePolicy(sizePolicy);
        brignes_value->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        brignes_value->setAlignment(Qt::AlignCenter);
        gain_value = new QLabel(CameraSettingsWindow);
        gain_value->setObjectName(QString::fromUtf8("gain_value"));
        gain_value->setGeometry(QRect(0, 230, 31, 20));
        sizePolicy.setHeightForWidth(gain_value->sizePolicy().hasHeightForWidth());
        gain_value->setSizePolicy(sizePolicy);
        gain_value->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        gain_value->setAlignment(Qt::AlignCenter);
        frequency_value = new QLabel(CameraSettingsWindow);
        frequency_value->setObjectName(QString::fromUtf8("frequency_value"));
        frequency_value->setGeometry(QRect(0, 270, 31, 20));
        sizePolicy.setHeightForWidth(frequency_value->sizePolicy().hasHeightForWidth());
        frequency_value->setSizePolicy(sizePolicy);
        frequency_value->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        frequency_value->setAlignment(Qt::AlignCenter);
        sharpness_value = new QLabel(CameraSettingsWindow);
        sharpness_value->setObjectName(QString::fromUtf8("sharpness_value"));
        sharpness_value->setGeometry(QRect(0, 310, 31, 20));
        sizePolicy.setHeightForWidth(sharpness_value->sizePolicy().hasHeightForWidth());
        sharpness_value->setSizePolicy(sizePolicy);
        sharpness_value->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        sharpness_value->setAlignment(Qt::AlignCenter);
        zoom_value = new QLabel(CameraSettingsWindow);
        zoom_value->setObjectName(QString::fromUtf8("zoom_value"));
        zoom_value->setGeometry(QRect(0, 350, 31, 21));
        sizePolicy.setHeightForWidth(zoom_value->sizePolicy().hasHeightForWidth());
        zoom_value->setSizePolicy(sizePolicy);
        zoom_value->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: transparent;"));
        zoom_value->setAlignment(Qt::AlignCenter);
        buttonBox = new QDialogButtonBox(CameraSettingsWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setGeometry(QRect(120, 440, 81, 27));
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        retranslateUi(CameraSettingsWindow);

        QMetaObject::connectSlotsByName(CameraSettingsWindow);
    } // setupUi

    void retranslateUi(QWidget *CameraSettingsWindow)
    {
        CameraSettingsWindow->setWindowTitle(QCoreApplication::translate("CameraSettingsWindow", "Camera Settings", nullptr));
        label_4->setText(QCoreApplication::translate("CameraSettingsWindow", "Brightness", nullptr));
        label_5->setText(QCoreApplication::translate("CameraSettingsWindow", "Contrast", nullptr));
        label_6->setText(QCoreApplication::translate("CameraSettingsWindow", "Gain", nullptr));
        label_7->setText(QCoreApplication::translate("CameraSettingsWindow", "Exposure", nullptr));
        auto_gain_enable->setText(QString());
        auto_exposure_enable->setText(QString());
        label_8->setText(QCoreApplication::translate("CameraSettingsWindow", "Auto", nullptr));
        label_9->setText(QCoreApplication::translate("CameraSettingsWindow", "Auto", nullptr));
        label_10->setText(QCoreApplication::translate("CameraSettingsWindow", "Zoom", nullptr));
        label_11->setText(QCoreApplication::translate("CameraSettingsWindow", "Hue ", nullptr));
        label_12->setText(QCoreApplication::translate("CameraSettingsWindow", "Saturation", nullptr));
        label_13->setText(QCoreApplication::translate("CameraSettingsWindow", "Power Frequency", nullptr));
        label_14->setText(QCoreApplication::translate("CameraSettingsWindow", "Sharpness", nullptr));
        horizontal_flip_enable->setText(QCoreApplication::translate("CameraSettingsWindow", "Horizontel Flip", nullptr));
        vertical_flip_enable->setText(QCoreApplication::translate("CameraSettingsWindow", "Vertical Flip", nullptr));
        contrast_value->setText(QCoreApplication::translate("CameraSettingsWindow", "255", nullptr));
        saturation_value->setText(QCoreApplication::translate("CameraSettingsWindow", "255", nullptr));
        hue_value->setText(QCoreApplication::translate("CameraSettingsWindow", "255", nullptr));
        exposure_value->setText(QCoreApplication::translate("CameraSettingsWindow", "255", nullptr));
        brignes_value->setText(QCoreApplication::translate("CameraSettingsWindow", "255", nullptr));
        gain_value->setText(QCoreApplication::translate("CameraSettingsWindow", "255", nullptr));
        frequency_value->setText(QCoreApplication::translate("CameraSettingsWindow", "255", nullptr));
        sharpness_value->setText(QCoreApplication::translate("CameraSettingsWindow", "255", nullptr));
        zoom_value->setText(QCoreApplication::translate("CameraSettingsWindow", "255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraSettingsWindow: public Ui_CameraSettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASETTINGSWINDOW_H
