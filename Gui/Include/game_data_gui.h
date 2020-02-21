#ifndef GAME_DATA_GUI_H
#define GAME_DATA_GUI_H

#include <QWidget>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>


#include "sqliteDbAccess.h"


/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      07/02/2020
 *
 *  \par       Description:
 *             This class defines the widget which displays the game names.
 */
class gameTitleWidget : public QWidget
{
    // Q object needed for the signals and slots mechanism
    Q_OBJECT
public:
    gameTitleWidget ( QWidget &parent, int minimumWidth = 200 );
    ~gameTitleWidget ( );

    // Member function for adding an element to the game title widget
    void addGameTitle ( GUI_game_information_st guiInformation );

    // Layout object
    QVBoxLayout *layout;

    // Maximum width of the object
    int max_width;

private:
    std::vector<QPushButton *> buttonPtrList;
};

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      07/02/2020
 *
 *  \par       Description:
 *             This class defines the widget which displays the game data
 */
class gamePrettyWidget : public QWidget
{
    // Q object needed for the signals and slots mechanism
    Q_OBJECT
public:
    gamePrettyWidget( QWidget &parent );
    ~gamePrettyWidget( );

    // Function for changing the icon that is being displayed
    void changeGameIcon( GUI_game_information_st &guiInformation );
    // Function for changing the game information
    void changeGameInfo( GUI_game_information_st &guiInformation );
    // Function for changing the play time
    void changePlayTime( GUI_game_information_st &guiInformation );

    // Layout objects
    QVBoxLayout *vertLayout;
    QVBoxLayout *timeVertLayout;
    QGroupBox *gameDescriptionBox;
    QGroupBox *playTimeBox;

    // Main game Icon widget
    QLabel *gameImage;
    // Launch button widget
    QPushButton *launchButton;
    // Game information widget
    QLabel *gameInformation;
    // Play time widget
    QLabel *playTime;

    // Layout object
    QGridLayout *layout;
};

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      07/02/2020
 *
 *  \par       Description:
 *             This class defines the main widget which handles the display interface
 *             for the launcher
 */
class gameDataGuiWidget : public QWidget
{
    // Q object needed for the signals and slots mechanism
    Q_OBJECT
public:
    gameDataGuiWidget( QWidget &parent );
    ~gameDataGuiWidget( );

    // The max width of the scroll area
    int scrollAreaMaxWidth;

    // Layout objects
    QHBoxLayout *horizLayout_p;

    // Scroll area objects
    QScrollArea *scrollArea;

    // Widget objects for the game data GUI
    gameTitleWidget *gameNameWidget;
    gamePrettyWidget *prettyWidget;

    // Objects to handle the interface to the sqlite database
    sqLiteDbInterface *myDatabase;
};

#endif // GAME_DATA_GUI_H
