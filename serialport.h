#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QDebug>
#include <QThread>
#include <QObject>
#include <QByteArray>
#include <QSerialPort>

class SerialPort : public QThread
{
    Q_OBJECT

    bool runEnabled = true;
    QSerialPort serial;

    QList<QByteArray> receiveQueue;
    QList<QByteArray> transmittQueue;

public:
    SerialPort();

    void run() override;
    bool connectTo(QString portName, QString portSpeed);
    void disconnect();

    QByteArray read();
    void write(QByteArray &data);
    bool isEmpty();

public slots:
    void quit();
};

#endif // SERIALPORT_H
