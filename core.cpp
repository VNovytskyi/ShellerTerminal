#include "core.h"

#include <QDebug>
#include <QThread>

Core::Core()
{
    qDebug() << "Core::constructor called";
}

void Core::run()
{
    qDebug() << "Core::run begin";

    while(runEnabled) {
        QThread().currentThread()->msleep(1000);
        qDebug() << "Core::run work";
    }

    qDebug() << "Core::run end";
}

void Core::quit()
{
    qDebug() << "Core::quit called";
    runEnabled = false;
}
