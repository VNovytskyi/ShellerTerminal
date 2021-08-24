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
    QObject::connect(core, &Core::appendReceivedData, this, &MainWindow::displayData);

    updateSerialPortsFuture = QtConcurrent::run(this, &MainWindow::updateSerialPortsNames);

    setWindowIcon(QIcon("ShellerIcon.ico"));
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
    if (ui->serialButton->text() == "Connect") {
        if (core->getSerial()->connectTo(ui->serialName_ComboBox->currentText(), ui->serialSpeed_ComboBox->currentText())) {
            qDebug() << "SerialPorts successffull open";
            ui->serialButton->setText("Disconnect");
        }
    } else {
        core->getSerial()->disconnect();
        ui->serialButton->setText("Connect");
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

void MainWindow::on_pushButton_clicked()
{
    QByteArray testData;
    testData.push_back(12);
    testData.push_back(65);
    testData.push_back(98);
    core->getSerial()->write(testData);
}


void MainWindow::on_pushButton_2_clicked()
{
    QByteArray testData;
    testData.push_back(32);
    testData.push_back(12);
    testData.push_back(24);
    core->getSerial()->write(testData);
}


void MainWindow::on_clearButton_clicked()
{
    ui->transmitHexLine->setText("");
}

void MainWindow::on_pushButton_4_clicked()
{
    QString values = ui->transmitHexLine->text();
    if (values.length()) {
        QStringList valuesList = values.split(QRegExp("\\s+"));

        QByteArray numbers;
        for(auto &el: valuesList) {
            numbers.push_back(el.toUInt());
        }

        core->getSerial()->write(numbers);
    }

}

void MainWindow::displayData(QByteArray data)
{
    ui->textEdit->append(data.toHex('.'));
}

