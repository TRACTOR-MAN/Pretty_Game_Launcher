#include <QMainWindow>
#include "main_window.h"
#include "ui_mainwindow.h"
#include "add_new_game_dialogue.h"
#include "sqliteDbAccess.h"

/****************************************************************************
  __  __    _    ___  _  _  __      __ ___  _  _  ___    ___ __      __
 |  \/  |  /_\  |_ _|| \| | \ \    / /|_ _|| \| ||   \  / _ \\ \    / /
 | |\/| | / _ \  | | | .` |  \ \/\/ /  | | | .` || |) || (_) |\ \/\/ /
 |_|  |_|/_/ \_\|___||_|\_|   \_/\_/  |___||_|\_||___/  \___/  \_/\_/

 ***************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    // For my own reference, the below line ensures that the QMainWindow
    // Constructor, with the &QWidget arguement is called :-) 
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
    if( addNewGame == nullptr )
    {
        addNewGame = new(Add_New_Game_Dialogue);
    }

    addNewGame->show();
}
