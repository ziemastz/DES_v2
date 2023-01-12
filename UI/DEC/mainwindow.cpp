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


void MainWindow::on_pushButton_dashboard_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_nuclide_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

