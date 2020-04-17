#ifndef CMD_LINE_ARGS_EDIT_H
#define CMD_LINE_ARGS_EDIT_H

#include <QDialog>


namespace Ui {
class cmd_line_args_edit;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             This class defines the dialog window for editing a game's command line args
 *
 *  \note      Part of this class is automatically generated
 *             using the meta object compiler.
 */
class cmd_line_args_edit : public QDialog
{
    Q_OBJECT

public:
    explicit cmd_line_args_edit(QWidget *parent = nullptr);
    ~cmd_line_args_edit();

    void setCmdLineArgsText( QString &text );

signals:
    void updateCmdLineArgs( const QString &string );

private slots:
    void acceptButtonPressed(  );

private:
    Ui::cmd_line_args_edit *ui;
};

#endif // CMD_LINE_ARGS_EDIT_H
