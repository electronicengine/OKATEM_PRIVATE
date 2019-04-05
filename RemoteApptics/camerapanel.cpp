
#include "camerapanel.h"
#include "QMessageBox"
#include "process.h"
#include "kalmanfilter.h"
#include "autocontrolwindow.h"

CameraPanel::CameraPanel(MainWindow *Window) : MainWindow(Window)
{
    attachWindow();

    gmRomeoTemplate = cv::imread("romeo_template.png", CV_LOAD_IMAGE_COLOR);
    gmJulietTemplate = cv::imread("juliet_template.png", CV_LOAD_IMAGE_COLOR);

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

        std::cout << "Streaming Connection Failed "<<std::endl;

        return FAIL;
    }
    else
    {
        std::cout << "Streaming Connection has been established" << std::endl;
        return SUCCESS;
    }
}



void CameraPanel::scaleTarget(int Value)
{

    cv::Mat template_image = cv::imread("template.png", CV_LOAD_IMAGE_COLOR);

    double height, width;

    double scale_coefficent;

    ui->scale_label->setText("Target Scale: " + QString::number(Value));

    if(Value >= 0)
    {
        scale_coefficent =  1 + (double)Value/10;

        height = 720 * scale_coefficent;
        width = 960 * scale_coefficent;

        std::cout << "scale_coefficent: " << std::to_string(scale_coefficent) << std::endl;
        std::cout << "size: " << std::to_string(width) << "x" << std::to_string(height) << std::endl;

        cv::resize(template_image, template_image, cv::Size(width, height)); // upscale

        cv::Mat croped_image(template_image, cv::Rect(cv::Point((int)(width - (960))/2,
                                           (int)(height - (720))/2), cv::Size(960, 720)));
        gmMutex.lock();
        gmRomeoTemplate = croped_image;
        gmJulietTemplate = croped_image;

        gmMutex.unlock();
    }
    else
    {
        scale_coefficent =  1 + (-(double)Value/10);

        height = 720 / scale_coefficent;
        width = 960 / scale_coefficent;

        cv::resize(template_image, template_image, cv::Size(width, height)); //down scale

        gmMutex.lock();
        template_image.copyTo(gmRomeoTemplate(cv::Rect(cv::Point((int)(960 - (width))/2,
                                                                 (int)(720 - (height))/2), cv::Size(width, height))));
        template_image.copyTo(gmJulietTemplate(cv::Rect(cv::Point((int)(960 - (width))/2,
                                                                 (int)(720 - (height))/2), cv::Size(width, height))));
        gmMutex.unlock();

    }

}



void CameraPanel::displayCallBack(cv::Mat &Frame)
{
    static int count = 0;


    cv::Mat scaled;
    count ++;

    cv::resize(Frame, scaled, cv::Size(ui->frame_label->width(), ui->frame_label->height()));

    processImage(scaled);



//    cv::addWeighted(scaled, 0.5, gmRomeoTemplate, 0.5, 1, scaled);

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

void CameraPanel::processImage(cv::Mat &Image)
{
    static KalmanFilter kalman_filter;
    cv::Point noisy_center;
    cv::Point clear_center;
    cv::Point drawing_center;

    int point_size;

    std::vector<cv::Point> points;

    cv::Mat processing_img;

    Image.copyTo(processing_img);

    Process::eliminateColors(processing_img);
    points = Process::detectContoursCenter(processing_img);

    point_size = points.size();

    noisy_center = Process::calculateCenter(points);

    if(noisy_center.x > 0 && noisy_center.y > 0)
        clear_center = kalman_filter.takeKalmanFilter(noisy_center);

    if(clear_center.x > 0 && clear_center.y > 0)
    {
        cv::circle(Image, clear_center, 5, cv::Scalar(255,255,255), -1);
        drawing_center = clear_center;

//        std::cout << "x:" << std::to_string(drawing_center.x) <<
//                     " y:" << std::to_string(drawing_center.y) << std::endl;
    }

    gpAutoControlWindow->setFsoPoints(drawing_center, point_size);
    gpAutoControlWindow->drawErrorVector(Image, drawing_center);


}
