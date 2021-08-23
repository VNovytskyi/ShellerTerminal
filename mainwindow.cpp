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
}

MainWindow::~MainWindow()
{
    core->quit();
    core->wait();

    delete core;
    delete ui;
}

void MainWindow::on_serialButton_clicked()
{
    qDebug() << "Connect button clicked";
}
