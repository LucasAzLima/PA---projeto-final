#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    ui->lineEdit->setText("127.0.0.1");
    connect(ui->pbconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));
    connect(ui->pbdisconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpDisconnect()));
    connect(ui->pushButtonStart,
            SIGNAL(clicked(bool)),
            this,
            SLOT(startTime()));
    connect(ui->pushButtonStop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(stopTime()));
    connect(ui->horizontalSlidertime,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(Time(int)));
}
void MainWindow::tcpConnect(){


    socket->connectToHost(ui->lineEdit->text(),1234);
    if(socket->waitForConnected(3000)){
        ui->labelStatus->setText("Connected");
    }
    else{
        ui->labelStatus->setText("Disconnected");
    }
}

void MainWindow::tcpDisconnect()
{

    socket->disconnectFromHost();
    if (socket->state() == QAbstractSocket::UnconnectedState ||
            socket->waitForDisconnected(1000)){

        ui->labelStatus->setText("Disconnect ");
    }
}

void MainWindow::startTime()
{

    startTimer(timming*1000);

}

void MainWindow::stopTime()
{
    killTimer(timeid);
}

void MainWindow::putData(){
    QDateTime datetime;
    QString str;
    qint64 msecdate;
    int min,max;
    min = ui->horizontalSliderMin->value();
    max = ui->horizontalSliderMax->value();

    if(socket->state()== QAbstractSocket::ConnectedState){

        msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
        str = "set "+ QString::number(msecdate) + " " + QString::number(((float)qrand()/RAND_MAX)*(max - min) +  min)+"\r\n";
        ui->listWidget->addItem(str);

        socket->write(str.toStdString().c_str()) ;
    }
}

MainWindow::~MainWindow(){
    delete socket;
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    timeid = event->timerId();


    putData();

    repaint();
}

void MainWindow::Time(int _timming)
{
    timming=_timming;
    startTime();
    killTimer(timeid);
}
