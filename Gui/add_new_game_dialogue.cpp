#include <QtCore>
#include <QMessageBox>

#include "add_new_game_dialogue.h"
#include "ui_add_new_game_dialogue.h"
#include "sqliteDbAccess.h"

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
    gameIconFileDialog(nullptr),
    gameWallpaperFileDialog(nullptr),
    gameScreenshotFileDialog(nullptr),
    fileDialogStartDir( new QString )
{
    ui->setupUi(this);
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      18/04/2020
 *
 *  \par       Description:
 *             Member function for returning a pointer to the ui.
 */
Ui::Add_New_Game_Dialogue * Add_New_Game_Dialogue::returnUIPointer( void )
{
    return ui;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      18/04/2020
 *
 *  \par       Description:
 *             Member functrion for updating the file start directory
 */
void Add_New_Game_Dialogue::setStartFileDirectory( QString &dir )
{
    *fileDialogStartDir = dir;
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

    // Set the start directory
    if( *fileDialogStartDir != "\0" )
    {
        gameIconFileDialog->setDirectory( *fileDialogStartDir );
    }
    else
    {
        // Do nothing
    }

    // Show the file dialog
    gameIconFileDialog->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      30/04/2020
 *
 *  \par       Description:
 *             Member functrion for searching for a game wallpaper.
 */
void Add_New_Game_Dialogue::searchForGameWallpaper( )
{
    if( gameWallpaperFileDialog == nullptr )
    {
        gameWallpaperFileDialog = new( QFileDialog );
        // Ensure that file open events are connected to a callback function
        connect( gameWallpaperFileDialog, SIGNAL(fileSelected( QString )), this, SLOT(updateGameWallpaper( QString )) );
    }

    // Set the start directory
    if( *fileDialogStartDir != "\0" )
    {
        gameWallpaperFileDialog->setDirectory( *fileDialogStartDir );
    }
    else
    {
        // Do nothing
    }

    // Show the file dialog
    gameWallpaperFileDialog->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      30/04/2020
 *
 *  \par       Description:
 *             Member functrion for searching for a game screenshot.
 */
void Add_New_Game_Dialogue::searchForGameScreenshot( )
{
    if( gameScreenshotFileDialog == nullptr )
    {
        gameScreenshotFileDialog = new( QFileDialog );
        // Ensure that file open events are connected to a callback function
        connect( gameScreenshotFileDialog, SIGNAL(fileSelected( QString )), this, SLOT(updateGameScreenshot( QString )) );
    }

    // Set the start directory
    if( *fileDialogStartDir != "\0" )
    {
        gameScreenshotFileDialog->setDirectory( *fileDialogStartDir );
    }
    else
    {
        // Do nothing
    }

    // Show the file dialog
    gameScreenshotFileDialog->show( );
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
 *  \date      30/04/2020
 *
 *  \par       Description:
 *             Member functrion for updating the game wallpaper.
 */
void Add_New_Game_Dialogue::updateGameWallpaper( const QString selectedFile )
{
    // Emit the textChanged signal, passing in the selected file.
    emit gameWallpaperTextChanged( selectedFile );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      30/04/2020
 *
 *  \par       Description:
 *             Member functrion for updating the game screenshot.
 */
void Add_New_Game_Dialogue::updateGameScreenshot( const QString selectedFile )
{
    // Emit the textChanged signal, passing in the selected file.
    emit gameScreenshotTextChanged( selectedFile );
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
    ui->launchCommand->setPlainText("\0");
    ui->commandLineArgs->setText("\0");
    ui->gameDescription->setPlainText("\0");
    ui->gameWallpaper->setText("\0");
    ui->gameScreenshot->setText("\0");
    ui->youtubeID->setText("\0");
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
    delete fileDialogStartDir;

    if( gameIconFileDialog != nullptr )
    {
        delete gameIconFileDialog;
    }
}
