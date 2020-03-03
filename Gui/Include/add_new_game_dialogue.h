#ifndef ADD_NEW_GAME_DIALOGUE_H
#define ADD_NEW_GAME_DIALOGUE_H

#include <QDialog>
#include <QFileDialog>

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

    private slots:
        void searchForLaunchScript( );
        void searchForGameIcon( );
        void updateLaunchScript( const QString selectedFile );
        void updateGameIcon( const QString selectedFile );
    
    signals:
        void launchScriptTextChanged( const QString newString );
        void gameIconTextChanged( const QString newString );

    private:
        Ui::Add_New_Game_Dialogue * ui;
        QFileDialog *launchScriptFileDialog;
        QFileDialog *gameIconFileDialog;

};

#endif // ADD_NEW_GAME_DIALOGUE_H
