#ifndef CAMERAPANEL_H
#define CAMERAPANEL_H

#include "ui_mainwindow.h"
#include "mainwindow.h"


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
    virtual ~CameraPanel();

    int startCamera();
    void printScreen(const cv::Mat &Frame);



private:
    void attachWindow();
    QImage cvMatToQImage( const cv::Mat &inMat );

    cv::Mat gmTemplate;

};

#endif // CAMERAPANEL_H
