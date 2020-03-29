#include <QtSql>
#include <iostream>

#include <QMessageBox>
#include "sqliteDbAccess.h"

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      05/02/2020
 *
 *  \par       Description:
 *             Constructor for the sqLiteDbInterface class
 */
sqLiteDbInterface::sqLiteDbInterface( QWidget *parent ) :
    my_db( new( QSqlDatabase ) )
{
    // The directory where the database is to be stored
    const QString db_path("..//..//Config//game_data.db");

    // Before we do anything, check that the sqlite driver is available
    if( QSqlDatabase::isDriverAvailable("QSQLITE") )
    {
        // we are using the sqlite driver
        *my_db = QSqlDatabase::addDatabase( "QSQLITE" );

        // point to our game database
        my_db->setDatabaseName( db_path );

        // Check if the database connection is good
        bool connection_good_b = my_db->open( );

        // Provide some debug on the connection.
        if( connection_good_b == false )
        {
            // It is likely that the pretty_game_launcher excecutable is in the incorrect location
            qDebug() << "Connection to database bad, check that the executable is located"
                     << db_path
                     << " from game_data.db\n";

            // Message pop up to the application
            QMessageBox::warning( parent, "Pretty Game Launcher", "Bad Database Connection, run application from command line for more information");

            // abort.... abort....
            qWarning() << my_db->lastError() << "\n";
        }
        else
        {
            // Good connection!
            std::cout << "Connection to database good" << std::endl;
        }

        // Call the create table command, this ensures that the database is created, if it doesn't already exist
        QSqlQuery query;
        query.exec( "CREATE TABLE \"GameLaunchData\" (\"gameName\" TEXT NOT NULL, \"gameIconPath\" TEXT, \"launchCommand\"	TEXT, \"launchScript\" TEXT, \"gameDescription\" TEXT NOT NULL, \"playTime\" TEXT)");

        // Read GUI related information from the sqlite database
        readGameGuiInformation( );
    }
    // The sqlite driver is not available
    else
    {
        // The driver is not available
        qFatal( "SQLITE driver not available, check .pro file, and SQL libraries are available" );
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      05/02/2020
 *
 *  \par       Description:
 *             Member function of the readGameGuiInformation class for reading GUI
 *             information from the sqlite database.
 */
void sqLiteDbInterface::readGameGuiInformation( )
{
    // Query the database for the information to display
    QSqlQuery query;
    query.prepare("SELECT gameName, gameIconPath, gameDescription, playTime, launchCommand, launchScript FROM GameLaunchData ORDER BY gameName ASC");
    
    // Excecute the query
    if( query.exec( ) == false )
    {
        qDebug() << "Can't excecute query";
    }
    else
    {
        while( query.next( ) != false )
        {
            // Create a new pointer to lcl_GUI_game_information_ps data
            GUI_game_information_st *lcl_GUI_game_information_ps = new( GUI_game_information_st );

            // Store the information in a vector
            lcl_GUI_game_information_ps->gameName = query.value("gameName").toString();
            lcl_GUI_game_information_ps->gameIconPath = query.value("gameIconPath").toString();
            lcl_GUI_game_information_ps->gameDescription = query.value("gameDescription").toString();
            lcl_GUI_game_information_ps->playTime = query.value("playTime").toString();
            lcl_GUI_game_information_ps->LaunchCommand = query.value("launchCommand").toString();
            lcl_GUI_game_information_ps->LaunchScript = query.value("launchScript").toString();

            // Add the data pointer to the vector
            displayData_v.push_back( lcl_GUI_game_information_ps );
        }
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      05/02/2020
 *
 *  \par       Description:
 *             Destructor for the sqLiteDbInterface class.
 */
sqLiteDbInterface::~sqLiteDbInterface( )
{
    for(uint16_t i = 0U; i < displayData_v.size( ); i++)
    {
        delete displayData_v[i];
    }

    delete my_db;
}    
