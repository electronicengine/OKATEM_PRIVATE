/********************************************************************************
** Form generated from reading UI file 'calibrationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONWINDOW_H
#define UI_CALIBRATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationWindow
{
public:
    QLabel *label_11;
    QDialogButtonBox *buttonBox;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_12;
    QLabel *label_2;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *step1_max_step;
    QLineEdit *step1_current_step;
    QLineEdit *step2_current_step;
    QLineEdit *step2_max_step;
    QLineEdit *servo1_top_degree;
    QLineEdit *servo1_bottom_degree;
    QLineEdit *servo2_bottom_degree;
    QLineEdit *servo2_top_degree;
    QLineEdit *servo1_current_degree;
    QLabel *label_13;
    QLineEdit *servo2_current_degree;
    QLabel *label_15;

    void setupUi(QWidget *CalibrationWindow)
    {
        if (CalibrationWindow->objectName().isEmpty())
            CalibrationWindow->setObjectName(QString::fromUtf8("CalibrationWindow"));
        CalibrationWindow->resize(334, 413);
        CalibrationWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color: rgb(114, 159, 207);"));
        label_11 = new QLabel(CalibrationWindow);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(200, 270, 111, 19));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        buttonBox = new QDialogButtonBox(CalibrationWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(-40, 350, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_3 = new QLabel(CalibrationWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 80, 91, 19));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label = new QLabel(CalibrationWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 10, 81, 19));
        label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_4 = new QLabel(CalibrationWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(200, 80, 101, 19));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_12 = new QLabel(CalibrationWindow);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(50, 270, 101, 19));
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_2 = new QLabel(CalibrationWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(200, 10, 131, 19));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_9 = new QLabel(CalibrationWindow);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(50, 200, 101, 19));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_10 = new QLabel(CalibrationWindow);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(200, 200, 121, 19));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        step1_max_step = new QLineEdit(CalibrationWindow);
        step1_max_step->setObjectName(QString::fromUtf8("step1_max_step"));
        step1_max_step->setGeometry(QRect(30, 40, 113, 27));
        step1_max_step->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        step1_current_step = new QLineEdit(CalibrationWindow);
        step1_current_step->setObjectName(QString::fromUtf8("step1_current_step"));
        step1_current_step->setGeometry(QRect(190, 40, 113, 27));
        step1_current_step->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        step2_current_step = new QLineEdit(CalibrationWindow);
        step2_current_step->setObjectName(QString::fromUtf8("step2_current_step"));
        step2_current_step->setGeometry(QRect(190, 110, 113, 27));
        step2_current_step->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        step2_max_step = new QLineEdit(CalibrationWindow);
        step2_max_step->setObjectName(QString::fromUtf8("step2_max_step"));
        step2_max_step->setGeometry(QRect(30, 110, 113, 27));
        step2_max_step->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        servo1_top_degree = new QLineEdit(CalibrationWindow);
        servo1_top_degree->setObjectName(QString::fromUtf8("servo1_top_degree"));
        servo1_top_degree->setGeometry(QRect(30, 230, 113, 27));
        servo1_top_degree->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        servo1_bottom_degree = new QLineEdit(CalibrationWindow);
        servo1_bottom_degree->setObjectName(QString::fromUtf8("servo1_bottom_degree"));
        servo1_bottom_degree->setGeometry(QRect(190, 230, 113, 27));
        servo1_bottom_degree->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        servo2_bottom_degree = new QLineEdit(CalibrationWindow);
        servo2_bottom_degree->setObjectName(QString::fromUtf8("servo2_bottom_degree"));
        servo2_bottom_degree->setGeometry(QRect(190, 300, 113, 27));
        servo2_bottom_degree->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        servo2_top_degree = new QLineEdit(CalibrationWindow);
        servo2_top_degree->setObjectName(QString::fromUtf8("servo2_top_degree"));
        servo2_top_degree->setGeometry(QRect(30, 300, 113, 27));
        servo2_top_degree->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        servo1_current_degree = new QLineEdit(CalibrationWindow);
        servo1_current_degree->setObjectName(QString::fromUtf8("servo1_current_degree"));
        servo1_current_degree->setGeometry(QRect(30, 170, 113, 27));
        servo1_current_degree->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_13 = new QLabel(CalibrationWindow);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(40, 140, 111, 20));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        servo2_current_degree = new QLineEdit(CalibrationWindow);
        servo2_current_degree->setObjectName(QString::fromUtf8("servo2_current_degree"));
        servo2_current_degree->setGeometry(QRect(190, 170, 113, 27));
        servo2_current_degree->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_15 = new QLabel(CalibrationWindow);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(200, 140, 111, 20));
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));

        retranslateUi(CalibrationWindow);

        QMetaObject::connectSlotsByName(CalibrationWindow);
    } // setupUi

    void retranslateUi(QWidget *CalibrationWindow)
    {
        CalibrationWindow->setWindowTitle(QCoreApplication::translate("CalibrationWindow", "Calibration", nullptr));
        label_11->setText(QCoreApplication::translate("CalibrationWindow", "Servo2 Bottom", nullptr));
        label_3->setText(QCoreApplication::translate("CalibrationWindow", "Step 2 Max", nullptr));
        label->setText(QCoreApplication::translate("CalibrationWindow", "Step 1 Max", nullptr));
        label_4->setText(QCoreApplication::translate("CalibrationWindow", "Step 2 Current", nullptr));
        label_12->setText(QCoreApplication::translate("CalibrationWindow", "Servo2 Top ", nullptr));
        label_2->setText(QCoreApplication::translate("CalibrationWindow", "Step 1 Current", nullptr));
        label_9->setText(QCoreApplication::translate("CalibrationWindow", "Servo1 Top", nullptr));
        label_10->setText(QCoreApplication::translate("CalibrationWindow", "Servo1 Bottom", nullptr));
        label_13->setText(QCoreApplication::translate("CalibrationWindow", "Servo1 Current", nullptr));
        label_15->setText(QCoreApplication::translate("CalibrationWindow", "Servo2 Current", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalibrationWindow: public Ui_CalibrationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONWINDOW_H
