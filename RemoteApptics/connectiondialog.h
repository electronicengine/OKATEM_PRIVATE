#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

#define REJECTED    -1
#define ACCEPTED    1

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:

     Ui::ConnectionDialog *ui;
    explicit ConnectionDialog(QWidget *parent = nullptr);

    ~ConnectionDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

signals:
    void accepted(std::string, int);
    void rejected();

private:

};

#endif // CONNECTIONDIALOG_H
