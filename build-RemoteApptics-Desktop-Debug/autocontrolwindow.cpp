#include "autocontrolwindow.h"
#include "ui_autocontrolwindow.h"

AutoControlWindow::AutoControlWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoControlWindow)
{
    ui->setupUi(this);
}

AutoControlWindow::~AutoControlWindow()
{
    delete ui;
}
