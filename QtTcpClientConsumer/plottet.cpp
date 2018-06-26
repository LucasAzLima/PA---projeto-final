#include "plottet.h"
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QPainter>
#include <QDebug>
Plottet::Plottet(QWidget *parent) : QWidget(parent)
{
    startTimer(1000);

}
void Plottet::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QBrush brush;
    QPen pen;

    // habilita o anti aliasing (atenua oeve
    // efeito de serrilhado nas figuras geometricas)
    painter.setRenderHint(QPainter::Antialiasing);

    // brush com a cor amarela com preenchimento
    // solido
    brush.setColor(QColor(255,255,100));

    brush.setStyle(Qt::SolidPattern);
    // informa ao painter qual o pincel atual
    painter.setBrush(brush);

    pen.setStyle(Qt::SolidLine);
    // pen com cor vermelha e dois pixels de largura
    pen.setColor(QColor(255,0,0));
    pen.setWidth(2);

    // informa ao painter qual o pen atual
    painter.setPen(pen);

    // desenha um retangulo tomando toda a area
    // do componente


    painter.drawRect(0,0,width(), height());
    for (int i = 0; i < (tempof.size()-1) && tempof.size()!=0; ++i) {

        painter.drawLine(width()-width()*tempof[i],height()-height()*valorf[i]/100.0,
                         width()-width()*tempof[i+1],height()-height()*valorf[i+1]/100.0);

    }
}

void Plottet::setdata(vector<float> tempo, vector<float> valor)
{
    tempof=tempo;
    valorf=valor;
    repaint();
}


void Plottet::timerEvent(QTimerEvent *event)
{
    repaint();
}

