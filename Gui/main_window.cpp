#include <QMainWindow>
#include <QDebug>
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
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      13/04/2020
 *
 *  \par       Description:
 *             Constructor for the MainWindow class
 */
MainWindow::MainWindow(application_theme_c &psdTheme, QWidget *parent) :
    // For my own reference, the below line ensures that the QMainWindow
    // Constructor, with the &QWidget arguement is called :-) 
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    addNewGame(nullptr),
    lclTheme(psdTheme),
    last_windowed_state_b(false)
{
    // Set up the main window based upon the form.
    ui->setupUi( this );

    // Start in normal mode
    showNormal( );

    // Need to ensure this opens up in screen one
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      13/04/2020
 *
 *  \par       Description:
 *             Destructor for the MainWindow class
 */
MainWindow::~MainWindow()
{
    // Delete this instance of the UI
    delete ui;
    // Delete our instance of Add_New_Game_Dialogue
    delete addNewGame;
}


/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      13/04/2020
 *
 *  \par       Description:
 *             Slot function for adding a new game
 */
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

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      13/04/2020
 *
 *  \par       Description:
 *             Slot function for the fullscr toggle toolbar button
 */
void MainWindow::on_actionFullScr_triggered()
{
    if( isFullScreen() == true )
    {
        if( last_windowed_state_b != false )
        {
            showNormal( );
            showMaximized();
        }
        else
        {
            showNormal( );
        }
    }
    else
    {
        last_windowed_state_b = isMaximized();

        showFullScreen( );
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      13/04/2020
 *
 *  \par       Description:
 *             Slot for the theme toggle toolbar function.
 */
void MainWindow::on_actionToggleTheme_triggered()
{
    if( lclTheme.current_theme_e == LIGHT )
    {
        lclTheme.setupTheme( DARK );
    }
    else
    {
        lclTheme.setupTheme( LIGHT );
    }
}
