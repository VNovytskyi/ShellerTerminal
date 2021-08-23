#ifndef CORE_H
#define CORE_H

#include <QThread>
#include <QObject>

class Core : public QThread
{
    Q_OBJECT

    bool runEnabled = true;

public:
    Core();

    void run() override;

public slots:
    void quit();
};

#endif // CORE_H
