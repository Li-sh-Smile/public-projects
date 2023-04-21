#ifndef ROCKERVONTROL_H
#define ROCKERVONTROL_H

#include <QWidget>

class RockerVontrol :public QWidget
{
    Q_OBJECT
public:
    RockerVontrol(QWidget *parent = 0);

private:
    void init();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    int radiusBig = 0;              //外圆半径
    int radiusSmill = 0;            //内圆半径

    QPoint centerPos;               //中心位置
    QPoint mousePos;                //鼠标指针位置

    bool isPressed = false;         //鼠标是否被按下
};

#endif // ROCKERVONTROL_H
