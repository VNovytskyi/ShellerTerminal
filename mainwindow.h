#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent/QtConcurrent>

#include "core.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Core *core = nullptr;
    QThread coreThread;


    QList<QString> portsNames;
    bool continueUpdatedSerialPorts = true;
    QFuture<void> updateSerialPortsFuture;
    void updateSerialPortsNames();

    void configApp();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_serialButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_clearButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

public slots:
    void displayData(QByteArray data);

private:
    Ui::MainWindow *ui;

signals:
};
#endif // MAINWINDOW_H
