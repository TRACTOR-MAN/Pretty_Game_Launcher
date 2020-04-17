#ifndef GAME_DESCRIPTION_EDIT_H
#define GAME_DESCRIPTION_EDIT_H

#include <QDialog>

namespace Ui {
class game_description_edit;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             This class defines the dialog window for editing a game's description
 *
 *  \note      Part of this class is automatically generated
 *             using the meta object compiler.
 */
class game_description_edit : public QDialog
{
    Q_OBJECT

public:
    explicit game_description_edit(QWidget *parent = nullptr);
    ~game_description_edit();

    void updateDispGameDescription( const QString &text );

private:
    Ui::game_description_edit *ui;

public slots:
    void acceptButtonPressed(  );

signals:
    void updateGameDescription( const QString &text );
};

#endif // GAME_DESCRIPTION_EDIT_H
