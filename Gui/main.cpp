#include "main_window.h"

#include <QApplication>

#include "game_data_gui.h"


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // Create an instance of the MainWindow class
    MainWindow window;
    // Create an instance of the game data GUI widget
    gameDataGuiWidget gameDataWidget( window );

    // Set the gameData widget as the central widget
    window.setCentralWidget(&gameDataWidget);

    // Show the window
    window.show();

    return application.exec();
}

