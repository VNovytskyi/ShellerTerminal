#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QDebug>
#include <QThread>
#include <QObject>
#include <QByteArray>
#include <QSerialPort>
#include <QQueue>

#include "Sheller/Source/sheller.h"

class SerialPort : public QThread
{
    Q_OBJECT

    bool runEnabled = true;
    QSerialPort *serial = nullptr;

    QQueue<QByteArray> receiveQueue;
    QQueue<QByteArray> transmittQueue;

public:
    SerialPort();

    void run() override;
    bool connectTo(QString portName, QString portSpeed);
    void disconnect();

    QByteArray read();
    bool write(QByteArray &data);
    bool isEmpty();

public slots:
    void quit();
};

#endif // SERIALPORT_H
