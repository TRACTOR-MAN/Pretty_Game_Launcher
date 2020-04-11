#include <QtCore>
#include <QMessageBox>

#include "add_new_game_dialogue.h"
#include "ui_add_new_game_dialogue.h"
#include "sqliteDbAccess.h"

/***************************************************************************
  ___  _____  _  _____  ___  ___   __  __  ___  __  __  ___  ___  ___
 / __||_   _|/_\|_   _||_ _|/ __| |  \/  || __||  \/  || _ )| __|| _ \
 \__ \  | | / _ \ | |   | || (__  | |\/| || _| | |\/| || _ \| _| |   /
 |___/  |_|/_/_\_\|_|  |___|\___| |_|__|_||___||_|_ |_||___/|___||_|_\
 |   \ | __|/ __|| |   | __|  /_\  | _ \  /_\|_   _||_ _|/ _ \ | \| |
 | |) || _|| (__ | |__ | _|  / _ \ |   / / _ \ | |   | || (_) || .` |
 |___/ |___|\___||____||___|/_/ \_\|_|_\/_/ \_\|_|  |___|\___/ |_|\_|
 **************************************************************************/
sqLiteDbInterface *Add_New_Game_Dialogue::lclDatabase = nullptr;

/***************************************************************************
     _    ___   ___    _  _  ___ __      __   ___    _    __  __  ___
    /_\  |   \ |   \  | \| || __|\ \    / /  / __|  /_\  |  \/  || __|
   / _ \ | |) || |) | | .` || _|  \ \/\/ /  | (_ | / _ \ | |\/| || _|
  /_/ \_\|___/ |___/  |_|\_||___|  \_/\_/    \___|/_/ \_\|_|  |_||___|
 **************************************************************************/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      03/03/2020
 *
 *  \par       Description:
 *             Constructor for the Add_New_Game_Dialogue class
 */
Add_New_Game_Dialogue::Add_New_Game_Dialogue( QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::Add_New_Game_Dialogue),
    launchScriptFileDialog(nullptr),
    gameIconFileDialog(nullptr)
{
    ui->setupUi(this);
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      11/04/2020
 *
 *  \par       Description:
 *             Static function for setting the status of the lclDatabase variable
 */
void Add_New_Game_Dialogue::setLclDatabase( sqLiteDbInterface * const psd_database )
{
    lclDatabase = psd_database;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      03/03/2020
 *
 *  \par       Description:
 *             Member functrion for searching for a launch script.
 */
void Add_New_Game_Dialogue::searchForLaunchScript( )
{
    if( launchScriptFileDialog == nullptr )
    {
        launchScriptFileDialog = new( QFileDialog );
        // Ensure that file open events are connected to a callback function
        connect( launchScriptFileDialog, SIGNAL(fileSelected( QString )), this, SLOT(updateLaunchScript( QString )) );
    }

    // Show the file dialog
    launchScriptFileDialog->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      03/03/2020
 *
 *  \par       Description:
 *             Member functrion for updating the launch script.
 */
void Add_New_Game_Dialogue::updateLaunchScript( const QString selectedFile )
{
    // Emit the textChanged signal, passing in the selected file.
    emit launchScriptTextChanged( selectedFile );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      03/03/2020
 *
 *  \par       Description:
 *             Member functrion for searching for a game icon.
 */
void Add_New_Game_Dialogue::searchForGameIcon( )
{
    if( gameIconFileDialog == nullptr )
    {
        gameIconFileDialog = new( QFileDialog );
        // Ensure that file open events are connected to a callback function
        connect( gameIconFileDialog, SIGNAL(fileSelected( QString )), this, SLOT(updateGameIcon( QString )) );
    }

    // Show the file dialog
    gameIconFileDialog->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      03/03/2020
 *
 *  \par       Description:
 *             Member functrion for updating the game icon.
 */
void Add_New_Game_Dialogue::updateGameIcon( const QString selectedFile )
{
    // Emit the textChanged signal, passing in the selected file.
    emit gameIconTextChanged( selectedFile );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      11/04/2020
 *
 *  \par       Description:
 *             Member function for adding a new game to the game launcher database
 */
void Add_New_Game_Dialogue::addNewGameToDbc( )
{
    bool okToAddNewGame_b = true;

    // Check whether a Game Title has been entered
    if( ui->gameTitle->text() == "\0" )
    {
        okToAddNewGame_b = false;
    }
    else
    {
        // Do nothing
    }

    // Check whether a launch script or launch command has been entered
    if(
        ( ui->launchScript->text() == "\0" )
        &&
        ( ui->launchCommand->toPlainText() == "\0" )
      )
    {
        okToAddNewGame_b = false;
    }
    else
    {
        // Do nothing
    }

    // Check whether a game description has been provided
    if( ui->gameDescription->toPlainText() == "\0" )
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
        lclDatabase->addNewGame(
                                 ui->gameTitle->text(),
                                 ui->launchScript->text(),
                                 ui->launchCommand->toPlainText(),
                                 ui->gameDescription->toPlainText(),
                                 ui->gameIcon->text(),
                                 parentWidget()
                               );

        // Clear dialogue elements
        clearDialogueElements( );
    }
    else
    {
        // Message pop up to the application
        QMessageBox::warning( parentWidget(), "Pretty Game Launcher", "All inputs not populated, ensure that Game Title, a Launch Script or command, and the Game description are populated" );
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      03/03/2020
 *
 *  \par       Description:
 *             Member function for clearing the game dialogue elements
 */
void Add_New_Game_Dialogue::clearDialogueElements( )
{
    ui->gameTitle->setText("\0");
    ui->gameIcon->setText("\0");
    ui->launchScript->setText("\0");
    ui->launchCommand->setPlainText("\0");
    ui->gameDescription->setPlainText("\0");
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      03/03/2020
 *
 *  \par       Description:
 *             destructor for the Add_New_Game_Dialogue class.
 */
Add_New_Game_Dialogue::~Add_New_Game_Dialogue( )
{
    delete ui;

    if( launchScriptFileDialog != nullptr )
    {
        delete launchScriptFileDialog;
    }

    if( gameIconFileDialog != nullptr )
    {
        delete gameIconFileDialog;
    }
}
