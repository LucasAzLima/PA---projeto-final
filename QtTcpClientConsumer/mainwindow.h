#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plottet.h"

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <vector>
#include <iostream>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int timing, timeid;
    QString strIP;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void timerEvent(QTimerEvent *event);

signals:
vector<float> passData(vector<float>,vector<float>);


public slots:
    void getData();
    void tcpConnect();
    void startTime();
    void stopTime();
    void Time(int _timming);
    void tcpDisconnect();
   void setIP(QString _ip);
   void list();
private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
