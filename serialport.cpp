#include "serialport.h"


SerialPort::SerialPort()
{
    qDebug() << "SerialPort::constructor called";
}

void SerialPort::run()
{
    qDebug() << "SerialPort::run begin";

    serial = new QSerialPort;

    sheller_t shell;
    sheller_init(&shell);

    while(runEnabled) {
        if (serial->isOpen()) {
            if (!transmittQueue.isEmpty()) {
                QByteArray txData = transmittQueue.first();
                transmittQueue.pop_front();

                qDebug() << "Data to send: " << txData.toHex('.');
                uint8_t wrapperedDataBuff[SHELLER_PACKAGE_LENGTH] = {0};
                sheller_wrap(&shell, (uint8_t*)txData.data(), txData.size(), wrapperedDataBuff);
                QByteArray wrapperedData((char*)wrapperedDataBuff, SHELLER_PACKAGE_LENGTH);
                qDebug() << "Wrappered data: " << wrapperedData.toHex('.');

                serial->write(wrapperedData);
                serial->waitForBytesWritten(1);
            }

            if (serial->bytesAvailable() > 0) {
                serial->waitForReadyRead(1);
                QByteArray receiveData = serial->readAll();

                for (int i = 0; i < receiveData.size(); ++i) {
                    sheller_push(&shell, receiveData[i]);
                }
            }


            uint8_t receivedDataBuff[SHELLER_USEFULL_DATA_LENGTH] = {0};
            if (sheller_read(&shell, receivedDataBuff)) {
                QByteArray receivedData((char*)receivedDataBuff, SHELLER_USEFULL_DATA_LENGTH);
                qDebug() << "Received data: " << receivedData.toHex('.');
                receiveQueue.push_back(receivedData);
            }
        }

        QThread().currentThread()->msleep(1);
    }

    qDebug() << "SerialPort::run end";
}

bool SerialPort::connectTo(QString portName, QString portSpeed)
{
    qDebug() << "connectTo " << portName << " ," << portSpeed;
    serial->setPortName(portName);
    serial->setBaudRate(portSpeed.toInt());
    return serial->open(QIODevice::ReadWrite);
}

void SerialPort::disconnect()
{
    serial->clear();
    serial->close();
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
