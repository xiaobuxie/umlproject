#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Virus_Area_Widget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    (new Virus_Area_Widget())->show();
}
