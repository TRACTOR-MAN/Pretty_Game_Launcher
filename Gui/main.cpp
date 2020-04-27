#include "main_window.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

#include "sqliteDbAccess.h"
#include "add_new_game_dialogue.h"
#include "game_data_gui.h"
#include "main.h"

/*******************************************************************************
                      ___  ___  ___ __   __ _  _____  ___
                     | _ \| _ \|_ _|\ \ / //_\|_   _|| __|
                     |  _/|   / | |  \ V // _ \ | |  | _|
                     |_|_ |_|_\|___|  \_//_/ \_\|_|_ |___|
                     |   \ | __|| __||_ _|| \| || __|/ __|
                     | |) || _| | _|  | | | .` || _| \__ \
                     |___/ |___||_|  |___||_|\_||___||___/
*******************************************************************************/
/*******************************************************************************
                             __  __    _    ___  _  _
                            |  \/  |  /_\  |_ _|| \| |
                            | |\/| | / _ \  | | | .` |
                            |_|  |_|/_/ \_\|___||_|\_|
*******************************************************************************/
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
    application_theme_c theme( DARK, application );

    // Create an instance of the MainWindow class
    MainWindow window( theme );

    // Create a handle and interface to the sqlite database
    sqLiteDbInterface myDatabase( &window );

    // Create an instance of the game data GUI widget
    gameDataGuiWidget gameDataWidget( myDatabase, window, theme );

    // Set the reference variable to the gui in the main window
    window.setLclGuiWidget( gameDataWidget );

    // Set the gameData widget as the central widget
    window.setCentralWidget( &gameDataWidget );

    // Show the window
    window.show();

    // Excecute the application
    return application.exec();
}

/*******************************************************************************
                      _____  _  _  ___  ___  __  __  ___
                     |_   _|| || || __|| __||  \/  || __|
                       | |  | __ || _| | _| | |\/| || _|
                       |_|  |_||_||___||___||_|  |_||___|
*******************************************************************************/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      16/02/2020
 *
 *  \par       Description:
 *             Constructor for the application_theeme_c class
 */
application_theme_c::application_theme_c( application_themes_et desired_initial_theme_e, QApplication &psd_application ) :
    application( psd_application )
{
    setupTheme( desired_initial_theme_e );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      16/02/2020
 *
 *  \par       Description:
 *             This member function sets up the theme for the application
 */
void application_theme_c::setupTheme ( application_themes_et desired_theeme_e )
{
    if( desired_theeme_e == DARK )
    {
        QFile file(":/dark.qss");
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream stream(&file);
        application.setStyleSheet(stream.readAll());
    }
    else
    {
        QFile file(":/light.qss");
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream stream(&file);
        application.setStyleSheet(stream.readAll());
    }

    // Update the current theme
    current_theme_e = desired_theeme_e;
}
