#include "game_title_edit.h"
#include "ui_game_title_edit.h"

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Constructor for the game_title_edit class.
 */
game_title_edit::game_title_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game_title_edit)
{
    ui->setupUi(this);

    // Connect the accept button to the slot
    connect( this, SIGNAL( accepted(  ) ), this, SLOT( acceptButtonPressed( ) ));
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Member function for setting the text in the lineEdit.
 */
void game_title_edit::setGameNameText( QString &text )
{
    this->ui->lineEdit->setText( text );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot function to acknowledge when accept has been pressed.
 */
void game_title_edit::acceptButtonPressed(  )
{
    emit gameTitleAccepted( ui->lineEdit->text() );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Destructor for the game_title_edit class.
 */
game_title_edit::~game_title_edit()
{
    delete ui;
}
