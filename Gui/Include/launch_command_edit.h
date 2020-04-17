#ifndef LAUNCH_COMMAND_EDIT_H
#define LAUNCH_COMMAND_EDIT_H

#include <QDialog>

namespace Ui {
class launch_command_edit;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             This class defines the dialog window for editing a game's launch command
 *
 *  \note      Part of this class is automatically generated
 *             using the meta object compiler.
 */
class launch_command_edit : public QDialog
{
    Q_OBJECT

public:
    explicit launch_command_edit(QWidget *parent = nullptr);
    ~launch_command_edit();

    void updateDispLaunchCommand( const QString &text );

private:
    Ui::launch_command_edit *ui;

public slots:
    void acceptButtonPressed(  );

signals:
    void updateLaunchCommand( const QString &text );
};

#endif // LAUNCH_COMMAND_EDIT_H
