#ifndef ADD_NEW_GAME_DIALOGUE_H
#define ADD_NEW_GAME_DIALOGUE_H

#include <QDialog>
#include <QFileDialog>
#include "game_data_gui.h"
#include "ui_add_new_game_dialogue.h"

namespace Ui 
{
    class Add_New_Game_Dialogue;
}

/*! 
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      07/10/2019
 * 
 *  \par       Description:
 *             This class defines the add new game dialogue for the game launcher applicaiton.
 * 
 *  \note      Part of this class is automatically generated 
 *             using the meta object compiler.
 */
class Add_New_Game_Dialogue : public QDialog
{
    Q_OBJECT

public:
    explicit Add_New_Game_Dialogue( QWidget *parent = nullptr );
    ~Add_New_Game_Dialogue( );

    // Static function for setting the lclDatabase variable
    static void setLclData( gameDataGuiWidget * const psd_gui_data );
    // Function for returning a pointer to the ui
    Ui::Add_New_Game_Dialogue * returnUIPointer( void );
    // Function for setting the start directory of the file dialog
    void setStartFileDirectory( QString &dir );

public slots:
    // Function for clearing all dialog elements
    void clearDialogueElements( );

private slots:
    void searchForGameIcon( );
    void updateGameIcon( const QString selectedFile );

signals:
    void gameIconTextChanged( const QString newString );

private:
    Ui::Add_New_Game_Dialogue * ui;
    QFileDialog *gameIconFileDialog;
    static gameDataGuiWidget *lclGui;
    QString *fileDialogStartDir;
};

#endif // ADD_NEW_GAME_DIALOGUE_H
