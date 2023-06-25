#include "signalwidget.h"
#include <QPainter>

SignalWidget::SignalWidget(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{
    m_signalStrength = SignalStrength::Three;
}


void SignalWidget::setSignalStrength(SignalStrength newSignalStrength)
{
    m_signalStrength = newSignalStrength;
    this->update();
}

void SignalWidget::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);

    //widget 高度分为4份，信号柱由低到高使用对应份额
    float hUnit = this->height() / 4.0;
    int h1 = hUnit * 1;
    int h2 = hUnit * 2;
    int h3 = hUnit * 3;
    int h4 = hUnit * 4;

    //widget 宽度分为十份，四个信号柱各占一份，三个空白区域各占两份
    float wUnit = this->width() / 10.0;
    int x1 = 1;
    int x2 = wUnit * 3;
    int x3 = wUnit * 6;
    int x4 = wUnit * 9 - 1;

    //border-radius
    int rounded = wUnit / 2.0;

    QColor havaSignal = QColor(79, 134, 210);
    QColor noSignal = Qt::gray;

    QColor colorOne, colorTwo, colorThree, colorFour;
    colorOne = noSignal;
    colorTwo = noSignal;
    colorThree = noSignal;
    colorFour = noSignal;

    switch(m_signalStrength)
    {
    case SignalStrength::Four:
        colorFour = havaSignal;
    case SignalStrength::Three:
        colorThree = havaSignal;
    case SignalStrength::Two:
        colorTwo = havaSignal;
    case SignalStrength::One:
        colorOne = havaSignal;
    default: break;
    };

    painter->setPen(colorOne);
    painter->setBrush(colorOne);
    painter->drawRoundedRect(x1, this->height() - h1, wUnit, h1, rounded, rounded);

    painter->setPen(colorTwo);
    painter->setBrush(colorTwo);
    painter->drawRoundedRect(x2, this->height() - h2, wUnit, h2, rounded, rounded);

    painter->setPen(colorThree);
    painter->setBrush(colorThree);
    painter->drawRoundedRect(x3, this->height() - h3, wUnit, h3, rounded, rounded);

    painter->setPen(colorFour);
    painter->setBrush(colorFour);
    painter->drawRoundedRect(x4, this->height() - h4, wUnit, h4, rounded, rounded);
}
