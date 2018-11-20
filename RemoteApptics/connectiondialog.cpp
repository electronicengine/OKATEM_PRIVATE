#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_buttonBox_accepted()
{

    emit accepted(ui->ip_address_text->text().toStdString(), ui->port_number_text->text().toInt());

    this->hide();
}

void ConnectionDialog::on_buttonBox_rejected()
{
    emit rejected();

    this->hide();
}
