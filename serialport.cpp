#include "serialport.h"
#include <QDebug>

SerialPort::SerialPort()
{
    qDebug() << "SerialPort::constructor called";
}

void SerialPort::run()
{
    qDebug() << "SerialPort::run begin";

    while(runEnabled) {
        static clock_t workTime = clock();
        if ((clock() - workTime) >= 1000) {
            workTime = clock();
            qDebug() << "SerialPort::run work";
        }
    }

    qDebug() << "SerialPort::run end";
}

void SerialPort::connectTo(QString portName, QString portSpeed)
{
    qDebug() << "connectTo";
}

void SerialPort::serial_connectTo(QString portName, QString portSpeed)
{
    qDebug() << "serial_connectTo";
}

void SerialPort::quit()
{
    qDebug() << "SerialPort::quit called";
    runEnabled = false;
}
