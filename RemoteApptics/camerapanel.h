#ifndef CAMERAPANEL_H
#define CAMERAPANEL_H

#include "mainwindow.h"
#include "ui_mainwindow.h"


class CameraPanel : public MainWindow
{

    Q_OBJECT

signals:
    void refreshScreen(QPixmap Pix);
    void clearScreen();

    void screenClose();
    void screenShow();
    int showMessageBox(QString);

private slots:
    int showMessage(QString);

public:
    CameraPanel(MainWindow *Window);
    void startCamera();
    void printScreen(const QPixmap &PixMap);



private:
    void attachWindow();

    std::string *gpStreamIpAddress;
    int *gpStreamPort;

};

#endif // CAMERAPANEL_H
