#ifndef GAME_TITLE_EDIT_H
#define GAME_TITLE_EDIT_H

#include <QDialog>

namespace Ui {
class game_title_edit;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             This class defines the dialog window for editing a game title
 *
 *  \note      Part of this class is automatically generated
 *             using the meta object compiler.
 */
class game_title_edit : public QDialog
{
    Q_OBJECT

public:
    explicit game_title_edit(QWidget *parent = nullptr);
    ~game_title_edit();

    void setGameNameText( QString &text );

signals:
    void gameTitleAccepted( const QString string );

private slots:
    void acceptButtonPressed(  );

private:
    Ui::game_title_edit *ui;
};

#endif // GAME_TITLE_EDIT_H
