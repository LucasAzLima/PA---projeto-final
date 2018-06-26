#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <plottet.h>
#include <QDateTime>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    ui->label->setNum(ui->horizontalSlidertime->value());
    strIP="127.0.0.1";
    ui->lineEdit->setText(strIP);
    connect(ui->pushButtonconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));

    connect(ui->pushButtondisconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpDisconnect()));

    connect(ui->pushButtonstart,
            SIGNAL(clicked(bool)),
            this,
            SLOT(startTime()));

    connect(ui->pushButtonstop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(stopTime()));

    connect(this,
            SIGNAL(passData(vector<float>,vector<float>)),
            ui->widget,
            SLOT(setdata(vector<float>,vector<float>)));

    connect(ui->horizontalSlidertime,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(Time(int)));

    connect(ui->listWidget,
            SIGNAL(currentTextChanged(QString)),
            this,
            SLOT(setIP(QString)));

    connect(ui->pushButtonupdate,
            SIGNAL(clicked(bool)),
            this,
            SLOT(list()));

}

void MainWindow::tcpConnect(){
    strIP=ui->lineEdit->text();
    socket->connectToHost(strIP.toUtf8(),1234);
    if(socket->waitForConnected(3000)){
        ui->status->setText("Connected");
        list();
    }
    else{
        ui->status->setText( "Disconnected");
    }
}
void MainWindow::tcpDisconnect()
{
    socket->disconnectFromHost();
    if (socket->state() == QAbstractSocket::UnconnectedState ||
            socket->waitForDisconnected(1000)){
        ui->status->setText("Disconnect ");
    }
}

void MainWindow::setIP(QString _ip)
{

    strIP=_ip.replace("\n","").replace("\r","");;
    ui->lineEdit->setText(strIP);
}

void MainWindow::list()
{   QString ip;
    QStringList iplist;
    socket->write("list");
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    socket->bytesAvailable();
    while(socket->bytesAvailable()){
        ip = socket->readLine();
        iplist<<ip;
    }
    ui->listWidget->clear();
    ui->listWidget->addItems(iplist);
}
void MainWindow::getData(){
    QString str;
    QStringList list;
    QByteArray array;
    qint64 thetime; Plottet p;
    vector<quint64> thetime2;
    vector<float> tempo,valor;
    qDebug() << "to get data...";
    if(socket->state() == QAbstractSocket::ConnectedState){

        array=QByteArray("get "+strIP.toUtf8()+" 30\r\n");

        if(socket->isOpen()){
            qDebug() << "reading...";
            socket->write(array);
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            socket->bytesAvailable();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                list = str.split(" ");
                if(list.size() == 2){
                    bool ok;
                    str = list.at(0);
                    thetime = str.toLongLong(&ok);
                    str = list.at(1);
                    thetime2.push_back(thetime);
                    valor.push_back(str.toFloat());

                }
            }
            for (int i = 0; i < thetime2.size(); ++i) {
                tempo.push_back((float)(thetime2[i]- thetime2[0])/
                        (thetime2[thetime2.size()-1]-thetime2[0]));

                if(tempo[i]>1)tempo[i]=tempo[i]-1;

            }

            emit passData(tempo, valor);

        }

    }
}


MainWindow::~MainWindow()
{
    delete socket;
    delete ui;

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    timeid = event->timerId();
    getData();
}

void MainWindow::startTime()
{
    startTimer(ui->horizontalSlidertime->value()*1000);
}

void MainWindow::stopTime()
{
    killTimer(timeid);
}
void MainWindow::Time(int _timming)
{
    timing=_timming;
    startTime();
    killTimer(timeid);
}
