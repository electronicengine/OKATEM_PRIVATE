/********************************************************************************
** Form generated from reading UI file 'positionadd.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSITIONADD_H
#define UI_POSITIONADD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PositionAdd
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *auto_direction_button;
    QLabel *label_6;
    QStackedWidget *stackedWidget;
    QWidget *position;
    QLineEdit *x_position;
    QLineEdit *y_position;
    QLabel *label;
    QLabel *label_2;
    QWidget *direction;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *duration_command;
    QLineEdit *direction_command;

    void setupUi(QDialog *PositionAdd)
    {
        if (PositionAdd->objectName().isEmpty())
            PositionAdd->setObjectName(QString::fromUtf8("PositionAdd"));
        PositionAdd->resize(424, 135);
        PositionAdd->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color:rgb(114, 159, 207);\n"
""));
        buttonBox = new QDialogButtonBox(PositionAdd);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(60, 90, 341, 32));
        buttonBox->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color:rgb(114, 159, 207);\n"
""));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        auto_direction_button = new QPushButton(PositionAdd);
        auto_direction_button->setObjectName(QString::fromUtf8("auto_direction_button"));
        auto_direction_button->setGeometry(QRect(330, 20, 71, 31));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(auto_direction_button->sizePolicy().hasHeightForWidth());
        auto_direction_button->setSizePolicy(sizePolicy);
        auto_direction_button->setStyleSheet(QString::fromUtf8("#auto_direction_button\n"
"{\n"
"	border-image: url(:/images/toggle_button_off.png);\n"
"}\n"
"\n"
"#auto_direction_button:checked\n"
"{\n"
"border-image: url(:/images/toggle_button_on.png);\n"
"}"));
        auto_direction_button->setCheckable(true);
        auto_direction_button->setChecked(true);
        label_6 = new QLabel(PositionAdd);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(310, 60, 111, 20));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_6->setAlignment(Qt::AlignCenter);
        stackedWidget = new QStackedWidget(PositionAdd);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 10, 291, 80));
        position = new QWidget();
        position->setObjectName(QString::fromUtf8("position"));
        x_position = new QLineEdit(position);
        x_position->setObjectName(QString::fromUtf8("x_position"));
        x_position->setGeometry(QRect(20, 40, 113, 27));
        x_position->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        y_position = new QLineEdit(position);
        y_position->setObjectName(QString::fromUtf8("y_position"));
        y_position->setGeometry(QRect(170, 40, 113, 27));
        y_position->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label = new QLabel(position);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 111, 20));
        label->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(position);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 20, 111, 20));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_2->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(position);
        direction = new QWidget();
        direction->setObjectName(QString::fromUtf8("direction"));
        label_4 = new QLabel(direction);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 20, 111, 20));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_4->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(direction);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(170, 20, 111, 20));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        label_3->setAlignment(Qt::AlignCenter);
        duration_command = new QLineEdit(direction);
        duration_command->setObjectName(QString::fromUtf8("duration_command"));
        duration_command->setGeometry(QRect(170, 40, 113, 27));
        duration_command->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        direction_command = new QLineEdit(direction);
        direction_command->setObjectName(QString::fromUtf8("direction_command"));
        direction_command->setGeometry(QRect(20, 40, 113, 27));
        direction_command->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
        stackedWidget->addWidget(direction);

        retranslateUi(PositionAdd);
        QObject::connect(buttonBox, SIGNAL(accepted()), PositionAdd, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PositionAdd, SLOT(reject()));

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PositionAdd);
    } // setupUi

    void retranslateUi(QDialog *PositionAdd)
    {
        PositionAdd->setWindowTitle(QCoreApplication::translate("PositionAdd", "Command", nullptr));
        auto_direction_button->setText(QString());
        label_6->setText(QCoreApplication::translate("PositionAdd", "Auto Direction", nullptr));
        label->setText(QCoreApplication::translate("PositionAdd", "Step2 Position", nullptr));
        label_2->setText(QCoreApplication::translate("PositionAdd", "Step1 Position", nullptr));
        label_4->setText(QCoreApplication::translate("PositionAdd", "Direction", nullptr));
        label_3->setText(QCoreApplication::translate("PositionAdd", "Duration", nullptr));
        duration_command->setText(QString());
        direction_command->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PositionAdd: public Ui_PositionAdd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSITIONADD_H
