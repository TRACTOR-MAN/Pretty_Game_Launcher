#include <QMainWindow>
#include "main_window.h"
#include "ui_mainwindow.h"
#include <iostream>

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

// My first slot, that works.
void MainWindow::CustomFunction( void )
{
    std::cout << "hello world" << std::endl;
}
