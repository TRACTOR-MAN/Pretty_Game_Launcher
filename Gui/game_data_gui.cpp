#include <QtCore>
#include <QPushButton>

#include "game_data_gui.h"
#include "add_new_game_dialogue.h"

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
    connect( gameNameWidget, SIGNAL( gameTitleSigUpdateGameData( const GUI_game_information_st &, gameNameButtonWidget * const ) ), this, SLOT( changeGameData( const GUI_game_information_st &, gameNameButtonWidget * const ) ) );

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
 *  \date      18/04/2020
 *
 *  \par       Description:
 *             Slot for updating the game data for a specific game
 */
void gameDataGuiWidget::changeGameData( const GUI_game_information_st & data, gameNameButtonWidget * const thisNameButton )
{
    // Flag which notes whether or not to update the pretty information
    bool update_pretty_info_b = false;

    // Game name first
    if( thisNameButton->text( ) != data.gameName )
    {
        // First update the database with the new data
        lclDatabase.changeGameName( thisNameButton->text(), data.gameName );

        // Now update the game name in the game name button
        thisNameButton->setText( data.gameName );
    }
    else
    {
        // Do nothig
    }

    // Now Game Icon
    if( thisNameButton->gameIcon != data.gameIconPath )
    {
        // First update the database with the new data
        lclDatabase.changeGameIcon( thisNameButton->text(), data.gameIconPath );

        if( prettyWidget->currentIconPath == thisNameButton->gameIcon )
        {
            update_pretty_info_b = true;
        }
        else
        {
            // Images are not the same
        }
    }
    else
    {
        // Do nothing
    }

    if( thisNameButton->launchCommand != data.LaunchCommand )
    {
        // First update the database with the new data
        lclDatabase.changeLaunchScript( thisNameButton->text(), data.LaunchCommand );


        if( prettyWidget->launchButton->launchCommand == thisNameButton->launchCommand )
        {
            update_pretty_info_b = true;
        }
        else
        {
            // Launch script not the same
        }

        // Now update the launch command button
        thisNameButton->launchCommand = data.LaunchCommand;
    }
    else
    {
        // Do nothing
    }

    // Now command line args
    if( thisNameButton->launchCommandArgs != data.LaunchCommandArgs )
    {
        // First update the database with the new data
        lclDatabase.changeCmdArgs( thisNameButton->text(), data.LaunchCommandArgs );

        if( prettyWidget->launchButton->launchCommandArgs == thisNameButton->launchCommandArgs )
        {
            update_pretty_info_b = true;
        }
        else
        {
            // Launch script not the same
        }

        // Now update the launch command button
        thisNameButton->launchCommandArgs = data.LaunchCommandArgs;
    }
    else
    {
        // Do nothing
    }

    // Finally Game description
    if( thisNameButton->gameDescription != data.gameDescription )
    {
        // First update the database with the new data
        lclDatabase.changeGameDesc( thisNameButton->text(), data.gameDescription );

        if( prettyWidget->gameInformation->text() == thisNameButton->gameDescription )
        {
            update_pretty_info_b = true;
        }
        else
        {
            // Game desc not the same
        }

        // Now update the launch command button
        thisNameButton->gameDescription = data.gameDescription;
    }
    else
    {
        // Do nothing
    }

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
    connect( nameButton, SIGNAL(gameNameSigUpdateGameData( const GUI_game_information_st &, gameNameButtonWidget * const )), this, SLOT( gameTitleSlotUpdateGameData( const GUI_game_information_st &, gameNameButtonWidget * const ) ) );

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
 *  \date      18/04/2020
 *
 *  \par       Description:
 *             Slot function for updating a specific buttons game data.
 */
void gameTitleWidget::gameTitleSlotUpdateGameData( const GUI_game_information_st & data, gameNameButtonWidget * const thisNameButton  )
{
    emit gameTitleSigUpdateGameData( data, thisNameButton );
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
    connect( contextMenu, SIGNAL( gameContextUpdateGameData(  const GUI_game_information_st & ) ), this, SLOT( gameNameSlotUpdateGameData( const GUI_game_information_st & ) ) );
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
 *  \date      18/04/2020
 *
 *  \par       Description:
 *             Function for passing a game data update request up the Qt stack
 */
void gameNameButtonWidget::gameNameSlotUpdateGameData( const GUI_game_information_st &data )
{
    emit gameNameSigUpdateGameData( data, this );
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
    gameEditDialog( nullptr ),
    launchGame( new QAction( "Launch", parent ) ),
    removeGame( new QAction( "Remove Game", parent ) ),
    editGameLaunchData( new QAction( "Edit Game Launch Params", parent ) ),
    editGameLaunchParams( new QMenu( "Edit Game Launch Params", parent ) ),
    editGameName( new QAction( "Game Name", parent ) ),
    editGameIcon( new QAction( "Game Icon", parent ) ),
    editLaunchCommand( new QAction( "Launch Command", parent ) ),
    editCommandLineArgs( new QAction( "Command Line Args", parent ) ),
    editGameDescription( new QAction( "Game Description", parent ) ),
    lclParent( parent ),
    gameInformation( new GUI_game_information_st )
{
    // Set-up the context menu
    setContextMenuPolicy( Qt::CustomContextMenu );

    // Connect all of the actions
    connect( editGameLaunchData, SIGNAL( triggered( ) ), SLOT( editGameParamsEvent( ) ) );

    // Add the actions
    addAction( launchGame );
    // Add the sub menu
    addAction( editGameLaunchData );
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
 *             Slot function for openning a game parameters edit dialog.
 */
void gameNameContextMenu::editGameParamsEvent( )
{
    if( gameEditDialog == nullptr )
    {
        gameEditDialog = new( Add_New_Game_Dialogue );

        // Change the window title
        gameEditDialog->setWindowTitle( "Game Parameters Edit" );

        // Connect the signal to the slot
        connect( gameEditDialog, SIGNAL( accepted( ) ), this, SLOT( newGameDataAccepted(  ) ) );
    }
    else
    {
        // Do nothing
    }

    // Get a local copy of the UI so that it can be updated
    Ui::Add_New_Game_Dialogue *lclEditDialogUi = gameEditDialog->returnUIPointer( );

    // Set the current game title
    lclEditDialogUi->gameTitle->setText( lclParent->text( ) );

    // Set the current game Icon
    QFileInfo fullStartPath( lclParent->gameIcon );
    QString fileName( fullStartPath.fileName( ) );
    QString startDirectory( lclParent->gameIcon );
    startDirectory.remove( ( lclParent->gameIcon.size() - fileName.size() ), fileName.size() );

    // With the file params understood set the start directory and text
    lclEditDialogUi->gameIcon->setText( lclParent->gameIcon );
    gameEditDialog->setStartFileDirectory( startDirectory );

    // Set the current launch command
    lclEditDialogUi->launchCommand->setPlainText( lclParent->launchCommand );

    // Set the launch command args
    lclEditDialogUi->commandLineArgs->setText( lclParent->launchCommandArgs );

    // Set the game description
    lclEditDialogUi->gameDescription->setPlainText( lclParent->gameDescription );

    // Show the dialog
    gameEditDialog->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot function for openning acking an accepted game name change.
 */
void gameNameContextMenu::newGameDataAccepted( )
{
    Ui::Add_New_Game_Dialogue *lclEditDialogUi = gameEditDialog->returnUIPointer( );

    // Set all of the variables
    gameInformation->gameName = lclEditDialogUi->gameTitle->text( );
    gameInformation->gameIconPath = lclEditDialogUi->gameIcon->text( );
    gameInformation->LaunchCommand = lclEditDialogUi->launchCommand->toPlainText( );
    gameInformation->LaunchCommandArgs = lclEditDialogUi->commandLineArgs->text( );
    gameInformation->gameDescription = lclEditDialogUi->gameDescription->toPlainText( );

    // Emit the signal
    emit gameContextUpdateGameData( *gameInformation );
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

    if( gameEditDialog != nullptr )
    {
        delete gameEditDialog;
    }
    else
    {
        // Do nothing
    }

    delete gameInformation;
}
