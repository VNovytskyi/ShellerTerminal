#ifndef CORE_H
#define CORE_H

#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QObject>

#include "../../Libs/serial/serial.h"

class Core : public QObject
{
    Q_OBJECT

    bool loopEnabled = true;

    Serial  *serial = nullptr;
    QThread serialThread;

public:
    Core();
    ~Core();

    void loop();
    Serial *getSerial();

public slots:
    void disableLoop();

signals:
    void appendReceivedData(QByteArray data);
};

#endif // CORE_H
