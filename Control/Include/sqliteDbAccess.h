#ifndef SQ_LITE_DB_ACCESS_H
#define SQ_LITE_DB_ACCESS_H

#include <QString>
#include <QWidget>

// Forward decleration of the QSqlDatabase class
class QSqlDatabase;

// Structure containing the information to display in the GUI
struct GUI_game_information_st
{
    QString gameName;
    QString gameIconPath;
    QString gameDescription;
    QString playTime;
    QString LaunchCommand;
    QString LaunchCommandArgs;
};

/*! 
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      02/02/2020
 * 
 *  \par       Description:
 *             This class contains the interface between the sqLite database
 *             and the Qt qui application.
 */

class sqLiteDbInterface
{
public:
    sqLiteDbInterface( QWidget *parent );
    ~sqLiteDbInterface( );

    // Read in the information that we need to display for each game
    void readGameGuiInformation( );
    // Read in the information launch information for each game
    void readGameLaunchInformation( );
    // Add a new game to the sqlite database
    void addNewGame(
                     QString gameTitle,
                     QString launchCommand,
                     QString launchCommandArgs,
                     QString gameDescription,
                     QString gameIcon = "\0",
                     QWidget *new_dialogue_parent = nullptr
                   );
    // Function for changing a games name
    void changeGameName( const QString oldName, const QString newName );
    // Function for changing a games icon
    void changeGameIcon( const QString &gameName, const QString &newIcon );
    // Function for changing a games launch script
    void changeLaunchScript( const QString &gameName, const QString &newCommand );
    // Function for changing a games command line args
    void changeCmdArgs( const QString &gameName, const QString &newArgs );
    // Function for changing a games description
    void changeGameDesc( const QString &gameName, const QString &newDesc );

    // Constant pointer to an sqlite database
    QSqlDatabase * const my_db;
    // Vector of pointers to the containing the information to display in the GUI
    std::vector<GUI_game_information_st *> displayData_v;

private:
    // Copy constructor defined but not used, to protect against undefined
    // side effects
    sqLiteDbInterface( const sqLiteDbInterface & obj );
    // Member function for updating the display data vector
    void updateDisplayDataVector( );
    // Local parent widget
    QWidget *lclParent;
};

#endif
