#ifndef CONNECTIONPANEL_H
#define CONNECTIONPANEL_H


#include "ui_connectionwindow.h"
#include "connectionwindow.h"

class ConnectionPanel : public ConnectionWindow
{

    Q_OBJECT

public:
    ConnectionPanel(ConnectionWindow *Window);

private:
    void attachConnectionWindow();
    ConnectionWindow *localConnectionWindow;

signals:
    void setIpAddress(const QString &);
    void setStreamPort(const QString &);
    void setControlPort(const QString &);

private slots:
    void accepted();
    void rejected();
    void comboBoxIndexChanged(int);
    void closed();

};

#endif // CONNECTIONPANEL_H
