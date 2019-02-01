#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include "mainwindow.h"

#define REJECTED    -1
#define ACCEPTED    1

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:


    Ui::ConnectionDialog *ui_local;
   explicit ConnectionDialog(QWidget *parent = nullptr);

    void attach(MainWindow *Window);

    ~ConnectionDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_comboBox_currentIndexChanged(const QString &arg1);

signals:
    void accepted(std::string, int, int);
    void rejected();

private:

    MainWindow *gpMainWindow;

};

#endif // CONNECTIONDIALOG_H
