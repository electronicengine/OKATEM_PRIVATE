#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <thread>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    cv::Mat image = cv::imread("hyperion.jpg");

    if(image.empty()){
       std::cout << "image empty" << std::endl;
    }else{

        ui->frame_label->setPixmap(QPixmap::fromImage( cvMatToQImage( image ) ));
    }


    std::thread buttonFollow(&MainWindow::buttonFlower, this);
    buttonFollow.detach();


    gpConnectionBox = new ConnectionDialog;

    connect(gpConnectionBox, SIGNAL(accepted(std::string, int)), this, SLOT(connectionAccepted(std::string, int)));
    connect(gpConnectionBox, SIGNAL(rejected()), this, SLOT(connectionRejected()));

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionConnection_triggered()
{

    gpConnectionBox->show();

}


void MainWindow::streamFrameCallBack(const cv::Mat &Frame)
{
    QPixmap pix = QPixmap::fromImage( cvMatToQImage( Frame ) );

    ui->frame_label->setPixmap(pix.scaled(1024,768));
}


void MainWindow::on_actionUpdate_Firmware_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "select binary", "/root/qt-workspace");
    std::cout << file_name.toStdString() << std::endl;

//    gpController->updateFirmware(file_name.toStdString());

}


void MainWindow::deployPanel()
{

    ui->status_label->setText((gmSfpInfo.status == 1) ? "Connected":"Disconnected");

    ui->tx_power_label->setText(QString::number(gmSfpInfo.tx_power));
    ui->rx_power_label->setText(QString::number(gmSfpInfo.rx_power));


    std::cout << gmEnvironmentInfo.sensor_data.pressure << std::endl;
    ui->temperature_label->setText(QString::number(gmEnvironmentInfo.sensor_data.temperature));
    ui->pressure_label->setText(QString::number(gmEnvironmentInfo.sensor_data.pressure));
    ui->altitude_label->setText(QString::number(gmEnvironmentInfo.sensor_data.altitude));
    ui->compass_label->setText(QString::number(gmEnvironmentInfo.sensor_data.compass_degree));
    ui->nmea_label->setText(QString(gmEnvironmentInfo.gps_string.c_str()));

}

void MainWindow::buttonFlower()
{

    int counter=0;

    while(1)
    {
        counter++;

        if(gmUpButtonPressed){

            gpController->turnUp();

        }else if(gmDownButtonPressed){

            gpController->turnDown();

        }else if(gmLeftButtonPressed){

            gpController->turnLeft();

        }else if(gmRightButtonPressed){

            gpController->turnRight();

        }

        usleep(50000);

        if(counter >= 20)
        {
            counter = 0;

            if(gmControllerConnectionEstablished == 1)
            {

                std::cout << "deploy" << std::endl;
                gpController->getFsoInformations(gmControlInfo, gmEnvironmentInfo, gmSfpInfo);

                deployPanel();

            }

        }

    }

}



QImage  MainWindow::cvMatToQImage( const cv::Mat &inMat )
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



void MainWindow::connectionAccepted(std::string IpAddress, int Port)
{

    int ret;

    gpController = new Controller;
    gpStream = new VideoStream;

    gmIpAddress = IpAddress;
    gmPort = Port;

    ret = gpController->start(gmIpAddress, CONTROLLER_PORT);
    if(ret == FAIL)
    {
        QMessageBox::critical(this, "Error", "Controller Connection Failed");


        std::cout << "Controller Connection Failed"<<std::endl;
    }

    ret = gpController->getFsoInformations(gmControlInfo, gmEnvironmentInfo, gmSfpInfo);
    if(ret == FAIL)
    {

        QMessageBox::critical(this, "Error", "Connection Failed");
        std::cout << "Connection Failed"<<std::endl;

        delete gpController;
    }
    else
    {
        QMessageBox::information(this, "Info", "Connection Established");
        std::cout << "Connection Established "<<std::endl;

        ret = gpStream->start(gmIpAddress, gmPort, this);
        if(ret == FAIL)
        {
            QMessageBox::critical(this, "Error", "Streaming Connection Failed");
            std::cout << "Streaming Connection Failed "<<std::endl;
        }

        setTitle();

        gmControllerConnectionEstablished = 1;

        ui->servo1_pos_label->setText(QString::number(gmControlInfo.servo_motor1_degree));
        ui->servo2_pos_label->setText(QString::number(gmControlInfo.servo_motor2_degree));
        ui->step1_pos_label->setText(QString::number(gmControlInfo.step_motor1_direction));
        ui->step2_pos_label->setText(QString::number(gmControlInfo.step_motor2_direction));

        ui->servo1_slider->setValue(gmControlInfo.servo_motor1_degree);
        gmServo1SliderValue = gmControlInfo.servo_motor1_degree;

        ui->servo2_slider->setValue(gmControlInfo.servo_motor2_degree);
        gmServo2SliderValue = gmControlInfo.servo_motor2_degree;

        deployPanel();

        gpConnectionBox->ui->buttonBox->hide();
    }

}



void MainWindow::connectionRejected()
{
    std::cout << "rejected" << std::endl;
}



void MainWindow::on_speed_slider_valueChanged(int value)
{

    ui->speed_label->setText("Speed : " + QString::number(value));
    gpController->setSpeed(value);
}



void MainWindow::on_up_button_pressed(){ gmUpButtonPressed = 1; }



void MainWindow::on_up_button_released(){ gmUpButtonPressed = 0; }



void MainWindow::on_left_button_pressed(){ gmLeftButtonPressed = 1; }



void MainWindow::on_left_button_released(){ gmLeftButtonPressed = 0; }



void MainWindow::on_right_button_pressed(){ gmRightButtonPressed = 1; }



void MainWindow::on_right_button_released(){ gmRightButtonPressed = 0;}



void MainWindow::on_down_buttton_pressed(){ gmDownButtonPressed = 1;}



void MainWindow::on_down_buttton_released(){ gmDownButtonPressed = 0;}



void MainWindow::on_servo1_slider_valueChanged(int value)
{
    std::cout << value << std::endl;
    ui->servo1_pos_label->setText(QString::number(value));
    gpController->servo1SetValue(value);
}



void MainWindow::on_servo2_slider_valueChanged(int value)
{
    std::cout << value << std::endl;
    ui->servo2_pos_label->setText(QString::number(value));
    gpController->servo2SetValue(value);
}



void MainWindow::on_increase1_button_clicked()
{
    ui->servo1_slider->setValue(++gmServo1SliderValue);
}



void MainWindow::on_decrease1_button_clicked()
{
     ui->servo1_slider->setValue(--gmServo1SliderValue);
}



void MainWindow::on_increase2_button_clicked()
{
     ui->servo2_slider->setValue(++gmServo2SliderValue);
}



void MainWindow::on_decrease2_button_clicked()
{
     ui->servo2_slider->setValue(--gmServo2SliderValue);
}



std::string MainWindow::execCmd(const char* cmd)  // replace popen and pclose with _popen _pclose for windows
{
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
            {
                result += buffer;
            }
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);

    result = result.substr(0, result.size() - 1);

    return result;
}



void MainWindow::setTitle()
{
    char cmd[100];

    snprintf(cmd, 100, "sudo sshpass -p \"hyperion\" ssh pi@%s hostname", gmIpAddress.c_str());

    std::string hostName = execCmd(cmd);

    MainWindow::setWindowTitle(QString(hostName.c_str()) + QString(" - ") + QString(gmIpAddress.c_str()));

}

