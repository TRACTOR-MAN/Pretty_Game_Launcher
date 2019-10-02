#include <QMainWindow>
#include "main_window.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Set up the main window based upon the form.
    ui->setupUi(this);

    // This is how to set a background image for a widget
    ui->centralWidget->setStyleSheet(
                                     "#centralWidget { \
                                      border-image: url(\"/mnt/SSD_Games/ROMs/PS3/BLUS-30036/PS3_GAME/PIC1.PNG\") 0 0 0 0 stretch stretch; \
                                      }"
                                    );
                                    
    ui->commandLinkButton->setStyleSheet( 
                                         "#commandLinkButton { \
                                          background-color: pink \
                                          }"
                                        );

    ui->menuBar->setStyleSheet          ( 
                                         "#menuBar { \
                                          background-color: blue \
                                          }"
                                        
                                        );
    
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
