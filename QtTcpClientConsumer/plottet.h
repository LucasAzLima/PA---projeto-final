#ifndef PLOTTET_H
#define PLOTTET_H
#include <QDebug>
#include <QWidget>
#include <vector>
#include <iostream>

using namespace std;

class Plottet : public QWidget
{
    Q_OBJECT

    vector<float> tempof, valorf;

public:
    explicit Plottet(QWidget *parent = nullptr);

     void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

public slots:
void setdata(vector<float> tempo, vector<float> valor);
};

#endif // PLOTTET_H
