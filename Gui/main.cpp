#include "main_window.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

#include "sqliteDbAccess.h"
#include "game_data_gui.h"
#include "main.h"


/****** Prototypes ******/
static void                  setupTheme                   ( QApplication &application );

/****** extern function declerations ******/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      16/02/2020
 *
 *  \par       Description:
 *             Main entry function
 */
int main(int argc, char *argv[])
{
    // Create an application instance
    QApplication application(argc, argv);

    // Set the style sheet for the project
    setupTheme( application );

    // Create an instance of the MainWindow class
    MainWindow window;

    // Create an instance of the game data GUI widget
    gameDataGuiWidget gameDataWidget( window );

    // Set the gameData widget as the central widget
    window.setCentralWidget(&gameDataWidget);

    // Show the window
    window.show();

    // Excecute the application
    return application.exec();
}


/****** static function declerations ******/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      16/02/2020
 *
 *  \par       Description:
 *             This function sets up the theme for the application
 */
static void setupTheme ( QApplication &application )
{
    QFile file(":/dark.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    application.setStyleSheet(stream.readAll());
}
