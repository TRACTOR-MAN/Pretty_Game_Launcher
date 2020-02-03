#include <QtSql>
#include <iostream>
#include "sqliteDbAccess.h"

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
}

void sqLiteDbInterface::readGameGuiInformation( )
{
    // The command I need.
    // SELECT gameName, gameIconPath, gameDescription, playTime FROM GameLaunchData WHERE rowid = 1;
    // I also need the length of the database.
    QSqlQuery query;
    query.prepare("SELECT gameName, gameIconPath, gameDescription, playTime FROM GameLaunchData");
    
    if( query.exec( ) == false )
    {
        qDebug() << "Can't excecute query";
    }
    else
    {
        while(query.next( ))
        {
            qDebug() << "Game Name: " << query.value("gameName").toString();
            qDebug() << "Game Icon Path " << query.value("gameIconPath").toString();
            qDebug() << "Game Description" << query.value("gameDescription").toString();
            qDebug() << "Play time" << query.value("playTime").toString();
        }
    }
}

sqLiteDbInterface::~sqLiteDbInterface( )
{
    delete my_db;
}    