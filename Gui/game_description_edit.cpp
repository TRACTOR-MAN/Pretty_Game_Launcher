#include "game_description_edit.h"
#include "ui_game_description_edit.h"

#include <QDebug>

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Constructor for the game_description_edit class.
 */
game_description_edit::game_description_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game_description_edit)
{
    ui->setupUi(this);

    // Connect the signal to the slot for updating plain text
    connect( ui->buttonBox, SIGNAL( accepted( )), this, SLOT( acceptButtonPressed( ) ) );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Member function for updating the displayed game description.
 */
void game_description_edit::updateDispGameDescription( const QString &text )
{
    ui->plainTextEdit->setPlainText( text );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Member function for updating the displayed game description.
 */
void game_description_edit::acceptButtonPressed( )
{
    emit updateGameDescription( ui->plainTextEdit->toPlainText() );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Destructor for the launch_command_edit class.
 */
game_description_edit::~game_description_edit()
{
    delete ui;
}
