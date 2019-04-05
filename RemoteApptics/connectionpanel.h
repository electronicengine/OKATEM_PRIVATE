#ifndef CONNECTIONPANEL_H
#define CONNECTIONPANEL_H


#include "ui_connectionwindow.h"
#include "connectionwindow.h"

class ConnectionPanel : public ConnectionWindow
{

    Q_OBJECT

public:
    ConnectionPanel(ConnectionWindow *Window);
    void deployPanel(int Index);
    int startConnection();

signals:
    void setIpAddress(const QString &);
    void setStreamPort(const QString &);
    void setControlPort(const QString &);
    void hideConnectionWindow();
    void hideButtonBox();
    int showMessageBox(QWidget*, QString, QString, MessageBoxType);


private:
    void attachConnectionWindow();
    ConnectionWindow *localConnectionWindow;

};

#endif // CONNECTIONPANEL_H
