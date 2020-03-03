#include "add_new_game_dialogue.h"
#include "ui_add_new_game_dialogue.h"

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
