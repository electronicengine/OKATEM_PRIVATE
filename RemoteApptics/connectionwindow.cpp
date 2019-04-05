#include "ui_connectionwindow.h"
#include "connectionwindow.h"

#include "QMessageBox"
#include "connectionpanel.h"



ConnectionWindow::ConnectionWindow(ConnectionWindow *Window) : MainWindow(true)
{

    ui = Window->ui;
    connection_ui = Window->connection_ui;

    gpControlWindow = Window->gpControlWindow;
    gpDisplaypanel = Window->gpDisplaypanel;
    gpCameraPanel = Window->gpCameraPanel;

    gpEnvironmentInfo = Window->gpEnvironmentInfo;
    gpControlInfo = Window->gpControlInfo;
    gpSfpInfo = Window->gpSfpInfo;

    gpIpAddress = Window->gpIpAddress;
    gpStreamPort = Window->gpStreamPort;
    gpControlPort = Window->gpControlPort;

    gpConnectionAvailable = Window->gpConnectionAvailable;
    gpMainWindow = Window->gpMainWindow;

}


void ConnectionWindow::rejected()
{
    gpConnectionWindow->hide();

}

void ConnectionWindow::comboBoxIndexChanged(int Index)
{
    gpConnectionPanel->deployPanel(Index);
}



ConnectionWindow::ConnectionWindow(MainWindow *Window) :
    MainWindow(Window), connection_ui(new Ui::ConnectionWindow)
{

    connection_ui->setupUi(this);

    gpConnectionPanel = new ConnectionPanel(this);

    connect(connection_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(connection_ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
    connect(connection_ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxIndexChanged(int)));


}


void ConnectionWindow::closed()
{
    gpConnectionWindow->hide();
}


ConnectionWindow::~ConnectionWindow()
{
    delete gpConnectionPanel;
    delete connection_ui;

}

void ConnectionWindow::accepted()
{
    gpConnectionPanel->startConnection();
}
