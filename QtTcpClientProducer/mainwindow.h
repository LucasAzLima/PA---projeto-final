#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
int timming=1, timeid;

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
   void timerEvent(QTimerEvent *event);

public slots:
  void tcpConnect();
  void tcpDisconnect();
  void startTime();
  void stopTime();
  void putData();
  void Time(int _timming);
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
