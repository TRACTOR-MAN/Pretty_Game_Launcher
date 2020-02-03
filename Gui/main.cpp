#include "main_window.h"
#include <QApplication>
#include "sqliteDbAccess.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow window;
    window.show();

    // Initialise the connection to the sqlite database
    sqLiteDbInterface my_games_database;
    my_games_database.readGameGuiInformation( );

    return application.exec();
}

