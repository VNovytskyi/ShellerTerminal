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
        static clock_t time = clock();
        if ((clock() - time) >= 1000) {
            time = clock();
        }
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

