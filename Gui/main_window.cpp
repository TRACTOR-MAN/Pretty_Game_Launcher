#include <QMainWindow>
#include "main_window.h"
#include "ui_mainwindow.h"
#include "add_new_game_dialogue.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    addNewGame(nullptr)
{
    // Set up the main window based upon the form.
    ui->setupUi( this );

    // Fill the screen from start up
    this->showMaximized( );

    // Need to ensure this opens up in screen one    
}

MainWindow::~MainWindow()
{
    // Delete this instance of the UI
    delete ui;
    // Delete our instance of Add_New_Game_Dialogue
    delete addNewGame;
}

void MainWindow::on_actionAdd_New_Game_triggered()
{
    // Take some memory from the heap and create a new instance of addNewGame
    // If we dont do it this way, the dialoge gets trashed on the stack as soon
    // as MainWindow::on_actionAdd_New_Game_triggered goes out of scope
    addNewGame = new(Add_New_Game_Dialogue);

    addNewGame->show();
}
