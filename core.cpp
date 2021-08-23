#include "core.h"

#include <QDebug>
#include <QThread>

Core::Core()
{
    qDebug() << "Core::constructor called";
    serial = new SerialPort;
}

Core::~Core()
{
    serial->quit();
    serial->wait();
    delete serial;
}

void Core::run()
{
    qDebug() << "Core::run begin";

    serial->start();

    while(runEnabled) {
        if (!serial->isEmpty()) {
            qDebug() << "BL: Receive: " << serial->read().toHex('.');
        }
        QThread().currentThread()->msleep(1);
    }

    qDebug() << "Core::run end";
}

SerialPort *Core::getSerial()
{
    return serial;
}

void Core::quit()
{
    qDebug() << "Core::quit called";
    runEnabled = false;
}

