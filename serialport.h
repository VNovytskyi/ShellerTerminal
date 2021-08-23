#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QThread>
#include <QObject>

class SerialPort : public QThread
{
    Q_OBJECT

    bool runEnabled = true;

public:
    SerialPort();

    void run() override;
    void connectTo(QString portName, QString portSpeed);

public slots:
    void serial_connectTo(QString portName, QString portSpeed);
    void quit();
};

#endif // SERIALPORT_H
