
#include "camerapanel.h"
#include "QMessageBox"



CameraPanel::CameraPanel(MainWindow *Window) : MainWindow(Window)
{
    attachWindow();

    gmTemplate = cv::imread("template.png", CV_LOAD_IMAGE_COLOR);

}

CameraPanel::~CameraPanel()
{
    delete gpStream;
}



int CameraPanel::startCamera()
{
    int ret ;

    std::cout << "Starting Camera... Ip" << *gpIpAddress << "Port: " << std::to_string(*gpStreamPort) << std::endl;
    ret = gpStream->start(*gpIpAddress, *gpStreamPort, this);
    if(ret == FAIL)
    {
        emit showMessageBox("Connection Established!");
        std::cout << "Streaming Connection Failed "<<std::endl;

        return FAIL;
    }
    else
    {
        std::cout << "Streaming Connection has been established" << std::endl;
        return SUCCESS;
    }
}



int CameraPanel::showMessage(QString Str)
{
    this->setStyleSheet("QMessageBox{background-color:rgb(46, 52, 54); } QMessageBox QPushButton { background-color: rgb(46, 52, 54); color: rgb(114, 159, 207);} QMessageBox QLabel{color:rgb(114, 159, 207);}");
    return QMessageBox::information(this,"Upgrade Done",Str);

}



void CameraPanel::printScreen(const cv::Mat &Frame)
{
    static int count = 0;

    count ++;
    cv::Mat scaled;


    cv::resize(Frame, scaled, cv::Size(ui->frame_label->width(), ui->frame_label->height()));


    scaled = scaled + gmTemplate;

    if(count >= 50)
    {
        emit screenClose();
        usleep(1000);
        count = 0;
        emit screenShow();
        usleep(1000);
    }

    emit refreshScreen(QPixmap::fromImage(cvMatToQImage(scaled)));
}

void CameraPanel::attachWindow()
{
    connect(this, SIGNAL(refreshScreen(QPixmap)), ui->frame_label, SLOT(setPixmap(QPixmap)), Qt::QueuedConnection);
    connect(this, SIGNAL(screenClose()), ui->frame_label, SLOT(close()), Qt::QueuedConnection);
    connect(this, SIGNAL(screenShow()), ui->frame_label, SLOT(show()), Qt::QueuedConnection);
    connect(this, SIGNAL(showMessageBox(QString)), this, SLOT(showMessage(QString)), Qt::BlockingQueuedConnection);
}



QImage  CameraPanel::cvMatToQImage( const cv::Mat &inMat )
{

    switch ( inMat.type() )
    {
     // 8-bit, 4 channel
     case CV_8UC4:
     {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
     }

     // 8-bit, 3 channel
     case CV_8UC3:
     {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
     }

     // 8-bit, 1 channel
     case CV_8UC1:
     {
    #if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Grayscale8 );
    #else
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if ( sColorTable.isEmpty() )
        {
           sColorTable.resize( 256 );

           for ( int i = 0; i < 256; ++i )
           {
              sColorTable[i] = qRgb( i, i, i );
           }
        }

        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );
    #endif

        return image;
     }

     default:
       std::cout << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type() << std::endl;
        break;
    }

    return QImage();
}
