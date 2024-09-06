
/*

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QProcess>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , frameRate(30)  // Hardcoded frame rate to 30 FPS
{
    ui->setupUi(this);

    // Initialize QProcess to run ffmpeg command
    process = new QProcess(this);

    // ffmpeg command to capture and convert video frames
    QStringList arguments;
    arguments << "-fflags" << "nobuffer"
              << "-flags" << "low_delay"
              << "-strict" << "experimental"
              << "-video_size" << "506x295"
              << "-input_format" << "mjpeg"
              << "-framerate" << QString::number(frameRate)
              << "-i" << "/dev/video0"
              << "-vf" << "scale=506:295"
              << "-pix_fmt" << "rgb24"
              << "-f" << "rawvideo"
              << "-vsync" << "0"
              << "-";

    // Start ffmpeg process
    process->start("ffmpeg", arguments);

    // Set up a timer to periodically read from process output
    timer = new QTimer(this);
    timer->setInterval(1000 / frameRate);  // Set interval based on hardcoded FPS
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);
    timer->start();  // Start the timer
}

MainWindow::~MainWindow()
{
    delete ui;
    process->close();  // Ensure the process is closed when the application exits
    delete process;
}

void MainWindow::updateFrame()
{
    const int width = 506;
    const int height = 295;
    const int bytesPerFrame = width * height * 3;  // RGB24 format

    if (process->bytesAvailable() >= bytesPerFrame) {
        QByteArray byteArray = process->read(bytesPerFrame);
        QImage image((const uchar*)byteArray.data(), width, height, width * 3, QImage::Format_RGB888);

        if (!image.isNull()) {
            QPixmap pixmap = QPixmap::fromImage(image);
            ui->label_2->setPixmap(pixmap);
            ui->label_3->setPixmap(pixmap);
            ui->label_4->setPixmap(pixmap);
            ui->label->setPixmap(pixmap);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{

}


*/




#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QProcess>
#include <QByteArray>
#include <QLibrary>
#include <QMessageBox>
#include <QPropertyAnimation>



#include <QTimer>
#include <QTime>


const QString pis_lib_path = "/home/pi/zen_OS/pis.so";
const QString phone_lib_path = "/home/pi/zen_OS/phone_call.so";
const QString systemSettings_lib_path = "/home/pi/zen_OS/systemSettings.so";



// Define the function type for creating the PIS_WIDGET
typedef QWidget* (*CreatePISWidgetFunc)(QWidget * parent);
typedef QWidget* (*CreatePhoneCallWidgetFunc)(QWidget * parent);
typedef QWidget* (*createSystemSettingsWidgetFunc)(QWidget * parent);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , frameRate(10)  // Hardcoded frame rate to 30 FPS
, popupWidget(nullptr)  // Initialize the pisWidget pointer
{
    ui->setupUi(this);

    QApplication::setOverrideCursor(Qt::BlankCursor);//make moude/touch cursor invisible
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);  //own


    // Initialize QProcess to run ffmpeg command
    process = new QProcess(this);

    // ffmpeg command to capture and convert video frames
    QStringList arguments;
    arguments << "-fflags" << "nobuffer"
              << "-flags" << "low_delay"
              << "-strict" << "experimental"
              << "-video_size" << "506x295"
              << "-input_format" << "mjpeg"
              << "-framerate" << QString::number(frameRate)
              << "-i" << "/dev/video0"
              << "-vf" << "scale=506:295"
              << "-pix_fmt" << "rgb24"
              << "-f" << "rawvideo"
              << "-vsync" << "0"
              << "-";

    // Start ffmpeg process
    process->start("ffmpeg", arguments);

    // Set up a timer to periodically read from process output
    timer = new QTimer(this);
  //  timer->setInterval(1000 / frameRate);  // Set interval based on hardcoded FPS
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);
    timer->start();  // Start the timer



    //############################# System Time QLAbel #####################################

    // Create a QTimer to update the label every second
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimeLabel);
    timer->start(1000); // 1000 milliseconds = 1 second

    // Call it once to set the initial time immediately
    updateTimeLabel();



    //######################################################################################








}

MainWindow::~MainWindow()
{
    delete ui;
    process->close();  // Ensure the process is closed when the application exits
    delete process;
}





//##################   System time QLabel #####################################


void MainWindow::updateTimeLabel()
{
    // Get current time in desired format
    QTime currentTime = QTime::currentTime();
    QString timeText = currentTime.toString("h:mm:ss - AP");

    // Set the formatted time to label_16
    ui->label_16->setText(timeText);
}




//############################################################################



void MainWindow::updateFrame()
{
    const int width = 506;
    const int height = 295;
    const int bytesPerFrame = width * height * 3;  // RGB24 format

    if (process->bytesAvailable() >= bytesPerFrame) {
        QByteArray byteArray = process->read(bytesPerFrame);
        QImage image((const uchar*)byteArray.data(), width, height, width * 3, QImage::Format_RGB888);

        if (!image.isNull()) {
            QPixmap pixmap = QPixmap::fromImage(image);
            ui->label_cam2->setPixmap(pixmap);
            ui->label_cam3->setPixmap(pixmap);
            ui->label_cam4->setPixmap(pixmap);
            ui->label_cam1->setPixmap(pixmap);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{



   /*  This animation is to keep constant width and height and change x,y */
    ui->frame->show();

    // Create the animation for the position property
    QPropertyAnimation *animation = new QPropertyAnimation(ui->frame, "pos");
    animation->setDuration(280); // Set the animation speed

    // Set the start and end positions (only x and y, width and height remain unchanged)
    animation->setStartValue(QPoint(0, 601));
    animation->setEndValue(QPoint(0, 390));

    // Start the animation
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}















void MainWindow::on_pushButton_5_clicked() {








    // Load the createSystemSettingsWidget.so library
    QLibrary pisLibrary(systemSettings_lib_path);

    if (pisLibrary.load()) {
        // Resolve the function createVideoPlayerWidget
        createSystemSettingsWidgetFunc createSystemSettingsWidget = (createSystemSettingsWidgetFunc) pisLibrary.resolve("createSystemSettingsWidget");
        if (createSystemSettingsWidget) {
            // Create the createSystemSettingsWidget instance
            popupWidget = createSystemSettingsWidget(this);
            if (popupWidget) {
                popupWidget -> showFullScreen();
                this -> hide(); // Hide the ZEN_OS main window

                // Capture pisLibrary by reference using [&]
                connect(popupWidget, & QWidget::destroyed, [ & pisLibrary, this]() {
                    pisLibrary.unload(); // Unload the library
                    this -> showFullScreen(); // Show the ZEN_OS main window again
                });

            } else {
                QMessageBox::critical(this, "Error", "Failed to create createSystemSettingsWidget.");
            }
        } else {
            QMessageBox::critical(this, "Error", "Failed to resolve createSystemSettingsWidget function in createSystemSettingsWidget.so.");
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to load createSystemSettingsWidget.so library.");
    }



}





void MainWindow::on_pushButton_Route_clicked() {
    // Load the pis.so library
    QLibrary pisLibrary(pis_lib_path);

    if (pisLibrary.load()) {
        // Resolve the function createPISWidget
        CreatePISWidgetFunc createPISWidget = (CreatePISWidgetFunc) pisLibrary.resolve("createPISWidget");
        if (createPISWidget) {
            // Create the PIS_WIDGET instance
            popupWidget = createPISWidget(this);
            if (popupWidget) {
                popupWidget -> showFullScreen();
                this -> hide(); // Hide the ZEN_OS main window

                // Capture pisLibrary by reference using [&]
                connect(popupWidget, & QWidget::destroyed, [ & pisLibrary, this]() {
                    pisLibrary.unload(); // Unload the library
                    this -> showFullScreen(); // Show the ZEN_OS main window again
                });

            } else {
                QMessageBox::critical(this, "Error", "Failed to create PIS_WIDGET.");
            }
        } else {
            QMessageBox::critical(this, "Error", "Failed to resolve createPISWidget function in pis.so.");
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to load pis.so library.");
    }
}

void MainWindow::on_pushButton_Phone_clicked() {
    // Load the pis.so library
    QLibrary pisLibrary(phone_lib_path);

    if (pisLibrary.load()) {
        // Resolve the function createPhoneCallWidget
        CreatePhoneCallWidgetFunc createPhoneCallWidget = (CreatePhoneCallWidgetFunc) pisLibrary.resolve("createPhoneCallWidget");
        if (createPhoneCallWidget) {
            // Create the PhoneCall widget instance
            popupWidget = createPhoneCallWidget(this);
            if (popupWidget) {
                popupWidget -> showFullScreen();
                this -> hide(); // Hide the ZEN_OS main window

                // Capture pisLibrary by reference using [&]
                connect(popupWidget, & QWidget::destroyed, [ & pisLibrary, this]() {
                    pisLibrary.unload(); // Unload the library
                    this -> showFullScreen(); // Show the ZEN_OS main window again
                });

            } else {
                QMessageBox::critical(this, "Error", "Failed to create PhoneCall widget.");
            }
        } else {
            QMessageBox::critical(this, "Error", "Failed to resolve createPhoneCallWidget function in pis.so.");
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to load pis.so library.");
    }
}

void MainWindow::on_pushButton_2_clicked()
{


    /*  This animation is to keep constant width and height and change x,y */
   // ui->frame->show();

    // Create the animation for the position property
    QPropertyAnimation *animation = new QPropertyAnimation(ui->frame, "pos");
    animation->setDuration(260); // Set the animation speed

    // Set the start and end positions (only x and y, width and height remain unchanged)
    animation->setStartValue(QPoint(0, 390));
    animation->setEndValue(QPoint(0, 601));

    // Start the animation
    animation->start(QAbstractAnimation::DeleteWhenStopped);


}


void MainWindow::on_pushButton_7_clicked()
{

}


