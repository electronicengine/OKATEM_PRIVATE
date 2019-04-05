#ifndef CAMERAPANEL_H
#define CAMERAPANEL_H

#include "ui_mainwindow.h"
#include "mainwindow.h"


class Process;

class CameraPanel : public MainWindow
{

    Q_OBJECT

signals:
    void refreshScreen(QPixmap Pix);
    void clearScreen();

    void screenClose();
    void screenShow();



public:
    CameraPanel(MainWindow *Window);
    virtual ~CameraPanel();

    int startCamera();
    void displayCallBack(cv::Mat &Frame);
    void scaleTarget(int Value);


private:
    void attachWindow();
    QImage cvMatToQImage( const cv::Mat &inMat );
    void processImage(cv::Mat &Image);
    cv::Mat gmRomeoTemplate;
    cv::Mat gmJulietTemplate;

    std::mutex gmMutex;
};



#endif // CAMERAPANEL_H
