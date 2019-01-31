
#include "camerapanel.h"
#include "QMessageBox"


int CameraPanel::showMessage(QString Str)
{
    this->setStyleSheet("QMessageBox{background-color:rgb(46, 52, 54); } QMessageBox QPushButton { background-color: rgb(46, 52, 54); color: rgb(114, 159, 207);} QMessageBox QLabel{color:rgb(114, 159, 207);}");
    return QMessageBox::information(this,"Upgrade Done",Str);

}

CameraPanel::CameraPanel(MainWindow *Window) : MainWindow(Window)
{
    attachWindow();

    gpStream = new VideoStream(gpVideoStreamSocket);
    gpStreamIpAddress = &gmIpAddress;
    gpStreamPort = &gmStreamPort;

}

void CameraPanel::startCamera()
{
    int ret ;

    ret = gpStream->start(*gpStreamIpAddress, *gpStreamPort, this);
    if(ret == FAIL)
    {
        emit showMessageBox("Connection Established!");
        std::cout << "Streaming Connection Failed "<<std::endl;
    }

}

void CameraPanel::printScreen(const QPixmap &PixMap)
{
    static int count = 0;

    count ++;

    if(count >= 50)
    {
        emit screenClose();
        usleep(1000);
        count = 0;
        emit screenShow();
        usleep(1000);
    }

    emit refreshScreen(PixMap);
}

void CameraPanel::attachWindow()
{
    connect(this, SIGNAL(refreshScreen(QPixmap)), ui->frame_label, SLOT(setPixmap(QPixmap)), Qt::QueuedConnection);
    connect(this, SIGNAL(screenClose()), ui->frame_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(screenShow()), ui->frame_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(showMessageBox(QString)), this, SLOT(showMessage(QString)), Qt::BlockingQueuedConnection);
}
