#ifndef SIGNALWIDGET_H
#define SIGNALWIDGET_H

/*!
    信号显示控件
    自适应长宽比例；
    widget 高度分为4份，信号柱由低到高使用对应份额；
    widget 宽度分为十份，四个信号柱各占一份，三个空白区域各占两份
*/

#include <QQuickPaintedItem>

class SignalWidget : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit SignalWidget(QQuickPaintedItem *parent = nullptr);

    /*! 信号强度 */
    enum class SignalStrength{
        Zero,
        One,
        Two,
        Three,
        Four
    };

    /*! 设置信号强度 */
    void setSignalStrength(SignalStrength newSignalStrength);

protected:
    void paint(QPainter *painter) override;

private:
    SignalStrength m_signalStrength;

};

#endif // SIGNALWIDGET_H
