/********************************************************************************
** Form generated from reading UI file 'autocontrolwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOCONTROLWINDOW_H
#define UI_AUTOCONTROLWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoControlWindow
{
public:
    QPushButton *stop_button;
    QPushButton *start_button;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *add_button;
    QLabel *label_3;
    QPushButton *delete_button;
    QLabel *label_6;
    QListWidget *command_list;
    QLabel *label_7;
    QSpinBox *spinBox;
    QWidget *page_2;
    QLineEdit *position_y;
    QLabel *x_pos;
    QLabel *label_9;
    QLineEdit *position_x;
    QWidget *page_3;
    QLabel *label_5;
    QComboBox *comboBox;
    QLabel *label_2;
    QLabel *label_10;
    QLabel *label;

    void setupUi(QWidget *AutoControlWindow)
    {
        if (AutoControlWindow->objectName().isEmpty())
            AutoControlWindow->setObjectName(QString::fromUtf8("AutoControlWindow"));
        AutoControlWindow->resize(459, 359);
        AutoControlWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color: rgb(114, 159, 207);"));
        stop_button = new QPushButton(AutoControlWindow);
        stop_button->setObjectName(QString::fromUtf8("stop_button"));
        stop_button->setGeometry(QRect(40, 300, 41, 41));
        stop_button->setStyleSheet(QString::fromUtf8("#stop_button\n"
"{\n"
"border-image: url(:/images/stop_unpressed.png);\n"
"}\n"
"\n"
"#stop_button:pressed\n"
"{\n"
"border-image: url(:/images/stop_pressed.png);\n"
"}"));
        start_button = new QPushButton(AutoControlWindow);
        start_button->setObjectName(QString::fromUtf8("start_button"));
        start_button->setGeometry(QRect(360, 300, 41, 41));
        start_button->setStyleSheet(QString::fromUtf8("#start_button\n"
"{\n"
"border-image: url(:/images/start_unpressed.png);\n"
"}\n"
"\n"
"#start_button:pressed\n"
"{\n"
"border-image: url(:/images/start_pressed.png);\n"
"}"));
        stackedWidget = new QStackedWidget(AutoControlWindow);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 50, 441, 221));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        add_button = new QPushButton(page);
        add_button->setObjectName(QString::fromUtf8("add_button"));
        add_button->setGeometry(QRect(340, 40, 61, 61));
        add_button->setStyleSheet(QString::fromUtf8("#add_button\n"
"{\n"
"border-image: url(:/images/add_unpressed.png);\n"
"}\n"
"#add_button:pressed\n"
"{\n"
"border-image: url(:/images/add_pressed.png);\n"
"}\n"
""));
        label_3 = new QLabel(page);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(320, 100, 111, 19));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        delete_button = new QPushButton(page);
        delete_button->setObjectName(QString::fromUtf8("delete_button"));
        delete_button->setGeometry(QRect(350, 140, 41, 41));
        delete_button->setStyleSheet(QString::fromUtf8("#delete_button\n"
"{\n"
"border-image: url(:/images/delete_unpressed.png);\n"
"}\n"
"#delete_button:pressed\n"
"{\n"
"border-image: url(:/images/delete_pressed.png);\n"
"}\n"
""));
        label_6 = new QLabel(page);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(310, 190, 121, 19));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        command_list = new QListWidget(page);
        command_list->setObjectName(QString::fromUtf8("command_list"));
        command_list->setGeometry(QRect(30, 40, 256, 192));
        command_list->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: rgb(46, 52, 54);"));
        label_7 = new QLabel(page);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(170, 0, 51, 19));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        spinBox = new QSpinBox(page);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(230, 0, 49, 28));
        spinBox->setMinimum(1);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        position_y = new QLineEdit(page_2);
        position_y->setObjectName(QString::fromUtf8("position_y"));
        position_y->setGeometry(QRect(250, 120, 113, 27));
        position_y->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        x_pos = new QLabel(page_2);
        x_pos->setObjectName(QString::fromUtf8("x_pos"));
        x_pos->setGeometry(QRect(100, 100, 111, 20));
        x_pos->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        x_pos->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(page_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(250, 100, 111, 20));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_9->setAlignment(Qt::AlignCenter);
        position_x = new QLineEdit(page_2);
        position_x->setObjectName(QString::fromUtf8("position_x"));
        position_x->setGeometry(QRect(100, 120, 113, 27));
        position_x->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        label_5 = new QLabel(page_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(90, 40, 141, 19));
        stackedWidget->addWidget(page_3);
        comboBox = new QComboBox(AutoControlWindow);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(200, 10, 141, 27));
        comboBox->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        comboBox->setEditable(false);
        label_2 = new QLabel(AutoControlWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(320, 310, 31, 19));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_10 = new QLabel(AutoControlWindow);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(100, 10, 91, 20));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label = new QLabel(AutoControlWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 310, 41, 20));
        label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));

        retranslateUi(AutoControlWindow);

        stackedWidget->setCurrentIndex(1);
        comboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(AutoControlWindow);
    } // setupUi

    void retranslateUi(QWidget *AutoControlWindow)
    {
        AutoControlWindow->setWindowTitle(QCoreApplication::translate("AutoControlWindow", "AutoControl", nullptr));
        stop_button->setText(QString());
        start_button->setText(QString());
        add_button->setText(QString());
        label_3->setText(QCoreApplication::translate("AutoControlWindow", "Add Command", nullptr));
        delete_button->setText(QString());
        label_6->setText(QCoreApplication::translate("AutoControlWindow", "Delete Command", nullptr));
        label_7->setText(QCoreApplication::translate("AutoControlWindow", "Repeat", nullptr));
        position_y->setText(QString());
        x_pos->setText(QCoreApplication::translate("AutoControlWindow", "Lock Position X", nullptr));
        label_9->setText(QCoreApplication::translate("AutoControlWindow", "Lock Position Y", nullptr));
        position_x->setText(QString());
        label_5->setText(QCoreApplication::translate("AutoControlWindow", "Calibration Page", nullptr));
        comboBox->setCurrentText(QString());
        label_2->setText(QCoreApplication::translate("AutoControlWindow", "Start", nullptr));
        label_10->setText(QCoreApplication::translate("AutoControlWindow", "Select Mode:", nullptr));
        label->setText(QCoreApplication::translate("AutoControlWindow", "  Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoControlWindow: public Ui_AutoControlWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOCONTROLWINDOW_H
