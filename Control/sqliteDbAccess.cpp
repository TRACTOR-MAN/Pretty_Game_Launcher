#include <QtSql>
#include <iostream>

#include <QMessageBox>
#include "sqliteDbAccess.h"

// If this is a windows build
#ifdef Q_OS_WIN
    #include <windows.h>
// Must be linux
#else
    extern"C"
    {
    #include <stdlib.h>
    #include <pwd.h>
    #include <stdio.h>
    #include <unistd.h>
    }
#endif

/*******************************************************************************
                      ___  ___  ___ __   __ _  _____  ___
                     | _ \| _ \|_ _|\ \ / //_\|_   _|| __|
                     |  _/|   / | |  \ V // _ \ | |  | _|
                     |_|_ |_|_\|___|  \_//_/ \_\|_|_ |___|
                     |   \ | __|| __||_ _|| \| || __|/ __|
                     | |) || _| | _|  | | | .` || _| \__ \
                     |___/ |___||_|  |___||_|\_||___||___/
*******************************************************************************/
#define MAX_USERNAME_LENGTH                                     255

/*******************************************************************************
                    ___   ___    _     ___  _____  ___
                   / __| / _ \  | |   |_ _||_   _|| __|
                   \__ \| (_) | | |__  | |   | |  | _|
                ___|___/ \__\_\ |____||___|  |_|  |___|___
               |   \  /_\|_   _|/_\  | _ )  /_\  / __|| __|
               | |) |/ _ \ | | / _ \ | _ \ / _ \ \__ \| _|
              _|___//_/ \_\|_|/_/_\_\|___//_/ \_\|___/|___|_
             |_ _|| \| ||_   _|| __|| _ \| __|/_\  / __|| __|
              | | | .` |  | |  | _| |   /| _|/ _ \| (__ | _|
             |___||_|\_|  |_|  |___||_|_\|_|/_/ \_\\___||___|
*******************************************************************************/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      05/02/2020
 *
 *  \par       Description:
 *             Constructor for the sqLiteDbInterface class
 */
sqLiteDbInterface::sqLiteDbInterface( QWidget *parent ) :
    my_db( new( QSqlDatabase ) ),
    lclParent( parent )
{
    QString config_path_c;

    // If this is a windws build
    #ifdef Q_OS_WIN
        char username[ MAX_USERNAME_LENGTH ];
        DWORD len_username = sizeof( username );

        if( GetUserNameA( username, &len_username ) != false )
        {
            // Define the path to the database
            config_path_c = "c://users//" + QString::fromStdString( username ) + "//Application Data//Pretty_Game_Launcher//";
        }
        else
        {
            // Provide a warning, we can't find the user name
            if( lclParent != nullptr )
            {
                QMessageBox::warning( lclParent, "Pretty Game Launcher", "Cannot determine username, thus cannot connect to the games database" );
            }
            else
            {
                // Do nothing
            }
        }

    // Must be Linux
    #else
        uid_t uid = geteuid( );
        struct passwd *passwd_ps = getpwuid( uid );

        // If we are pointing to a valid passwd structure
        if( passwd_ps != nullptr )
        {
            // Define the path to the database
            config_path_c = "//home//" + QString::fromStdString( passwd_ps->pw_name ) + "//.config//Pretty_Game_Launcher//";
        }
        else
        {
            // Message pop up to the application
            QString debug_c( "Cannot determine user name for UID: " );
            debug_c = debug_c + QString::number( uid );

            // Provide a warning, we can't find the user name
            if( lclParent != nullptr )
            {
                QMessageBox::warning( lclParent, "Pretty Game Launcher", debug_c );
            }
            else
            {
                // Do nothing
            }
        }
    #endif

    // Directory type
    QDir config_dir_c( config_path_c );

    // Create the directory if it doesn't exist
    if( QDir( config_path_c ).exists( ) == false )
    {
        config_dir_c.mkdir( config_path_c );
    }
    else
    {
        // Do nothing
    }

    // Now create the db path variable
    const QString db_path_c = config_path_c + "game_data.db";

    // Before we do anything, check that the sqlite driver is available
    if( QSqlDatabase::isDriverAvailable("QSQLITE") )
    {
        // we are using the sqlite driver
        *my_db = QSqlDatabase::addDatabase( "QSQLITE" );

        // point to our game database
        my_db->setDatabaseName( db_path_c );

        // Check if the database connection is good
        bool connection_good_b = my_db->open( );

        // Provide some debug on the connection.
        if( connection_good_b == false )
        {
            // It is likely that the pretty_game_launcher excecutable is in the incorrect location
            qDebug() << "Connection to database bad \n";

            // Message pop up to the application
            if( lclParent != nullptr )
            {
                QMessageBox::warning( lclParent, "Pretty Game Launcher", "Bad Database Connection, run application from command line for more information");
            }
            else
            {
                // Do nothing
            }
            // abort.... abort....
            qWarning() << my_db->lastError() << "\n";
        }
        else
        {
            // Good connection!
            std::cout << "Connection to database good" << std::endl;

            // Call the create table command, this ensures that the database is created, if it doesn't already exist
            QSqlQuery query;
            query.exec( "CREATE TABLE \"GameLauncherData\" (\"gameName\" TEXT NOT NULL, \"gameIconPath\" TEXT, \"gameScreenshotPath\" TEXT, \"YoutubeVideoId\" TEXT, \"gameWallpaper\" TEXT, \"gameTextColor\" TEXT NOT NULL, \"launchCommand\" TEXT NOT NULL, \"launchCommandArgs\" TEXT, \"gameDescription\" TEXT NOT NULL, \"playTime\" TEXT)");

            // Read GUI related information from the sqlite database
            readGameGuiInformation( );
        }
    }
    // The sqlite driver is not available
    else
    {
        // Message pop up to the application
        if( lclParent != nullptr )
        {
            QMessageBox::warning( lclParent, "Pretty Game Launcher", "QSQLITE driver not available or not installed");
        }
        else
        {
            // Do nothing
        }
        // The driver is not available
        qWarning( "SQLITE driver not available, check .pro file, and SQL libraries are available" );
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
    query.prepare("SELECT gameName, gameIconPath, gameScreenshotPath, YoutubeVideoId, gameWallpaper, gameTextColor, gameDescription, playTime, launchCommand, launchCommandArgs FROM GameLauncherData ORDER BY gameName COLLATE NOCASE ASC");
    
    // Excecute the query
    if( query.exec( ) == false )
    {
        qDebug() << "Can't excecute query";

        // Message pop up to the application
        if( lclParent != nullptr )
        {
            QMessageBox::warning( lclParent, "Pretty Game Launcher", query.lastError().text() );
        }
        else
        {
            // Do nothing
        }
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
            lcl_GUI_game_information_ps->gameScreenShot = query.value("gameScreenshotPath").toString();
            lcl_GUI_game_information_ps->youtubeVideoID = query.value("YoutubeVideoId").toString();
            lcl_GUI_game_information_ps->GameWallpaper = query.value("gameWallpaper").toString();
            lcl_GUI_game_information_ps->gameTextColor = query.value("gameTextColor").toString();
            lcl_GUI_game_information_ps->gameDescription = query.value("gameDescription").toString();
            lcl_GUI_game_information_ps->playTime = query.value("playTime").toString();
            lcl_GUI_game_information_ps->LaunchCommand = query.value("launchCommand").toString();
            lcl_GUI_game_information_ps->LaunchCommandArgs = query.value("launchCommandArgs").toString();

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
 *             Member function of the readGameGuiInformation class for reading GUI
 *             information from the sqlite database.
 */
void sqLiteDbInterface::addNewGame(
                                    QString gameTitle,
                                    QString launchCommand,
                                    QString launchCommandArgs,
                                    QString gameDescription,
                                    QString gameWallpaper,
                                    QString gameIcon,
                                    QWidget *new_dialogue_parent
                                  )
{
    QSqlQuery query;

    // prepare the query
    query.prepare( "INSERT INTO GameLauncherData(gameName, gameIconPath, gameDescription, playTime, launchCommand, launchCommandArgs, gameWallpaper) values (:gameName, :gameIconPath, :gameDescription, :playTime, :launchCommand, :launchCommandArgs)" );

    // Now bind the values
    query.bindValue( ":gameName", gameTitle );
    query.bindValue( ":gameIconPath", gameIcon );
    query.bindValue( ":gameDescription", gameDescription );
    query.bindValue( ":playTime", "00h:00m:00s" );
    query.bindValue( ":launchCommand", launchCommand );
    query.bindValue( ":launchCommandArgs", launchCommandArgs );
    query.bindValue( ":gameWallpaper", gameWallpaper );

    // Execute the query
    if(query.exec() == false)
    {
        qDebug() << "addNewGameError error:  "
                 << query.lastError();

        // Message pop up to the application
        if( new_dialogue_parent != nullptr )
        {
            QMessageBox::warning( new_dialogue_parent, "Pretty Game Launcher", query.lastError().text() );
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        // Update the vector with the new data
        updateDisplayDataVector( );
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Member function for changing a records game name
 */
void sqLiteDbInterface::changeGameName( const QString oldName, const QString newName )
{
    QSqlQuery query;

    query.prepare( "UPDATE gameLauncherData SET gameName=\"" + newName + "\" WHERE gameName=\"" + oldName + "\"");

    // Execute the query
    if(query.exec() == false)
    {
        // Message pop up to the application
        if( lclParent != nullptr )
        {
            QMessageBox::warning( lclParent, "Pretty Game Launcher", query.lastError().text() );
        }
        else
        {
            // Do nothing
        }
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Member function for changing a records game icon
 */
void sqLiteDbInterface::changeGameIcon( const QString &gameName, const QString &newIcon )
{
    QSqlQuery query;

    query.prepare( "UPDATE gameLauncherData SET gameIconPath=\"" + newIcon + "\" WHERE gameName=\"" + gameName + "\"");

    // Execute the query
    if(query.exec() == false)
    {
        // Message pop up to the application
        if( lclParent != nullptr )
        {
            QMessageBox::warning( lclParent, "Pretty Game Launcher", query.lastError().text() );
        }
        else
        {
            // Do nothing
        }
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Member function for changing a records game icon
 */
void sqLiteDbInterface::changeLaunchScript( const QString &gameName, const QString &newCommand )
{
    QSqlQuery query;

    query.prepare( "UPDATE gameLauncherData SET launchCommand=\"" + newCommand + "\" WHERE gameName=\"" + gameName + "\"");

    // Execute the query
    if(query.exec() == false)
    {
        // Message pop up to the application
        if( lclParent != nullptr )
        {
            QMessageBox::warning( lclParent, "Pretty Game Launcher", query.lastError().text() );
        }
        else
        {
            // Do nothing
        }
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Member function for changing a records cmd args
 */
void sqLiteDbInterface::changeCmdArgs( const QString &gameName, const QString &newArgs )
{
    QSqlQuery query;

    query.prepare( "UPDATE gameLauncherData SET launchCommandArgs=\"" + newArgs + "\" WHERE gameName=\"" + gameName + "\"");

    // Execute the query
    if(query.exec() == false)
    {
        // Message pop up to the application
        if( lclParent != nullptr )
        {
            QMessageBox::warning( lclParent, "Pretty Game Launcher", query.lastError().text() );
        }
        else
        {
            // Do nothing
        }
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Member function for changing a records game description
 */
void sqLiteDbInterface::changeGameDesc( const QString &gameName, const QString &newDesc )
{
    QSqlQuery query;

    query.prepare( "UPDATE gameLauncherData SET gameDescription=\"" + newDesc + "\" WHERE gameName=\"" + gameName + "\"");

    // Execute the query
    if(query.exec() == false)
    {
        // Message pop up to the application
        if( lclParent != nullptr )
        {
            QMessageBox::warning( lclParent, "Pretty Game Launcher", query.lastError().text() );
        }
        else
        {
            // Do nothing
        }
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      05/02/2020
 *
 *  \par       Description:
 *             Member function for updating the data stored in the data vector
 */
void sqLiteDbInterface::updateDisplayDataVector( )
{
    // Delete the old data
    for(uint16_t i = 0U; i < displayData_v.size( ); i++)
    {
        delete displayData_v[i];
    }

    // Clear down the entire displayData_v vector
    displayData_v.clear( );

    // Read the new data
    readGameGuiInformation( );
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
