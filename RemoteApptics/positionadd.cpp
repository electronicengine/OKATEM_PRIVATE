#include "positionadd.h"
#include "ui_positionadd.h"

void PositionAdd::autoDiretionButtonToggled(bool Value)
{
    switch ((int)!Value) {
    case position:
        ui->stackedWidget->setCurrentIndex(position);
        break;
    case direction:
        ui->stackedWidget->setCurrentIndex(direction);
        break;
    default:
        break;
    }


}

PositionAdd::PositionAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PositionAdd)
{
    ui->setupUi(this);


    ui->stackedWidget->setCurrentIndex(position);

    connect(ui->auto_direction_button, SIGNAL(toggled(bool)), this, SLOT(autoDiretionButtonToggled(bool)));

}

PositionAdd::~PositionAdd()
{
    delete ui;
}
