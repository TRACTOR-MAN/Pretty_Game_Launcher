#include "launch_command_edit.h"
#include "ui_launch_command_edit.h"

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Constructor for the launch_command_edit class.
 */
launch_command_edit::launch_command_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::launch_command_edit)
{
    ui->setupUi(this);

    // Connect the signal to the slot for updating plain text
    connect( ui->buttonBox, SIGNAL( accepted( )), this, SLOT(  acceptButtonPressed( ) ) );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Member function for updating the displayed launch command.
 */
void launch_command_edit::updateDispLaunchCommand( const QString &text )
{
    ui->plainTextEdit->setPlainText( text );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Member function for updating the displayed launch command.
 */
void launch_command_edit::acceptButtonPressed( )
{
    emit updateLaunchCommand( ui->plainTextEdit->toPlainText() );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Destructor for the launch_command_edit class.
 */
launch_command_edit::~launch_command_edit()
{
    delete ui;
}
