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



public slots:
    void accepted();
    void rejected();
    void comboBoxIndexChanged(int);
    void closed();


protected:


    enum connections
    {
        juliet,
        romeo

    }gmConnections;

    QStringList gmConnectionList = {"Juliet", "Romeo"};


private:
    ConnectionPanel *gpConnectionPanel;


signals:
    void hideConnectionWindow();


};

#endif // CONNECTIONWINDOW_H