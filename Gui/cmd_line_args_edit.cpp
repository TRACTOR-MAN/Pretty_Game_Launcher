#include "cmd_line_args_edit.h"
#include "ui_cmd_line_args_edit.h"

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Constructor for the cmd_line_args_edit class.
 */
cmd_line_args_edit::cmd_line_args_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cmd_line_args_edit)
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
void cmd_line_args_edit::setCmdLineArgsText( QString &text )
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
void cmd_line_args_edit::acceptButtonPressed(  )
{
    emit updateCmdLineArgs( ui->lineEdit->text() );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Destructor for the cmd_line_args_edit class.
 */
cmd_line_args_edit::~cmd_line_args_edit()
{
    delete ui;
}
