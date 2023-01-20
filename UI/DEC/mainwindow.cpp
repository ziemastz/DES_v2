#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_versionApp->setText(QApplication::applicationVersion());
    ui->label_currentDate->setText(QDateTime::currentDateTime().toString("dddd, d MMMM yyyy"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


