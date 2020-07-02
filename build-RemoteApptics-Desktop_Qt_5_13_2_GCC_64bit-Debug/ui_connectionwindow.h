/********************************************************************************
** Form generated from reading UI file 'connectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONWINDOW_H
#define UI_CONNECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectionWindow
{
public:
    QLineEdit *ip_address_text;
    QLineEdit *stream_port_text;
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QLabel *label_3;
    QLineEdit *control_port_text;

    void setupUi(QWidget *ConnectionWindow)
    {
        if (ConnectionWindow->objectName().isEmpty())
            ConnectionWindow->setObjectName(QString::fromUtf8("ConnectionWindow"));
        ConnectionWindow->resize(186, 258);
        ConnectionWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color:rgb(114, 159, 207);\n"
""));
        ip_address_text = new QLineEdit(ConnectionWindow);
        ip_address_text->setObjectName(QString::fromUtf8("ip_address_text"));
        ip_address_text->setGeometry(QRect(40, 70, 113, 27));
        ip_address_text->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        stream_port_text = new QLineEdit(ConnectionWindow);
        stream_port_text->setObjectName(QString::fromUtf8("stream_port_text"));
        stream_port_text->setGeometry(QRect(40, 120, 113, 27));
        stream_port_text->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        buttonBox = new QDialogButtonBox(ConnectionWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 210, 166, 27));
        buttonBox->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);\n"
"background-color: rgb(46, 52, 54);"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(ConnectionWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 50, 81, 19));
        label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_2 = new QLabel(ConnectionWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 100, 91, 19));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        comboBox = new QComboBox(ConnectionWindow);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(60, 10, 79, 27));
        comboBox->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        comboBox->setEditable(false);
        label_3 = new QLabel(ConnectionWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 150, 91, 19));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        control_port_text = new QLineEdit(ConnectionWindow);
        control_port_text->setObjectName(QString::fromUtf8("control_port_text"));
        control_port_text->setGeometry(QRect(40, 170, 113, 27));
        control_port_text->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));

        retranslateUi(ConnectionWindow);

        comboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(ConnectionWindow);
    } // setupUi

    void retranslateUi(QWidget *ConnectionWindow)
    {
        ConnectionWindow->setWindowTitle(QCoreApplication::translate("ConnectionWindow", "Connection", nullptr));
        label->setText(QCoreApplication::translate("ConnectionWindow", "Ip Address", nullptr));
        label_2->setText(QCoreApplication::translate("ConnectionWindow", "Stream Port", nullptr));
        comboBox->setCurrentText(QString());
        label_3->setText(QCoreApplication::translate("ConnectionWindow", "Control Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectionWindow: public Ui_ConnectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONWINDOW_H
