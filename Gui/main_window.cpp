#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include "main_window.h"
#include "ui_mainwindow.h"
#include "ui_add_new_game_dialogue.h"
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
    last_windowed_state_b(false),
    lclGuiWidget(nullptr)
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
 *             Member function for setting the reference to the game data gui widget
 */
void MainWindow::setLclGuiWidget( gameDataGuiWidget &psdGuiWidget )
{
    lclGuiWidget = &psdGuiWidget;
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

        // Connect the signal to the slot for the dialog
        connect( addNewGame, SIGNAL( accepted( ) ), this, SLOT( addNewGameToDbc( ) ) );
    }

    addNewGame->show();
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      11/04/2020
 *
 *  \par       Description:
 *             Member function for adding a new game to the game launcher database
 */
void MainWindow::addNewGameToDbc( )
{
    bool okToAddNewGame_b = true;

    Ui::Add_New_Game_Dialogue *newGameUi = addNewGame->returnUIPointer( );

    // Check whether a Game Title has been entered
    if( newGameUi->gameTitle->text() == "\0" )
    {
        okToAddNewGame_b = false;
    }
    else
    {
        // Do nothing
    }

    // Check whether a launch command has been entered
    if( newGameUi->launchCommand->toPlainText() == "\0" )
    {
        okToAddNewGame_b = false;
    }
    else
    {
        // Do nothing
    }

    // Check whether a game description has been provided
    if( newGameUi->gameDescription->toPlainText() == "\0" )
    {
        okToAddNewGame_b = false;
    }
    else
    {
        // Do nothing
    }

    // If it is OK to add the new game
    if( okToAddNewGame_b != false )
    {
        if( lclGuiWidget != nullptr )
        {
            lclGuiWidget->AddNewGameToGuiAndDbc(
                                                 newGameUi->gameTitle->text(),
                                                 newGameUi->launchCommand->toPlainText(),
                                                 newGameUi->commandLineArgs->text(),
                                                 newGameUi->gameDescription->toPlainText(),
                                                 newGameUi->gameIcon->text(),
                                                 newGameUi->textColorComboBox->currentText(),
                                                 newGameUi->gameWallpaper->text(),
                                                 newGameUi->gameScreenshot->text(),
                                                 newGameUi->youtubeID->text(),
                                                 this
                                               );

        // Clear dialogue elements
        addNewGame->clearDialogueElements( );
        }
        else
        {
            // Message pop up to the application
            QMessageBox::warning( this, "Pretty Game Launcher", "All inputs not populated, ensure that Game Title, a Launch Command, and the Game description are populated" );
        }
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      13/04/2020
 *
 *  \par       Description:
 *             Slot function for the fullscr toggle toolbar button
 */
void MainWindow::on_actionFullScr_triggered( )
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
