#ifndef GAME_DATA_GUI_H
#define GAME_DATA_GUI_H

#include <QWidget>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QProcess>
#include <QMouseEvent>
#include <QMenu>

#include "sqliteDbAccess.h"

struct proc_and_thread_data_st
{
    QProcess *process;
    QThread *thread;
};

// Forward decleration of the gameNameButtonWidget, defined later in this file
class gameNameButtonWidget;
// Forward decleration of the Add New Game Dialogue Class
class Add_New_Game_Dialogue;

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             This class defines the context menu for each game name
 *             button widget.
 */
class gameNameContextMenu : public QMenu
{
    // Q object needed for the signals and slots mechanism
    Q_OBJECT

public:
    gameNameContextMenu( gameNameButtonWidget *parent );
    ~gameNameContextMenu( );

    // Game edit dialog
    Add_New_Game_Dialogue *gameEditDialog;

private:
    // Top level actions
    QAction *launchGame;
    QAction *removeGame;
    QAction *editGameLaunchData;

    // Sub menu
    QMenu   *editGameLaunchParams;
    // Sub menu actions
    QAction *editGameName;
    QAction *editGameIcon;
    QAction *editLaunchCommand;
    QAction *editCommandLineArgs;
    QAction *editGameDescription;

    // Pointer to the local parent
    gameNameButtonWidget *lclParent;

    // last variables
    GUI_game_information_st *gameInformation;

private slots:
    void editGameParamsEvent( );
    void newGameDataAccepted( );

signals:
    void gameContextUpdateGameData( const GUI_game_information_st &data );
};

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             This class defines the name button widget
 */
class gameNameButtonWidget : public QPushButton
{
    // Q object needed for the signals and slots mechanism
    Q_OBJECT
public:
    gameNameButtonWidget( const QString &text );
    ~gameNameButtonWidget( ) override;

    // String variables storing the metadata for the launch object
    QString gameDescription;
    QString playTime;
    QString gameIcon;
    QString launchCommand;
    QString launchCommandArgs;

private:
    gameNameContextMenu *contextMenu;

private slots:
    // Callback function for when the button is clicked
    void mousePressEvent(QMouseEvent *e) override;
    // Callback function to update the game parameters
    void gameNameSlotUpdateGameData( const GUI_game_information_st &data );

signals:
    // Signal to pass up the Qt parent list to note that the button has been clicked, with the required args
    void nameBtnclicked( gameNameButtonWidget &buttonWidget);
    // Signal to update the game data
    void gameNameSigUpdateGameData( const GUI_game_information_st &data, gameNameButtonWidget * const thisNameButton );
};

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             This class defines the name button widget
 */
class LaunchButtonWidget : public QPushButton
{
    // Q object needed for the signals and slots mechanism
    Q_OBJECT
public:
    LaunchButtonWidget( const QString &text );
    ~LaunchButtonWidget( );

    // String variables storing the metadata for the launch object
    QString launchCommand;
    // String variables storing the metadata for the launch object
    QString launchCommandArgs;

    // vector containing all of the active processes and threads
    std::vector<proc_and_thread_data_st *> proc_and_thread_vp;

private slots:
    // Callback function for when the button is clicked
    void launchGame( );

signals:
    // Signal to pass up the Qt parent list to note that the button has been clicked, with the required args
    void launchBtnClicked( LaunchButtonWidget &launchWidget);
};

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

    // Function for adding the spacer to the layout
    void addVerticalSpacer( );

    // Function for deleting all current games
    void deleteAllGameButtons( );

    // Layout object
    QVBoxLayout *layout;

    // Maximum width of the object
    int max_width;

private:
    std::vector<QPushButton *> buttonPtrList;
    QSpacerItem *VGameNameSpacer;


private slots:
    // Slot function to update the pretty game information
    void updatePrettyGameInfo( gameNameButtonWidget &buttonwidget );
    // Slot function for updating the game name only
    void gameTitleSlotUpdateGameData( const GUI_game_information_st & data, gameNameButtonWidget * const thisNameButton );

signals:
    // Signal to pass up the Qt stack to update the pretty information in the parent
    void updatePrettyInformation( gameNameButtonWidget &buttonwidget );
    // Signal to pass up the Qt stack to update the game data of a specific button
    void gameTitleSigUpdateGameData( const GUI_game_information_st &data, gameNameButtonWidget * const thisNameButton );
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
    void changeGameIcon( gameNameButtonWidget &buttonInformation );
    // Function for changing the game information
    void changeGameInfo( gameNameButtonWidget &buttonInformation );
    // Function for changing the play time
    void changePlayTime( gameNameButtonWidget &buttonInformation );

    // Layout objects
    QVBoxLayout *vertLayout;
    QVBoxLayout *timeVertLayout;
    QGroupBox *gameDescriptionBox;
    QGroupBox *playTimeBox;

    // Main game Icon widget
    QLabel *gameImage;
    // Launch button widget
    LaunchButtonWidget *launchButton;
    // Game information widget
    QLabel *gameInformation;
    // Play time widget
    QLabel *playTime;

    // Layout object
    QGridLayout *layout;

    // The current icon path in use
    QString *currentIconPath;
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
    gameDataGuiWidget( sqLiteDbInterface &psdDatabase, QWidget *parent = nullptr);
    ~gameDataGuiWidget( );

    // Member function for adding a new game to the database and GUI
    void AddNewGameToGuiAndDbc(
                                QString gameTitle,
                                QString launchCommand,
                                QString launchCommandArgs,
                                QString gameDescription,
                                QString gameIcon = "\0",
                                QWidget *parent = nullptr
                              );

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
    sqLiteDbInterface &lclDatabase;

private slots:
    void redrawPrettyInformation( gameNameButtonWidget &buttonInformation );
    void changeGameData( const GUI_game_information_st & data, gameNameButtonWidget * const thisNameButton );

protected:
    void refreshAllGames( );
};

#endif // GAME_DATA_GUI_H
