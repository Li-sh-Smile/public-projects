#include "DrawScales.h"
#include <QDebug>

DrawScales::DrawScales(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{
    connect(this,&DrawScales::sigMarginsChanged,[=](){
        setTopMargin(stuDrawProperty.margins);
        setBottomMargin(stuDrawProperty.margins);
        setLeftMargin(stuDrawProperty.margins);
        setRightMargin(stuDrawProperty.margins);
    });

    setStartValue(0);
    setStopValue(100);
    setLineColor("red");
    setTextColor("green");
    setTextPixelSize(20);
    setSpacingValue(1);
    setMargins(0);
    setDrawType(0);
}

void DrawScales::paint(QPainter *painter)
{
    paintLines(painter);
}

void DrawScales::paintLines(QPainter *painter)
{
    int x = stuDrawProperty.leftMargin;
    int y = stuDrawProperty.topMargin;
    int w = boundingRect().width() - x - stuDrawProperty.rightMargin;
    int h = boundingRect().height() - y - stuDrawProperty.bottomMargin;
    //== 0刻度尺在上，字体在下
    if(stuDrawProperty.drawType == 0){
        float length = (stuDrawProperty.stopValue - stuDrawProperty.startValue)*1.0/(stuDrawProperty.spacingValue);
        QVector<QPointF> lines;
        float height = (h-stuDrawProperty.textPixelSize)*0.5;
        float posX = x;

        QFont font = painter->font();
        font.setPixelSize(stuDrawProperty.textPixelSize);
        painter->setFont(font);
        painter->setPen(stuDrawProperty.textColor);
        painter->setBrush(Qt::NoBrush);

        //>0正序 <0倒叙
        if(length > 0){
            int count = 0;
            float countSpacing =  w*1.0/(length);
            while (posX <= w+stuDrawProperty.rightMargin) {
                QRectF textRect(posX-stuDrawProperty.textPixelSize*2, h-stuDrawProperty.textPixelSize, stuDrawProperty.textPixelSize*4, stuDrawProperty.textPixelSize);

                //绘制字体
                if(stuDrawProperty.textPixelSize*(QString::number(stuDrawProperty.stopValue).size()*0.5+0.5) < countSpacing
                        || count%2 == 0)
                    painter->drawText(textRect, Qt::AlignHCenter|Qt::AlignVCenter, QString::number(count*stuDrawProperty.spacingValue));
                if(count%2 == 0)
                    height = (h-stuDrawProperty.textPixelSize)*0.8;
                else
                    height = (h-stuDrawProperty.textPixelSize)*0.6;
                lines.append(QPointF(posX,y));
                lines.append(QPointF(posX,y+height));
                count++;
                posX = countSpacing*count+x;
            }
        }


        QPen pen(stuDrawProperty.lineColor, 1);
        painter->setPen(pen);
        painter->drawLines(lines);
    }
    //== 1刻度尺在下，字体在上
    else if(stuDrawProperty.drawType == 1){

    }
    //== 2刻度尺在左，字体在右
    else if(stuDrawProperty.drawType == 2){

    }
    //== 3刻度尺在右，字体在左
    else if(stuDrawProperty.drawType == 3){

    }
}
