#include "core.h"

#include <QDebug>
#include <QThread>

Core::Core()
{
    qDebug() << "Core::constructor called";
    serial = new Serial;
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
            QByteArray recvData = serial->read();
            qDebug() << "BL: Receive: " << recvData.toHex('.');
            emit appendReceivedData(recvData);
        }
        QThread().currentThread()->msleep(1);
    }

    qDebug() << "Core::run end";
}

Serial *Core::getSerial()
{
    return serial;
}

void Core::quit()
{
    qDebug() << "Core::quit called";
    runEnabled = false;
}

