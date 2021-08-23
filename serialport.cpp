#include "serialport.h"


SerialPort::SerialPort()
{
    qDebug() << "SerialPort::constructor called";
}

void SerialPort::run()
{
    qDebug() << "SerialPort::run begin";

    while(runEnabled) {
        if (serial.isOpen()) {
            if (!transmittQueue.isEmpty()) {
                QByteArray data = transmittQueue.first();
                transmittQueue.pop_front();
                serial.write(data);
                serial.waitForBytesWritten();
            }

            if (serial.bytesAvailable() > 0) {
                serial.waitForReadyRead();
                QByteArray receiveData = serial.readAll();

                //push in sheller
                //if sheller find the package push in receiveQueue
                receiveQueue.push_back(receiveData);
            }
        }

        QThread().currentThread()->msleep(1);
    }

    qDebug() << "SerialPort::run end";
}

bool SerialPort::connectTo(QString portName, QString portSpeed)
{
    qDebug() << "connectTo " << portName << " ," << portSpeed;
    serial.setPortName(portName);
    serial.setBaudRate(portSpeed.toInt());
    return serial.open(QIODevice::ReadWrite);
}

void SerialPort::disconnect()
{
    serial.close();
    serial.clear();
}

QByteArray SerialPort::read()
{
    QByteArray data;

    if (!receiveQueue.isEmpty()) {
        data = receiveQueue.first();
        receiveQueue.pop_front();
    }

    return data;
}

void SerialPort::write(QByteArray &data)
{
    //push data in sheller than in transmittQueue
    transmittQueue.push_back(data);
}

bool SerialPort::isEmpty()
{
    return receiveQueue.isEmpty();
}

void SerialPort::quit()
{
    qDebug() << "SerialPort::quit called";
    runEnabled = false;
}
