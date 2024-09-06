/*


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setFrameRate(int fps);  // New method to set frame rate

private slots:
    void on_pushButton_clicked();
    void updateFrame();

private:
    Ui::MainWindow *ui;
    QProcess *process;
    QTimer *timer;
    int frameRate;  // Frame rate variable




};

#endif // MAINWINDOW_H




*/







#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setFrameRate(int fps);  // New method to set frame rate

private slots:
    void on_pushButton_clicked();
    void updateFrame();

    void on_pushButton_Route_clicked();

    void on_pushButton_Phone_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *process;
    QTimer *timer;
    int frameRate;  // Frame rate variable
 QWidget *popupWidget;  // Pointer to the PIS_WIDGET instance



 //########### System QLabel ######################


 private slots:
 void updateTimeLabel();  // Slot to update the QLabel with the current time

 //#############################################



};

#endif // MAINWINDOW_H
