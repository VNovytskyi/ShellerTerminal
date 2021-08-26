#ifndef CORE_H
#define CORE_H

#include <QTimer>
#include <QThread>
#include <QObject>

#include "serial.h"

class Core : public QThread
{
    Q_OBJECT

    Serial *serial = nullptr;
    bool runEnabled = true;

public:
    Core();
    ~Core();

    void run() override;

    Serial *getSerial();

public slots:
    void quit();

signals:
    void appendReceivedData(QByteArray data);
};

#endif // CORE_H
