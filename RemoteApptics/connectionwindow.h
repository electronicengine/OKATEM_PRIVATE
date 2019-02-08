#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include "mainwindow.h"


class ConnectionPanel;

namespace Ui {
class ConnectionWindow;
}


class ConnectionWindow : public MainWindow
{
    Q_OBJECT

public:


    ConnectionWindow(ConnectionWindow *Window);
    ConnectionWindow(MainWindow *Window);
    ~ConnectionWindow();


    Ui::ConnectionWindow *connection_ui;



protected:


    enum connections
    {
        juliet,
        romeo

    }gmConnections;

    QStringList gmConnectionList = {"Juliet", "Romeo"};

    bool *gpConnectionAvailable;

    std::string *gpIpAddress;
    int *gpStreamPort;
    int *gpControlPort;

private:
    ConnectionPanel *gpConnectionPanel;


signals:
    void hideConnectionWindow();


};

#endif // CONNECTIONWINDOW_H
