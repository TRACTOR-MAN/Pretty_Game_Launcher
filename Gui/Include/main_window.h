#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

// Forward decleration of the MainWindow class created in the form,
// confusingly, it has the same name as our MainWindow class.
namespace Ui 
{
    class MainWindow;
}

// Forward decleration of the Add New Game Dialogue Class
class Add_New_Game_Dialogue;

/*! 
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      04/10/2019
 * 
 *  \par       Description:
 *             This class defines the main window for the game launcher applicaiton.
 * 
 *  \note      Part of this class is automatically generated 
 *             using the meta object compiler.
 */
class MainWindow : public QMainWindow
{
    // Macro to allow the QT meta object compiler to convert this 
    // class allong with the associated form to machine generated code.
    Q_OBJECT

    public:
        // The explicit keyword here, prevents an object from being created
        // with the wrong type passed in, it prevents implicit type casting.
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    // This custom keyword allows the QT meta object compiler to 
    // be aware of the slots
    private slots:
        // This member function is called when the Add New Game toolbar button 
        // is pressed. 
        void on_actionAdd_New_Game_triggered( );

    private:
        Ui::MainWindow * ui;
        Add_New_Game_Dialogue * addNewGame;
};

#endif // MAIN_WINDOW_H
