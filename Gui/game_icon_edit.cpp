#include <QDebug>

#include "game_icon_edit.h"
#include "ui_game_icon_edit.h"

// Static fileDialog variable decleration
QFileDialog *game_icon_edit::fileDialog = nullptr;

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Constructor for the game_icon_edit class.
 */
game_icon_edit::game_icon_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game_icon_edit),
    desFileStartPos( new QString )
{
    ui->setupUi(this);
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Member function for openning a file dialog.
 */
void game_icon_edit::openFileDialog( )
{
    if( fileDialog == nullptr )
    {
        fileDialog = new QFileDialog;
        connect( fileDialog, SIGNAL( fileSelected( const QString& ) ), this, SLOT( gameIconFileAccepted( const QString& ) ) );
    }
    else
    {
        // Do nothing
    }

    // Strip the directory from the file path
    QFileInfo fullStartPath( *desFileStartPos );
    QString fileName( fullStartPath.fileName( ) );
    QString startDirectory( *desFileStartPos );
    startDirectory.remove( ( desFileStartPos->size() - fileName.size() ), fileName.size() );

    // Set the start position for the file dialog
    fileDialog->setDirectory( startDirectory );

    // Show the file dialog
    fileDialog->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Member function for setting the text in the line edit.
 */
void game_icon_edit::setGameIconText( const QString& text  )
{
    ui->lineEdit->setText( text );
    *desFileStartPos = text;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Member function for logging an accepted new icon
 */
void game_icon_edit::gameIconFileAccepted( const QString& text )
{
    ui->lineEdit->setText( text );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Member function for logging a user accept button press.
 */
void game_icon_edit::okButtonPressed( )
{
    emit gameIconUpdated( ui->lineEdit->text() );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Destructor for the game_icon_edit class.
 */
game_icon_edit::~game_icon_edit()
{
    delete ui;
    delete desFileStartPos;
}
