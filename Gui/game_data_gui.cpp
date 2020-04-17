#include <QtCore>
#include <QPushButton>

#include "game_data_gui.h"

/*******************************************************************************
               ___    _    __  __  ___   ___    _  _____  _
              / __|  /_\  |  \/  || __| |   \  /_\|_   _|/_\
             | (_ | / _ \ | |\/| || _|  | |) |/ _ \ | | / _ \
              \___|/_/ \_\|_| _|_||___|_|___//_/ \_\|_|/_/ \_\
                             / __|| | | ||_ _|
                            | (_ || |_| | | |
                             \___| \___/ |___|
*******************************************************************************/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      07/02/2020
 *
 *  \par       Description:
 *             Constructor for the gameDatauiWidget class
 */
gameDataGuiWidget::gameDataGuiWidget( sqLiteDbInterface &psdDatabase, QWidget *parent ) :
    QWidget(parent),
    scrollAreaMaxWidth( 200 ),
    horizLayout_p( new QHBoxLayout ),
    scrollArea( new QScrollArea ),
    gameNameWidget( new gameTitleWidget( *this, (scrollAreaMaxWidth - 15) )),
    prettyWidget( new gamePrettyWidget( *this )),
    lclDatabase( psdDatabase )
{
    connect( gameNameWidget, SIGNAL( updatePrettyInformation( gameNameButtonWidget &) ), this, SLOT(redrawPrettyInformation( gameNameButtonWidget & ) ) );
    connect( gameNameWidget, SIGNAL( gameTitleSigUpdateGameName( const QString, gameNameButtonWidget * const ) ), this, SLOT( changeGameName( const QString, gameNameButtonWidget * const ) ) );
    connect( gameNameWidget, SIGNAL( gameTitleSigUpdateGameIcon( const QString&, gameNameButtonWidget * const ) ), this, SLOT( changeGameIcon( const QString&, gameNameButtonWidget * const ) ) );
    connect( gameNameWidget, SIGNAL( gameTitleSigUpdateLaunchScript( const QString&, gameNameButtonWidget * const ) ), this, SLOT( changeLaunchScript( const QString&, gameNameButtonWidget * const ) ) );
    connect( gameNameWidget, SIGNAL( gameTitleSigUpdateCmdArgs( const QString&, gameNameButtonWidget * const ) ), this, SLOT( changeCmdArgs( const QString&, gameNameButtonWidget * const ) ) );
    connect( gameNameWidget, SIGNAL( gameTitleSigUpdateGameDesc( const QString&, gameNameButtonWidget * const ) ), this, SLOT( changeGameDesc( const QString&, gameNameButtonWidget * const ) ) );

    // If there is data to process
    if(  lclDatabase.displayData_v.empty( ) == false )
    {
        // Itterate through the entire database, and add every game name
        for( uint16_t i = 0U; i < lclDatabase.displayData_v.size(); i++ )
        {
            gameNameWidget->addGameTitle( *lclDatabase.displayData_v[i] );
        }

        // Add a vertical spacer to push items up
        gameNameWidget->addVerticalSpacer( );
    }
    else
    {
        // Do nothing
    }

    // Add the game name widget to the scroll area
    scrollArea->setMaximumWidth( scrollAreaMaxWidth );
    scrollArea->setWidget( gameNameWidget );
    scrollArea->setWidgetResizable( true );

    // Add the widgets to the main view
    horizLayout_p->addWidget( scrollArea );
    horizLayout_p->addWidget( prettyWidget );

    this->setLayout( horizLayout_p );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Slot for updating the game GUI information
 */
void gameDataGuiWidget::redrawPrettyInformation( gameNameButtonWidget &buttonInformation )
{
    prettyWidget->changeGameIcon( buttonInformation );
    prettyWidget->changeGameInfo( buttonInformation );
    prettyWidget->changePlayTime( buttonInformation );

    prettyWidget->launchButton->launchCommand = buttonInformation.launchCommand;
    prettyWidget->launchButton->launchCommandArgs = buttonInformation.launchCommandArgs;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot for updating the game name for a specific game.
 */
void gameDataGuiWidget::changeGameName( const QString string, gameNameButtonWidget * const thisNameButton )
{
    // First update the database with the new data
    lclDatabase.changeGameName( thisNameButton->text(), string );

    // Now update the game name in the game name button
    thisNameButton->setText( string );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot for updating the game icon for a specific game
 */
void gameDataGuiWidget::changeGameIcon( const QString &string, gameNameButtonWidget * const thisNameButton )
{
    // First update the database with the new data
    lclDatabase.changeGameIcon( thisNameButton->text(), string );

    // Flag which notes whether or not to update the pretty information
    bool update_pretty_info_b = false;

    if( prettyWidget->currentIconPath == thisNameButton->gameIcon )
    {
        update_pretty_info_b = true;
    }
    else
    {
        // Images are not the same
    }


    // Now update the game name in the game name button
    thisNameButton->gameIcon = string;

    // If we need to redraw the pretty info
    if( update_pretty_info_b != false )
    {
        redrawPrettyInformation( *thisNameButton );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Slot for updating the launch script for a specific game
 */
void gameDataGuiWidget::changeLaunchScript( const QString &string, gameNameButtonWidget * const thisNameButton )
{
    // First update the database with the new data
    lclDatabase.changeLaunchScript( thisNameButton->text(), string );

    // Flag which notes whether or not to update the pretty information
    bool update_pretty_info_b = false;

    if( prettyWidget->launchButton->launchCommand == thisNameButton->launchCommand )
    {
        update_pretty_info_b = true;
    }
    else
    {
        // Launch script not the same
    }


    // Now update the launch command button
    thisNameButton->launchCommand = string;

    // If we need to redraw the pretty info
    if( update_pretty_info_b != false )
    {
        redrawPrettyInformation( *thisNameButton );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Slot for updating the command line args for a specific game
 */
void gameDataGuiWidget::changeCmdArgs( const QString &string, gameNameButtonWidget * const thisNameButton )
{
    // First update the database with the new data
    lclDatabase.changeCmdArgs( thisNameButton->text(), string );

    // Flag which notes whether or not to update the pretty information
    bool update_pretty_info_b = false;

    if( prettyWidget->launchButton->launchCommandArgs == thisNameButton->launchCommandArgs )
    {
        update_pretty_info_b = true;
    }
    else
    {
        // Launch script not the same
    }


    // Now update the launch command button
    thisNameButton->launchCommandArgs = string;

    // If we need to redraw the pretty info
    if( update_pretty_info_b != false )
    {
        redrawPrettyInformation( *thisNameButton );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Slot for updating the game description for a specific game
 */
void gameDataGuiWidget::changeGameDesc( const QString &string, gameNameButtonWidget * const thisNameButton )
{
    // First update the database with the new data
    lclDatabase.changeGameDesc( thisNameButton->text(), string );

    // Flag which notes whether or not to update the pretty information
    bool update_pretty_info_b = false;

    if( prettyWidget->gameInformation->text() == thisNameButton->gameDescription )
    {
        update_pretty_info_b = true;
    }
    else
    {
        // Launch script not the same
    }


    // Now update the launch command button
    thisNameButton->gameDescription = string;

    // If we need to redraw the pretty info
    if( update_pretty_info_b != false )
    {
        redrawPrettyInformation( *thisNameButton );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Member function for adding a new game to the GUI and DB file.
 */
void gameDataGuiWidget::AddNewGameToGuiAndDbc(
                                               QString gameTitle,
                                               QString launchCommand,
                                               QString launchCommandArgs,
                                               QString gameDescription,
                                               QString gameIcon,
                                               QWidget *parent
                                             )
{
    lclDatabase.addNewGame( gameTitle, launchCommand, launchCommandArgs, gameDescription, gameIcon, parent );

    refreshAllGames( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Member function for refreshing all games being displayed
 */
void gameDataGuiWidget::refreshAllGames( )
{    
    gameNameWidget->deleteAllGameButtons( );

    // If there is data to process
    if(  lclDatabase.displayData_v.empty( ) == false )
    {
        // Itterate through the entire database, and add every game name
        for( uint16_t i = 0U; i < lclDatabase.displayData_v.size(); i++ )
        {
            gameNameWidget->addGameTitle( *lclDatabase.displayData_v[i] );
        }

        // Add a vertical spacer to push items up
        gameNameWidget->addVerticalSpacer( );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      07/02/2020
 *
 *  \par       Description:
 *             Destructor for the gameDatauiWidget class
 */
gameDataGuiWidget::~gameDataGuiWidget( )
{
    delete horizLayout_p;
    delete gameNameWidget;
    delete prettyWidget;
    delete scrollArea;
}

/*******************************************************************************
               ___    _    __  __  ___   _____  ___  _____  _     ___
              / __|  /_\  |  \/  || __| |_   _||_ _||_   _|| |   | __|
             | (_ | / _ \ | |\/| || _|    | |   | |   | |  | |__ | _|
              \___|/_/ \_\|_|  |_||___|   |_|  |___|  |_|  |____||___|
*******************************************************************************/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      08/02/2020
 *
 *  \par       Description:
 *             Constructor for the gameTitleWidget class
 */
gameTitleWidget::gameTitleWidget( QWidget &parent, int minimumWidth ) :
    QWidget( &parent ),
    layout( new QVBoxLayout(this) ),
    VGameNameSpacer( new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding) )
{    
    this->setMinimumWidth( minimumWidth );

    this->setLayout( layout );

    this->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      16/02/2020
 *
 *  \par       Description:
 *             Member function for adding an element to the game title widget
 */
void gameTitleWidget::addGameTitle( GUI_game_information_st guiInformation )
{
    gameNameButtonWidget * nameButton = new gameNameButtonWidget( guiInformation.gameName );

    // Connect the signal to the slot for this button
    connect( nameButton, SIGNAL(nameBtnclicked( gameNameButtonWidget & )), this, SLOT(updatePrettyGameInfo( gameNameButtonWidget & )) );
    connect( nameButton, SIGNAL(gameNameSignalUpdateGameName( const QString, gameNameButtonWidget * const )), this, SLOT( gameTitleSlotUpdateGameName( const QString, gameNameButtonWidget * const ) ) );
    connect( nameButton, SIGNAL(gameNameSignalUpdateGameIcon( const QString&, gameNameButtonWidget * const )), this, SLOT( gameTitleSlotUpdateGameIcon( const QString&, gameNameButtonWidget * const ) ) );
    connect( nameButton, SIGNAL(gameNameSignalUpdateLaunchScript( const QString&, gameNameButtonWidget * const )), this, SLOT( gameTitleSlotUpdateLaunchScript( const QString&, gameNameButtonWidget * const ) ) );
    connect( nameButton, SIGNAL(gameNameSignalUpdateCmdArgs( const QString&, gameNameButtonWidget * const )), this, SLOT( gameTitleSlotUpdateCmdArgs( const QString&, gameNameButtonWidget * const ) ) );
    connect( nameButton, SIGNAL(gameNameSignalUpdateGameDesc( const QString&, gameNameButtonWidget * const )), this, SLOT( gameTitleSlotUpdateGameDesc( const QString&, gameNameButtonWidget * const ) ) );

    // Update the metadata with the metatata for this record
    nameButton->gameDescription = guiInformation.gameDescription;
    nameButton->playTime = guiInformation.playTime;
    nameButton->gameIcon = guiInformation.gameIconPath;
    nameButton->launchCommandArgs = guiInformation.LaunchCommandArgs;
    nameButton->launchCommand = guiInformation.LaunchCommand;

    // Add the push button to the layout
    layout->addWidget( nameButton );

    // Add the button pointer to the button pointer list
    buttonPtrList.push_back( nameButton );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Slot function for updating the pretty game information
 */
void gameTitleWidget::updatePrettyGameInfo( gameNameButtonWidget &buttonwidget )
{
    emit updatePrettyInformation( buttonwidget );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot function for updating the game name
 */
void gameTitleWidget::gameTitleSlotUpdateGameName( const QString text, gameNameButtonWidget * const thisNameButton )
{
    // Pass this up to the pretty widget, then update the game name
    emit gameTitleSigUpdateGameName( text, thisNameButton );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Slot function for updating the game icon
 */
void gameTitleWidget::gameTitleSlotUpdateGameIcon( const QString &text, gameNameButtonWidget * const thisNameButton )
{
    // Pass this up to the pretty widget, then update the game icon
    emit gameTitleSigUpdateGameIcon( text, thisNameButton );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Slot function for updating the launch script
 */
void gameTitleWidget::gameTitleSlotUpdateLaunchScript( const QString &text, gameNameButtonWidget * const thisNameButton )
{
    // Pass this up to the pretty widget, then update the launch script
    emit gameTitleSigUpdateLaunchScript( text, thisNameButton );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Slot function for updating the command line args
 */
void gameTitleWidget::gameTitleSlotUpdateCmdArgs( const QString &text, gameNameButtonWidget * const thisNameButton )
{
    // Pass this up to the pretty widget, then update the launch script
    emit gameTitleSigUpdateCmdArgs( text, thisNameButton );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Slot function for updating the game description.
 */
void gameTitleWidget::gameTitleSlotUpdateGameDesc( const QString &text, gameNameButtonWidget * const thisNameButton )
{
    // Pass this up to the pretty widget, then update the launch script
    emit gameTitleSigUpdateGameDesc( text, thisNameButton );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      22/04/2020
 *
 *  \par       Description:
 *             Function for adding a vertical spacer to the scroll area
 */
void gameTitleWidget::addVerticalSpacer(  )
{
    layout->addSpacerItem( VGameNameSpacer );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      22/04/2020
 *
 *  \par       Description:
 *             Function for deleting all game buttons
 */
void gameTitleWidget::deleteAllGameButtons(  )
{
    // Clean up all button objects
    for ( uint16_t i = 0; i < buttonPtrList.size(); i++)
    {
        layout->removeWidget( buttonPtrList[i] );
        delete buttonPtrList[i];
    }

    layout->removeItem( VGameNameSpacer );

    // Clear down the entire buttonPtrList vector
    buttonPtrList.clear( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      07/02/2020
 *
 *  \par       Description:
 *             Destructor for the gameTitleWidget class
 */
gameTitleWidget::~gameTitleWidget( )
{
    delete layout;

    // Note that deleting layout cleans up all objects contained in it
}

/*******************************************************************************
  ___  ___  ___  _____  _____ __   __ __      __ ___  ___    ___  ___  _____
 | _ \| _ \| __||_   _||_   _|\ \ / / \ \    / /|_ _||   \  / __|| __||_   _|
 |  _/|   /| _|   | |    | |   \ V /   \ \/\/ /  | | | |) || (_ || _|   | |
 |_|  |_|_\|___|  |_|    |_|    |_|     \_/\_/  |___||___/  \___||___|  |_|
*******************************************************************************/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      08/02/2020
 *
 *  \par       Description:
 *             Constructor for the gamePrettyWidget class
 */
gamePrettyWidget::gamePrettyWidget( QWidget &parent ) :
    QWidget( &parent ),
    vertLayout( new QVBoxLayout ),
    timeVertLayout( new QVBoxLayout ),
    gameDescriptionBox( new QGroupBox( "Game Description" ) ),
    playTimeBox( new QGroupBox( "Game Play Time" ) ),
    gameImage( new QLabel ),
    launchButton( new LaunchButtonWidget("Launch Game") ),
    gameInformation( new QLabel ),
    playTime( new QLabel ),
    layout( new QGridLayout(this) ),
    currentIconPath( new QString )
{
    // Set the info widget to wrap text
    gameInformation->setWordWrap(true);
    // Set the maximum size of the launch button
    launchButton->setMinimumSize( 160, 40 );
    // Set the minimum size of the game time widget
    playTime->setMinimumSize( 160, 40 );
    // Set the maximum size of the icon widget
    gameImage->setMaximumSize( 350, 350 );
    // Set the game time widget to central justify text
    playTime->setAlignment(Qt::AlignCenter);

    // Place the game information into the game description group box
    vertLayout->addWidget( gameInformation, 0, Qt::AlignTop );
    // Set the layout of the description box
    gameDescriptionBox->setLayout( vertLayout );

    // Place the play time into the play time group box
    timeVertLayout->addWidget( playTime, 0, Qt::AlignHCenter );
    // Set the layout of the play time box
    playTimeBox->setLayout( timeVertLayout );

    // Add all of the widgets
    layout->addWidget( gameImage, 1, 1, 1, 1, Qt::AlignCenter | Qt::AlignTop );
    layout->addWidget( launchButton, 0, 0, 1, 1, Qt::AlignCenter  );
    layout->addWidget( gameDescriptionBox, 2, 0, 1, 3);
    layout->addWidget( playTimeBox, 0, 2, 1, 1, Qt::AlignCenter );

    this->setLayout(layout);
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      16/02/2020
 *
 *  \par       Description:
 *             Member function for changing the image widget
 */
void gamePrettyWidget::changeGameIcon( gameNameButtonWidget &buttonInformation )
{
    // Only Add the picture if there is one assigned
    if( buttonInformation.gameIcon != "" )
    {
        QPixmap picture( buttonInformation.gameIcon );

        gameImage->setPixmap( picture.scaled(350, 350, Qt::KeepAspectRatio) );
    }
    else
    {
        QPixmap picture( "" );

        gameImage->setPixmap( picture );
    }

    *currentIconPath = buttonInformation.gameIcon;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      16/02/2020
 *
 *  \par       Description:
 *             Member function for changing the game information
 */
void gamePrettyWidget::changeGameInfo( gameNameButtonWidget &buttonInformation )
{
    // Only set the text if there is some to show
    if( buttonInformation.gameDescription != "" )
    {
        gameInformation->setText( buttonInformation.gameDescription );
    }
    else
    {
        gameInformation->setText( "" );
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      18/02/2020
 *
 *  \par       Description:
 *             Member function for changing the play time.
 */
void gamePrettyWidget::changePlayTime( gameNameButtonWidget &buttonInformation )
{
    // Only set the text if there is some to show
    if( buttonInformation.playTime != "" )
    {
        playTime->setText( buttonInformation.playTime );
    }
    else
    {
        playTime->setText( "" );
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      07/02/2020
 *
 *  \par       Description:
 *             Destructor for the gamePrettyWidget class
 */
gamePrettyWidget::~gamePrettyWidget( )
{
    delete layout;
    delete playTimeBox;
    delete vertLayout;
    delete launchButton;
    delete gameImage;
    delete gameInformation;
    delete currentIconPath;
}

/*******************************************************************************
               ___    _    __  __  ___   _  _    _    __  __  ___
              / __|  /_\  |  \/  || __| | \| |  /_\  |  \/  || __|
             | (_ | / _ \ | |\/| || _|  | .` | / _ \ | |\/| || _|
              \___|/_/_\_\|_|_ |_||___|_|_|\_|/_/ \_\|_|  |_||___|
                   | _ )| | | ||_   _||_   _|/ _ \ | \| |
                   | _ \| |_| |  | |    | | | (_) || .` |
                   |___/ \___/   |_|    |_|  \___/ |_|\_|
*******************************************************************************/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Constructor for the gameNameButtonWidget class
 */
gameNameButtonWidget::gameNameButtonWidget( const QString & text ) :
    QPushButton( text ),
    contextMenu( new gameNameContextMenu( this ) )
{
    connect( contextMenu, SIGNAL( gameContextUpdateGameName( const QString ) ), this, SLOT( gameNameSlotUpdateGameName( const QString ) ) );
    connect( contextMenu, SIGNAL( gameContextUpdateGameIcon( const QString&) ), this, SLOT( gameNameSlotUpdateGameIcon( const QString& ) ) );
    connect( contextMenu, SIGNAL( gameContextUpdateLaunchScript( const QString&) ), this, SLOT( gameNameSlotUpdateLaunchScript( const QString& ) ) );  
    connect( contextMenu, SIGNAL( gameContextUpdateCmdLineArgs( const QString&) ), this, SLOT( gameNameSlotUpdateCmdLineArgs( const QString& ) ) );
    connect( contextMenu, SIGNAL( gameContextUpdateGameDesc( const QString&) ), this, SLOT( gameNameSlotUpdateGameDescription( const QString& ) ) );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      13/04/2020
 *
 *  \par       Description:
 *             Function for logging mouse events
 */
void gameNameButtonWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        // Action the left click event
        emit nameBtnclicked( *this );
    }
    else
    if( e->button()==Qt::RightButton )
    {
        // Show the context menu
        contextMenu->exec( QCursor::pos() );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot function for updating the game name
 */
void gameNameButtonWidget::gameNameSlotUpdateGameName( const QString string )
{
    emit gameNameSignalUpdateGameName( string, this );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Slot function for updating the game icon
 */
void gameNameButtonWidget::gameNameSlotUpdateGameIcon( const QString &string )
{
    emit gameNameSignalUpdateGameIcon( string, this );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot function for updating the game launch script
 */
void gameNameButtonWidget::gameNameSlotUpdateLaunchScript( const QString &string )
{
    emit gameNameSignalUpdateLaunchScript( string, this );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Slot function for updating the game command line args
 */
void gameNameButtonWidget::gameNameSlotUpdateCmdLineArgs( const QString &string )
{
    emit gameNameSignalUpdateCmdArgs( string, this );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Slot function for updating the game description
 */
void gameNameButtonWidget::gameNameSlotUpdateGameDescription( const QString &string )
{
    emit gameNameSignalUpdateGameDesc( string, this );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Destructor for the gameNameButtonWidget class
 */
gameNameButtonWidget::~gameNameButtonWidget( )
{
    delete contextMenu;
}

/*******************************************************************************
  _       _   _   _  _  _   ___  _  _   ___  _   _  _____  _____  ___   _  _
 | |     /_\ | | | || \| | / __|| || | | _ )| | | ||_   _||_   _|/ _ \ | \| |
 | |__  / _ \| |_| || .` || (__ | __ | | _ \| |_| |  | |    | | | (_) || .` |
 |____|/_/ \_\\___/ |_|\_| \___||_||_| |___/ \___/   |_|    |_|  \___/ |_|\_|
*******************************************************************************/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Constructor for the launchButtonWidget class
 */
LaunchButtonWidget::LaunchButtonWidget( const QString & text ) :
    QPushButton( text )
{
    // Connect the signal to the slot for this button
    connect( this, SIGNAL(clicked( )), this, SLOT(launchGame( )) );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Slot function launch the associated game
 */
void LaunchButtonWidget::launchGame( )
{
    if( launchCommand != "" )
    {
        proc_and_thread_data_st * proc_and_thread_data_ps = new proc_and_thread_data_st;
        proc_and_thread_data_ps->thread = new QThread;
        proc_and_thread_data_ps->process = new QProcess;

        proc_and_thread_data_ps->process->moveToThread( proc_and_thread_data_ps->thread );

        proc_and_thread_data_ps->process->start( launchCommand + " " + launchCommandArgs );

        proc_and_thread_vp.push_back( proc_and_thread_data_ps );
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Destructor for the launchButtonWidget class
 */
LaunchButtonWidget::~LaunchButtonWidget( )
{
    for( uint16_t i = 0U; i < proc_and_thread_vp.size( ); i++ )
    {
        delete proc_and_thread_vp[i]->thread;
        delete proc_and_thread_vp[i]->process;
        delete proc_and_thread_vp[i];
    }
}

/*******************************************************************************
       ___    _    __  __  ___    ___  ___   _  _  _____  ___ __  __ _____
      / __|  /_\  |  \/  || __|  / __|/ _ \ | \| ||_   _|| __|\ \/ /|_   _|
     | (_ | / _ \ | |\/| || _|  | (__| (_) || .` |  | |  | _|  >  <   | |
      \___|/_/ \_\|_|  |_||___| _\___|\___/_|_|\_|  |_|  |___|/_/\_\  |_|
                       |  \/  || __|| \| || | | |
                       | |\/| || _| | .` || |_| |
                       |_|  |_||___||_|\_| \___/
*******************************************************************************/
/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Constructor for the gameNameContextMenu class
 */
gameNameContextMenu::gameNameContextMenu( gameNameButtonWidget *parent ) :
    QMenu( "Game Options", parent ),
    titleEdit( nullptr ),
    iconEdit( nullptr ),
    launchEdit( nullptr ),
    cmdArgsEdit( nullptr ),
    gameDescEdit( nullptr ),
    launchGame( new QAction( "Launch", parent ) ),
    removeGame( new QAction( "Remove Game", parent ) ),
    editGameLaunchParams( new QMenu( "Edit Game Launch Params", parent ) ),
    editGameName( new QAction( "Game Name", parent ) ),
    editGameIcon( new QAction( "Game Icon", parent ) ),
    editLaunchCommand( new QAction( "Launch Command", parent ) ),
    editCommandLineArgs( new QAction( "Command Line Args", parent ) ),
    editGameDescription( new QAction( "Game Description", parent ) ),
    lclParent( parent ),
    lastGameName( new QString ),
    lastGameIcon( new QString ),
    lastLaunchCommand( new QString ),
    lastCmdLineArgs( new QString ),
    lastGameDescription( new QString )
{
    // Set-up the context menu
    setContextMenuPolicy( Qt::CustomContextMenu );

    // Connect all of the actions
    connect( editGameName, SIGNAL(triggered( )), this, SLOT( gameTitleChangeEvent( ) ) );
    connect( editGameIcon, SIGNAL(triggered( )), this, SLOT( gameIconChangeEvent( ) ) );
    connect( editLaunchCommand, SIGNAL(triggered( )), this, SLOT( launchCommandChangeEvent( ) ) );
    connect( editCommandLineArgs, SIGNAL(triggered( )), this, SLOT( cmdLineArgsChangeEvent( ) ) );
    connect( editGameDescription, SIGNAL(triggered( )), this, SLOT( gameDescChangeEvent( ) ) );


    // First configure the sub menu
    editGameLaunchParams->addAction( editGameName );
    editGameLaunchParams->addAction( editGameIcon );
    editGameLaunchParams->addAction( editLaunchCommand );
    editGameLaunchParams->addAction( editCommandLineArgs );
    editGameLaunchParams->addAction( editGameDescription );

    // Add the actions
    addAction( launchGame );
    // Add the sub menu
    addMenu( editGameLaunchParams );
    // Add more actions
    addAction( removeGame );

    // Start up hidden
    hide( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot function for openning a game title edit window.
 */
void gameNameContextMenu::gameTitleChangeEvent( )
{
    if( titleEdit == nullptr )
    {
        titleEdit = new game_title_edit;
        connect( titleEdit, SIGNAL( gameTitleAccepted( const QString ) ), this, SLOT( newGameTitleAccepted( const QString ) ));
    }
    else
    {
        // Do nothing
    }

    // Set the current game name in the lineedit box
    *lastGameName = lclParent->text( );
    titleEdit->setGameNameText( *lastGameName );

    titleEdit->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Slot function for openning a game icon edit window.
 */
void gameNameContextMenu::gameIconChangeEvent( )
{
    if( iconEdit == nullptr )
    {
        iconEdit = new game_icon_edit;
        connect( iconEdit, SIGNAL( gameIconUpdated( const QString& ) ), this, SLOT( newGameIconAccepted( const QString& ) ));
    }
    else
    {
        // Do nothing
    }

    // Set the current game icon in the lineedit box
    *lastGameIcon = lclParent->gameIcon;
    iconEdit->setGameIconText( *lastGameIcon );

    iconEdit->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      15/04/2020
 *
 *  \par       Description:
 *             Slot function for openning a launch command edit window.
 */
void gameNameContextMenu::launchCommandChangeEvent( )
{
    if( launchEdit == nullptr )
    {
        launchEdit = new launch_command_edit;
        connect( launchEdit, SIGNAL( updateLaunchCommand( const QString& ) ), this, SLOT( newLaunchCommandAccepted( const QString& ) ));
    }
    else
    {
        // Do nothing
    }

    // Set the current launch command in the lineedit box
    *lastLaunchCommand = lclParent->launchCommand;
    launchEdit->updateDispLaunchCommand( *lastLaunchCommand );

    launchEdit->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Slot function for openning a command line args edit window.
 */
void gameNameContextMenu::cmdLineArgsChangeEvent( )
{
    if( cmdArgsEdit == nullptr )
    {
        cmdArgsEdit = new cmd_line_args_edit;
        connect( cmdArgsEdit, SIGNAL( updateCmdLineArgs( const QString& ) ), this, SLOT( newCmdLineArgsAccepted( const QString& ) ));
    }
    else
    {
        // Do nothing
    }

    // Set the current command line args in the lineedit box
    *lastCmdLineArgs = lclParent->launchCommandArgs;
    cmdArgsEdit->setCmdLineArgsText( *lastCmdLineArgs );

    cmdArgsEdit->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Slot function for openning a game description dialogue box.
 */
void gameNameContextMenu::gameDescChangeEvent( )
{
    if( gameDescEdit == nullptr )
    {
        gameDescEdit = new game_description_edit;
        connect( gameDescEdit, SIGNAL( updateGameDescription( const QString& ) ), this, SLOT( newGameDescAccepted( const QString& ) ));
    }
    else
    {
        // Do nothing
    }

    // Set the current game description in the lineedit box
    *lastGameDescription = lclParent->gameDescription;
    gameDescEdit->updateDispGameDescription( *lastGameDescription );

    gameDescEdit->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot function for openning acking an accepted game name change.
 */
void gameNameContextMenu::newGameTitleAccepted( const QString string )
{
    // If the user has changed the string, make a note of this
    if( string != *lastGameName )
    {
        // Update the game name in the database
        emit( gameContextUpdateGameName( string ) );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot function for openning acking an accepted game name change.
 */
void gameNameContextMenu::newGameIconAccepted( const QString &string )
{
    // If the user has changed the string, make a note of this
    if( string != *lastGameIcon )
    {
        // Update the game icon in the database
        emit( gameContextUpdateGameIcon( string ) );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot function for openning acking an accepted game name change.
 */
void gameNameContextMenu::newLaunchCommandAccepted( const QString &string )
{
    // If the user has changed the string, make a note of this
    if( string != *lastLaunchCommand )
    {
        // Update the game launch script in the database
        emit( gameContextUpdateLaunchScript( string ) );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Slot function for openning acking an accepted change to cmd line args.
 */
void gameNameContextMenu::newCmdLineArgsAccepted( const QString &string )
{
    // If the user has changed the string, make a note of this
    if( string != *lastCmdLineArgs )
    {
        // Update the game launch script command line args in the database
        emit( gameContextUpdateCmdLineArgs( string ) );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      17/04/2020
 *
 *  \par       Description:
 *             Slot function for openning acking an accepted game description.
 */
void gameNameContextMenu::newGameDescAccepted( const QString &string )
{
    // If the user has changed the string, make a note of this
    if( string != *lastGameDescription )
    {
        // Update the game game desc in the database
        emit( gameContextUpdateGameDesc( string ) );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Destructor for the gameNameContextMenu class
 */
gameNameContextMenu::~gameNameContextMenu( )
{
    delete launchGame;
    delete editGameLaunchParams;
    delete removeGame;

    if( titleEdit != nullptr )
    {
        delete titleEdit;
    }
    else
    {
        // Do nothing
    }
    if( iconEdit != nullptr )
    {
        delete iconEdit;
    }
    else
    {
        // Do nothing
    }
    if( launchEdit != nullptr )
    {
        delete launchEdit;
    }
    else
    {
        // Do nothing
    }
    if( editCommandLineArgs != nullptr )
    {
        delete editCommandLineArgs;
    }
    else
    {
        // Do nothing
    }
    if( editGameDescription != nullptr )
    {
        delete editGameDescription;
    }
    else
    {
        // Do nothing
    }

    delete lastGameName;
    delete lastGameIcon;
    delete lastLaunchCommand;
    delete lastCmdLineArgs;
    delete lastGameDescription;
}
