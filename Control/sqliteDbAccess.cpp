#include <QtSql>
#include <iostream>
#include "sqliteDbAccess.h"

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      05/02/2020
 *
 *  \par       Description:
 *             Constructor for the sqLiteDbInterface class
 */
sqLiteDbInterface::sqLiteDbInterface( ) :
    my_db( new( QSqlDatabase ) )
{
    // we are using the sqlite driver
    *my_db = QSqlDatabase::addDatabase( "QSQLITE" );

    // point to our game database
    my_db->setDatabaseName( "../../Config/game_data.db" );

    bool connection_good_b = my_db->open( );

    // Provide some debug on the connection.
    if( connection_good_b == false )
    {
        std::cout << "connection to database bad" << std::endl;
    }
    else
    {
        std::cout << "connection to database good" << std::endl;
    }

    // Read GUI related information from the sqlite database
    readGameGuiInformation( );

    // Read game launch information

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
    query.prepare("SELECT gameName, gameIconPath, gameDescription, playTime, launchCommand, launchScript FROM GameLaunchData");
    
    // Excecute the query
    if( query.exec( ) == false )
    {
        qDebug() << "Can't excecute query";
    }
    else
    {
        while( query.next( ) != false )
        {

            GUI_game_information_st *lcl_GUI_game_information_ps = new( GUI_game_information_st );

            // Store the information in a vector
            lcl_GUI_game_information_ps->gameName = query.value("gameName").toString();
            lcl_GUI_game_information_ps->gameIconPath = query.value("gameIconPath").toString();
            lcl_GUI_game_information_ps->gameDescription = query.value("gameDescription").toString();
            lcl_GUI_game_information_ps->playTime = query.value("playTime").toString();
            lcl_GUI_game_information_ps->LaunchCommand = query.value("launchCommand").toString();
            lcl_GUI_game_information_ps->LaunchScript = query.value("launchScript").toString();

            displayData_vp.push_back( lcl_GUI_game_information_ps );
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
    for(uint16_t i = 0U; i < displayData_vp.size( ); i++)
    {
        delete displayData_vp[i];
    }

    delete my_db;
}    
