#ifndef CORE_H
#define CORE_H

#include <QTimer>
#include <QThread>
#include <QObject>

#include "serialport.h"

class Core : public QThread
{
    Q_OBJECT

    SerialPort *serial = nullptr;
    bool runEnabled = true;

    void updateSerialPortNames();

public:
    Core();
    ~Core();

    void run() override;

    SerialPort *getSerial();

public slots:
    void quit();
};

#endif // CORE_H
