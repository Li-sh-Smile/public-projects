#include "mousehook.h"

#include <QDebug>
#include <QThread>

#ifdef _WIN32

#include <windows.h>

#endif

static MouseHook *mHook = nullptr;
static HHOOK mMouseHook = NULL;
static HHOOK mKeyboardHook = NULL;
static QThread *mThread = nullptr;

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
HMODULE ModuleFromAddress(PVOID pv);



MouseHook *MouseHook::getInstance()
{
    qDebug() << "main:" << QThread::currentThread();
    if(nullptr == mHook
            || nullptr == mThread){
        mHook = new MouseHook;
        mThread = new QThread;
        mHook->setParent(nullptr);
        mHook->moveToThread(mThread);
        connect(mThread,&QThread::started,mHook,&MouseHook::startHook);
        connect(mThread,&QThread::finished,mHook,&MouseHook::stopHook);

    }
    return mHook;
}

void MouseHook::start()
{
    mThread->start();
}

void MouseHook::stop()
{
    mThread->quit();
    mThread->wait();
}

void MouseHook::startHook()
{
    startMouseHook();
    startKeyboardHook();
}

void MouseHook::stopHook()
{
    stopMouseHook();
    stopKeyboardHook();
}

bool MouseHook::startMouseHook()
{
    qDebug() << "startMouseHook:" << QThread::currentThread();
    if (NULL != mMouseHook
            && !stopMouseHook())
        return true;

    mMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, ModuleFromAddress((PVOID)MouseProc), NULL);
    if (NULL == mMouseHook)
    {
        qDebug() << "regiter hook for mouse failed";
        return false;
    }

    {
        POINT point;
        GetCursorPos(&point);            // 获取鼠标指针位置（屏幕坐标）
        emit sigMouseCurrentPos(point.x,point.y);
    }

    return true;
}

bool MouseHook::stopMouseHook()
{
    qDebug() << "stopMouseHook:" << QThread::currentThread();
    if (NULL == mMouseHook)
        return true;

    UnhookWindowsHookEx(mMouseHook);
    mMouseHook = NULL;

    return true;
}

bool MouseHook::startKeyboardHook()
{
    if (NULL != mKeyboardHook
            && !stopKeyboardHook())
        return true;

    mKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, ModuleFromAddress((PVOID)KeyboardProc), NULL);
    if (NULL == mKeyboardHook)
    {
        qDebug() << "regiter hook for keyboard failed";
        return false;
    }

    return true;
}

bool MouseHook::stopKeyboardHook()
{
    if (NULL == mKeyboardHook)
        return true;

    UnhookWindowsHookEx(mKeyboardHook);
    mKeyboardHook = NULL;

    return true;
}


HMODULE ModuleFromAddress(PVOID pv)
{
    MEMORY_BASIC_INFORMATION mbi;

    if (VirtualQuery(pv, &mbi, sizeof(mbi)) != 0)
        return (HMODULE)mbi.AllocationBase;

    else
        return NULL;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)

{
    if(HC_ACTION == nCode){
        PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT)lParam;
        qDebug() << "MousePos:" << p->pt.x << p->pt.y;

        //qDebug() << "MouseProc:" << QThread::currentThread();

        emit mHook->sigMouseCurrentPos(p->pt.x,p->pt.y);

        if (WM_LBUTTONDOWN == wParam || WM_RBUTTONDOWN == wParam
                || WM_MBUTTONDOWN == wParam)
            emit mHook->sigMousePressed(true);

        if (WM_LBUTTONUP == wParam || WM_RBUTTONUP == wParam
                || WM_MBUTTONUP == wParam)
            emit mHook->sigMousePressed(false);


        //qDebug() << wParam;

    }

    return CallNextHookEx(mMouseHook, nCode, wParam, lParam);

}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(HC_ACTION == nCode){
        PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;

        if(WM_KEYDOWN == wParam){
            qDebug() << "key down:" << Qt::Key(p->vkCode);
        }
        if(WM_KEYUP == wParam){

            qDebug() <<  "key up  :" << Qt::Key(p->vkCode);
        }

    }

    return CallNextHookEx(mKeyboardHook, nCode, wParam, lParam);
}
