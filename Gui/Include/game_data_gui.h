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
#include "game_title_edit.h"
#include "game_icon_edit.h"
#include "launch_command_edit.h"

struct proc_and_thread_data_st
{
    QProcess *process;
    QThread *thread;
};

// Forward decleration of the gameNameButtonWidget, defined later in this file
class gameNameButtonWidget;

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

    // Game title edit dialog
    game_title_edit *titleEdit;
    // Game icon edit dialog
    game_icon_edit *iconEdit;
    // Launch command edit dialog
    launch_command_edit *launchEdit;

private:
    // Top level actions
    QAction *launchGame;
    QAction *removeGame;

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
    QString *lastGameName;
    QString *lastGameIcon;
    QString *lastLaunchCommand;

private slots:
    void gameTitleChangeEvent( );
    void newGameTitleAccepted( const QString string );
    void gameIconChangeEvent( );
    void newGameIconAccepted( const QString &string );
    void launchCommandChangeEvent( );
    void newLaunchCommandAccepted( const QString &string );

signals:
    void gameContextUpdateGameName( const QString string );
    void gameContextUpdateGameIcon( const QString &string );
    void gameContextUpdateLaunchScript( const QString &string );
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
    // Callback function to update the game name
    void gameNameSlotUpdateGameName( const QString string );
    // Callback function to update the game icon
    void gameNameSlotUpdateGameIcon( const QString &string );
    // Callback function to update the Launch Script
    void gameNameSlotUpdateLaunchScript( const QString &string );

signals:
    // Signal to pass up the Qt parent list to note that the button has been clicked, with the required args
    void nameBtnclicked( gameNameButtonWidget &buttonWidget);
    // Signal to update the game name
    void gameNameSignalUpdateGameName( const QString string, gameNameButtonWidget * const thisGameName );
    // Signal to update the game icon
    void gameNameSignalUpdateGameIcon( const QString &string, gameNameButtonWidget * const thisGameName );
    // Signal to update the Launch Script
    void gameNameSignalUpdateLaunchScript( const QString &string, gameNameButtonWidget * const thisGameName );
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
    void gameTitleSlotUpdateGameName( const QString text, gameNameButtonWidget * const thisNameButton  );
    // Slot function for updating the game icon only
    void gameTitleSlotUpdateGameIcon( const QString &text, gameNameButtonWidget * const thisNameButton  );
    // Slot function for updating the game launch script only
    void gameTitleSlotUpdateLaunchScript( const QString &text, gameNameButtonWidget * const thisNameButton  );

signals:
    // Signal to pass up the Qt stack to update the pretty information in the parent
    void updatePrettyInformation( gameNameButtonWidget &buttonwidget );
    // Signal to pass up the Qt stack to update the game name of a specific button
    void gameTitleSigUpdateGameName( const QString text, gameNameButtonWidget * const thisNameButton );
    // Signal to pass up the Qt stack to update the game icon of a specific button
    void gameTitleSigUpdateGameIcon( const QString &text, gameNameButtonWidget * const thisNameButton );
    // Signal to pass up the Qt stack to update the Launch Script of a specific button
    void gameTitleSigUpdateLaunchScript( const QString &text, gameNameButtonWidget * const thisNameButton );
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
    void changeGameName( const QString string, gameNameButtonWidget * const thisNameButton );
    void changeGameIcon( const QString &string, gameNameButtonWidget * const thisNameButton );
    void changeLaunchScript( const QString &string, gameNameButtonWidget * const thisNameButton );

protected:
    void refreshAllGames( );
};

#endif // GAME_DATA_GUI_H
