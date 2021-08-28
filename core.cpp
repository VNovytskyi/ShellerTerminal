#include "core.h"

Core::Core()
{
    serial = new Serial;
    serial->moveToThread(&serialThread);
    connect(&serialThread, &QThread::started, serial, &Serial::loop);
    serialThread.start();
}

Core::~Core()
{
    serial->disableLoop();
    serialThread.quit();
    serialThread.wait();
    delete serial;
}

void Core::loop()
{
    while(loopEnabled) {
        if (!serial->isEmpty()) {
            QByteArray recvData = serial->read();
            emit appendReceivedData(recvData);
        }
        QThread().currentThread()->msleep(1);
    }
}

Serial *Core::getSerial()
{
    return serial;
}

void Core::disableLoop()
{
    loopEnabled = false;
}

