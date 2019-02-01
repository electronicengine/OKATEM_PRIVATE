
#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui_local(new Ui::ConnectionDialog)
{
    ui_local->setupUi(this);

    ui_local->comboBox->addItem("Romeo");
    ui_local->comboBox->addItem("Juliet");
}

void ConnectionDialog::attach(MainWindow *Window)
{
    gpMainWindow = Window;
}


ConnectionDialog::~ConnectionDialog()
{
    delete ui_local;
}

void ConnectionDialog::on_buttonBox_accepted()
{

//    emit accepted(ui->ip_address_text->text().toStdString(), ui->stream_port_text->text().toInt(), ui->control_port_text->text().toInt());

//    this->hide();
}

void ConnectionDialog::on_buttonBox_rejected()
{
//    emit rejected();

//    this->hide();
}

void ConnectionDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Romeo")
    {
         ui_local->ip_address_text->setText("10.100.93.61");
         ui_local->stream_port_text->setText("26000");
         ui_local->control_port_text->setText("24000");
    }
    else if(arg1 == "Juliet")
    {
         ui_local->ip_address_text->setText("10.100.93.62");
         ui_local->stream_port_text->setText("27000");
         ui_local->control_port_text->setText("25000");

    }
}
