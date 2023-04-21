#include "rockervontrol.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QtMath>

RockerVontrol::RockerVontrol(QWidget *parent)
    :QWidget(parent)
{
    init();
}

void RockerVontrol::init()
{
    int _width = width();
    int _height = height();

    //中心位置
    centerPos.setX(_width/2);
    centerPos.setY(_height/2);
    mousePos = centerPos;

    //摇杆内外圈半径
    radiusBig = (_width>_height?_height:_width)/2/5*4;
    radiusSmill = (_width>_height?_height:_width)/2/5;

    qDebug() << QStringLiteral("中心点") << centerPos;
    qDebug() << QStringLiteral("外半径") << radiusBig
             << QStringLiteral("内半径") << radiusSmill;
}

void RockerVontrol::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return QWidget::mousePressEvent(event);

    isPressed = true;
    mousePos = event->pos();
    update();
}

void RockerVontrol::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return QWidget::mouseReleaseEvent(event);

    isPressed = false;
    mousePos = centerPos;
    update();
}

void RockerVontrol::mouseMoveEvent(QMouseEvent *event)
{
    if(!isPressed)
        return QWidget::mouseMoveEvent(event);

    mousePos = event->pos();
    update();
}

void RockerVontrol::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    //消锯齿
    painter.setRenderHints(QPainter::SmoothPixmapTransform);


    //设置偏移点
    painter.translate(centerPos.x(),centerPos.y());

    //绘制外圆
    painter.setPen(QPen(QColor(255,0,0),0,Qt::SolidLine));
    painter.setBrush(QColor(255,0,0));
    painter.drawEllipse(-radiusBig,-radiusBig,radiusBig*2,radiusBig*2);


    //绘制内圆
    painter.setPen(QPen(QColor(0,255,0),0,Qt::SolidLine));
    painter.setBrush(QColor(0,255,0));

    if(!isPressed){
        painter.drawEllipse(-radiusSmill,-radiusSmill,radiusSmill*2,radiusSmill*2);
    }
    else {
        QPoint shiftingPos = mousePos - centerPos;
        //计算鼠标点到中心点的半径距离
        qreal mouseRadius = qSqrt(qPow(mousePos.x()-centerPos.x(),2) + qPow(mousePos.y()-centerPos.y(),2));
        qDebug() << mouseRadius;

        //判断鼠标点位置是否在外圆内
        if(mouseRadius <= radiusBig){
            ;
        }
        else {
            //鼠标点在圆外边
            shiftingPos.setX(shiftingPos.x()/(mouseRadius/radiusBig));
            shiftingPos.setY(shiftingPos.y()/(mouseRadius/radiusBig));
            qDebug() << QStringLiteral("修正点位") << shiftingPos;
        }

        //设置内圆偏移点
        painter.translate(shiftingPos.x(),shiftingPos.y());
        //绘制内圆
        painter.drawEllipse(-radiusSmill,-radiusSmill
                            ,radiusSmill*2,radiusSmill*2);


    }


//    painter.drawEllipse(-150,-30,60,60);
//    painter.drawEllipse(90,-30,60,60);
//    painter.drawEllipse(-30,-150,60,60);
//    painter.drawEllipse(-30,90,60,60);


//    painter.drawEllipse(-30,-30,60,60);
}

void RockerVontrol::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    init();
    update();
}
