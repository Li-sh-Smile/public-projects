#ifndef MOUSEHOOK_H
#define MOUSEHOOK_H

#include <QObject>

#ifdef _WIN32

#include <windows.h>

#endif
class MouseHook : public QObject
{
    Q_OBJECT
public:
    static MouseHook *getInstance();

    void start();
    void stop();

signals:
    void sigMouseCurrentPos(long x,long y);
    void sigMousePressed(bool pressed);

private slots:
    void startHook();
    void stopHook();

private:

    //启动鼠标HOOK
    bool startMouseHook();
    //关闭鼠标HOOK
    bool stopMouseHook();

    //启动键盘HOOK
    bool startKeyboardHook();
    //关闭键盘HOOK
    bool stopKeyboardHook();

private:
    explicit MouseHook(QObject *parent = nullptr){}
public:
};

#endif // MOUSEHOOK_H
