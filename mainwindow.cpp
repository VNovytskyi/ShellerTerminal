#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    core = new Core();
    core->start();

    updateSerialPortsFuture = QtConcurrent::run(this, &MainWindow::updateSerialPortsNames);
}

MainWindow::~MainWindow()
{
    continueUpdatedSerialPorts = false;
    updateSerialPortsFuture.waitForFinished();

    core->quit();
    core->wait();

    delete core;
    delete ui;
}

void MainWindow::on_serialButton_clicked()
{
    if (core->getSerial()->connectTo(ui->serialName_ComboBox->currentText(), ui->serialSpeed_ComboBox->currentText())) {
        qDebug() << "SerialPorts successffull open";
    } else {
        qDebug() << "SerialPorts cannot open";
    }
}

void MainWindow::updateSerialPortsNames()
{
    while(continueUpdatedSerialPorts) {
        static clock_t time = clock();
        if ((clock() - time) >= 1000) {
            time = clock();
            auto info = QSerialPortInfo::availablePorts();
            QList<QString> currentPortsNames;
            for (auto &el: info) {
                currentPortsNames.push_back(el.portName());
            }

            if (currentPortsNames != portsNames) {
                qDebug() << "Changed";
                portsNames = currentPortsNames;
                ui->serialName_ComboBox->clear();
                if (currentPortsNames.size() > 0) {
                    ui->serialName_ComboBox->addItems(currentPortsNames);
                    ui->serialName_ComboBox->setCurrentIndex(0);
                }
            }
        }
        QThread().currentThread()->msleep(1);
    }
}
