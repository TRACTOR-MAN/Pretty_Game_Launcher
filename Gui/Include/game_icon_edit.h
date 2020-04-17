#ifndef GAME_ICON_EDIT_H
#define GAME_ICON_EDIT_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class game_icon_edit;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             This class defines the dialog window for editing a game icon
 *
 *  \note      Part of this class is automatically generated
 *             using the meta object compiler.
 */
class game_icon_edit : public QDialog
{
    Q_OBJECT

public:
    explicit game_icon_edit(QWidget *parent = nullptr);
    ~game_icon_edit( );

    // Function for setting the text in the line edit
    void setGameIconText( const QString& text );

private:
    Ui::game_icon_edit *ui;
    QString *desFileStartPos;
    static QFileDialog *fileDialog;

private slots:
    // Member function for openning a file dialog
    void openFileDialog( );
    // Slot function for triggering a game icon changed event
    void gameIconFileAccepted( const QString& text );
    // Slot function for triggering when the user has pressed the OK button
    void okButtonPressed( );


signals:
    void gameIconUpdated( const QString& text );
};

#endif // GAME_ICON_EDIT_H
