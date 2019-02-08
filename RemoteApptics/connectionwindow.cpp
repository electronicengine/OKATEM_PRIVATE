#include "ui_connectionwindow.h"
#include "connectionwindow.h"


#include "connectionpanel.h"



ConnectionWindow::ConnectionWindow(ConnectionWindow *Window) : MainWindow(true)
{

    ui = Window->ui;
    connection_ui = Window->connection_ui;

    gpControlPanel = Window->gpControlPanel;
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



ConnectionWindow::ConnectionWindow(MainWindow *Window) :
    MainWindow(Window), connection_ui(new Ui::ConnectionWindow)
{

    connection_ui->setupUi(this);

    ui = Window->ui;

    gpControlPanel = Window->gpControlPanel;
    gpDisplaypanel = Window->gpDisplaypanel;
    gpCameraPanel = Window->gpCameraPanel;

    gpEnvironmentInfo = Window->gpEnvironmentInfo;
    gpControlInfo = Window->gpControlInfo;
    gpSfpInfo = Window->gpSfpInfo;

    gpIpAddress = &Window->gmIpAddress;
    gpStreamPort = &Window->gmStreamPort;
    gpControlPort = &Window->gmControlPort;

    gpConnectionAvailable = &Window->gmConnectionAvailable;


    gpConnectionPanel = new ConnectionPanel(this);


    connect(this, SIGNAL(hideConnectionWindow()), (ConnectionWindow*)this, SLOT(ConnectionWindow::hide()));


}



ConnectionWindow::~ConnectionWindow()
{
    delete connection_ui;
}
