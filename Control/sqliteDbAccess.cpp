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
    my_db( new( QSqlDatabase ) ),
    displayData_vp( new( std::vector<GUI_game_information_st> ) )
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
    query.prepare("SELECT gameName, gameIconPath, gameDescription, playTime FROM GameLaunchData");
    
    // Excecute the query
    if( query.exec( ) == false )
    {
        qDebug() << "Can't excecute query";
    }
    else
    {
        GUI_game_information_st lcl_GUI_game_information_s;

        while( query.next( ) != false )
        {

            // Store the information in a vector
            lcl_GUI_game_information_s.gameName = query.value("gameName").toString();
            lcl_GUI_game_information_s.gameIconPath = query.value("gameIconPath").toString();
            lcl_GUI_game_information_s.gameDescription = query.value("gameDescription").toString();
            lcl_GUI_game_information_s.playTime = query.value("playTime").toString();

            displayData_vp->push_back( lcl_GUI_game_information_s );
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

    #if(1)
        GUI_game_information_st *lcl_GUI_game_information_p = &displayData_vp->operator[](0);

        if( lcl_GUI_game_information_p != nullptr )
        {   
            qDebug( ) << lcl_GUI_game_information_p->gameName << endl;
        }
    #endif

    delete my_db;
    delete displayData_vp;
}    
