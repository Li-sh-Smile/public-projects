#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

#include "mousehook.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(QSize(50,50));
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SplashScreen);
    setAttribute(Qt::WA_TranslucentBackground, true);
    slotPressed(false);


#ifdef Q_OS_LINUX
    XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput, 0,
                            0, NULL, 0, ShapeSet, YXBanded);
#endif
#ifdef Q_OS_WIN
    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
                  WS_EX_TRANSPARENT//忽略一切消息（WM_PAINT除外）
                  | WS_EX_LAYERED); //层风格，有他才能支持半透明
#endif

    MouseHook::getInstance()->start();
    connect(MouseHook::getInstance(),&MouseHook::sigMouseCurrentPos,this,&Widget::slotMove);
    connect(MouseHook::getInstance(),&MouseHook::sigMousePressed,this,&Widget::slotPressed);

}

Widget::~Widget()
{
    delete ui;
    MouseHook::getInstance()->stop();
}

void Widget::slotMove(long x, long y)
{
    move(x-25,y-25);
}

void Widget::slotPressed(bool pressed)
{
    if(pressed)
        ui->widget->setStyleSheet("background:#66333300;border: 2px solid gray;border-radius:25px;");
    else
        ui->widget->setStyleSheet("background:#33003333;border: 2px solid gray;border-radius:25px;");
}

void Widget::paintEvent(QPaintEvent *event)
{
    return QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setBrush(QColor(255,200,200,100));

//    if(pressed_){
//        painter.setBrush(QColor(255,200,200,100));
//    }
//    else{
//        painter.setBrush(QColor(125,125,125,100));
//    }

    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();
    painter.drawEllipse(QPoint(this->rect().left()+25, this->rect().top()+25), 25, 25);

}

