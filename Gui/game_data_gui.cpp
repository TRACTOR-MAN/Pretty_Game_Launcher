#include <QtCore>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>

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
gameDataGuiWidget::gameDataGuiWidget( sqLiteDbInterface &psdDatabase, MainWindow &psdMainWin, application_theme_c &psdTheme, QWidget *parent ) :
    QWidget(parent),
    scrollAreaMaxWidth( 200 ),
    horizLayout_p( new QHBoxLayout ),
    scrollArea( new QScrollArea ),
    lclTheme( psdTheme ),
    lclMainWindow( psdMainWin ),
    gameNameWidget( new gameTitleWidget( *this, (scrollAreaMaxWidth - 15) )),
    prettyWidget( new gamePrettyWidget( *this, lclMainWindow, lclTheme ) ),
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
    // Ensure the key widgets are showing
    prettyWidget->launchButton->show();
    prettyWidget->playTimeBox->show();
    prettyWidget->gameDescriptionBox->show();

    prettyWidget->changeGameIconAndYtVideo( buttonInformation );
    prettyWidget->changeGameInfo( buttonInformation );
    prettyWidget->changePlayTime( buttonInformation );
    prettyWidget->updateTheme( buttonInformation );

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
        // Do nothing
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

        // Now update game icon button
        thisNameButton->gameIcon = data.gameIconPath;
    }
    else
    {
        // Do nothing
    }

    // Now launch command
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

    // Now game text colour and background wallpaper
    if( thisNameButton->gameTextColor != data.gameTextColor )
    {
        // First update the database with the new data
        lclDatabase.changeGameColour( thisNameButton->text(), data.gameTextColor );

        // Create a current stylesheet QString
        QString CurrentStyleSheet( prettyWidget->styleSheet() );

        // Obtain the current style sheet in use
        QString styleText;
        prettyWidget->prepTextColourStlSht( styleText, thisNameButton->gameTextColor, thisNameButton->gameWallpaper );

        // Updat the current display if we are currently displaying data for this button
        if( styleText == prettyWidget->styleSheet() )
        {
            update_pretty_info_b = true;
        }
        else
        {
            // Game text colour not the same
        }

        // Now update the text colour and background image
        thisNameButton->gameTextColor = data.gameTextColor;
        thisNameButton->gameWallpaper = data.GameWallpaper;
    }
    else
    {
        // Do nothing
    }

    // Now the Game description
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

    // Now the youtube video ID
    if( thisNameButton->youtubeVideoID != data.youtubeVideoID )
    {
        // First update the database with the new data
        lclDatabase.changeGameYtId( thisNameButton->text(), data.youtubeVideoID );

        if( prettyWidget->youtubeVideo->url() == QUrl(prettyWidget->URLString1 + thisNameButton->youtubeVideoID + prettyWidget->URLString2NoAutoplay ) )
        {
            update_pretty_info_b = true;
        }
        else
        {
            // Game desc not the same
        }

        // Now update the youtube video ID
        thisNameButton->youtubeVideoID = data.youtubeVideoID;
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
                                               QString gameTextColor,
                                               QString gameWallpaper,
                                               QString gameScreenshot,
                                               QString gameYoutubeVideo,
                                               QWidget *parent
                                             )
{
    lclDatabase.addNewGame( gameTitle, launchCommand, launchCommandArgs, gameDescription, gameIcon, gameTextColor, gameWallpaper, gameScreenshot, gameYoutubeVideo, parent );

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
    if( lclDatabase.displayData_v.empty( ) == false )
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
    nameButton->gameScreenshot = guiInformation.gameScreenShot;
    nameButton->youtubeVideoID = guiInformation.youtubeVideoID;
    nameButton->gameWallpaper = guiInformation.GameWallpaper;
    nameButton->gameTextColor = guiInformation.gameTextColor;
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
gamePrettyWidget::gamePrettyWidget( QWidget &parent, MainWindow &psdMainWin, application_theme_c &psdTheme ) :
    QLabel( &parent ),
    vertLayout( new QVBoxLayout ),
    timeVertLayout( new QVBoxLayout ),
    gameDescriptionBox( new QGroupBox( "Game Description" ) ),
    playTimeBox( new QGroupBox( "Game Play Time" ) ),
    gameImageVLayout( new QVBoxLayout ),
    maximumImageWidthMinimised( 350 ),
    maximumImageHeightMinimised( 200 ),
    maximumImageWidthMaximised( 500 ),
    maximumImageHeightMaximised( 350 ),
    lclTheme( psdTheme ),
    gameImageBorder( new QWidget ),
    gameImage( new QLabel ),
    launchButton( new LaunchButtonWidget("Launch Game") ),
    gameInformation( new QLabel ),
    playTime( new QLabel ),
    youtubeVideo( new QWebEngineView ),
    youtubeVideoBorder( new QLabel ),
    layout( new QGridLayout(this) ),
    currentIconPath( new QString ),
    URLString1( new QString("https://www.youtube-nocookie.com/embed/") ),
    URLString2NoAutoplay( new QString("?mute=1") ),
    URLString2Autoplay( new QString("?autoplay=1&mute=1") ),
    lclMainWindow( psdMainWin ),
    last_windowed_state( false )
{
    // Set the info widget to wrap text
    gameInformation->setWordWrap(true);
    // Set the maximum size of the launch button
    launchButton->setMinimumSize( 160, 40 );
    // Set the minimum size of the game time widget
    playTime->setMinimumSize( 160, 40 );
    // Set the game time widget to central justify text
    playTime->setAlignment(Qt::AlignCenter);

    // Create a handler for rescale events
    connect( &lclMainWindow, SIGNAL( changeEvent( QEvent* ) ), this, SLOT( rescaleYtVideoAndIcon( QEvent* ) ) );

    // Place the game information into the game description group box
    vertLayout->addWidget( gameInformation, 0, Qt::AlignTop );
    // Set the layout of the description box
    gameDescriptionBox->setLayout( vertLayout );

    // Place the play time into the play time group box
    timeVertLayout->addWidget( playTime, 0, Qt::AlignHCenter );
    // Set the layout of the play time box
    playTimeBox->setLayout( timeVertLayout );

    // Set up the V layout and image
    gameImageVLayout->addWidget( gameImage, 0, Qt::AlignHCenter );
    gameImageBorder->setLayout( gameImageVLayout );

    // Start with the youtube video border hidden
    youtubeVideoBorder->hide();

    // Add the common widgets
    layout->addWidget( launchButton, 0, 0, 1, 1, Qt::AlignCenter );
    layout->addWidget( gameDescriptionBox, 2, 0, 1, 4);
    layout->addWidget( playTimeBox, 0, 3, 1, 1, Qt::AlignCenter );

    // Hide the widgets during start up
    launchButton->hide();
    gameDescriptionBox->hide();
    playTimeBox->hide();

    // Load a dummy page to initialise the QWebEngineView, without this the application is initially
    // quite slow to load the first page.
    youtubeVideo->load(QUrl("https://duckduckgo.com"));
    youtubeVideo->hide();

    this->setLayout(layout);
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      19/04/2020
 *
 *  \par       Description:
 *             Paint event function for paint event override
 */
void gamePrettyWidget::paintEvent( QPaintEvent * )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      19/04/2020
 *
 *  \par       Description:
 *             Slot function for rescaling certain pretty widgets
 */
void gamePrettyWidget::rescaleYtVideoAndIcon( QEvent* event )
{
    // If the event is a window state change
    if (event->type() == QEvent::WindowStateChange)
    {

        // Just here incase we ever need to access the raw window state info
        #if(0)
        // Cast the event to a window state change event
        QWindowStateChangeEvent* ev = static_cast<QWindowStateChangeEvent*>(event);
        qDebug() << ev->oldState();
        qDebug() << lclMainWindow.windowState();
        qDebug() << (lclMainWindow.windowState() == Qt::WindowFullScreen);
        qDebug() << (lclMainWindow.windowState() == Qt::WindowMaximized);
        qDebug() << (lclMainWindow.windowState() == Qt::WindowNoState);
        #endif

        // If we are maximising or entering full screen
        if(
            (lclMainWindow.windowState() == Qt::WindowFullScreen)
            ||
            (lclMainWindow.windowState() == Qt::WindowMaximized)
          )
        {
            // If there is an icon in use
            if( *currentIconPath != "" )
            {
                // When using a toggling image and screenshot, may need to change currentIconPath
                QPixmap pic(*currentIconPath);
                gameImage->setPixmap( pic.scaled( maximumImageWidthMaximised, maximumImageHeightMaximised, Qt::KeepAspectRatio ) );
                gameImageBorder->repaint( );

                if( youtubeVideo != nullptr )
                {
                    youtubeVideoBorder->setMinimumSize( gameImage->pixmap()->width() + 18, gameImage->pixmap()->height() + 18 );
                    youtubeVideoBorder->setMaximumSize( gameImage->pixmap()->width() + 18, gameImage->pixmap()->height() + 18 );
                    youtubeVideo->setMaximumSize( gameImage->pixmap()->width(), gameImage->pixmap()->height() );
                    youtubeVideoBorder->repaint();
                }
                else
                {
                    // Do nothing
                }
            }
            // If there is a youtube video in use
            else
            if(
                (youtubeVideo != nullptr)
                &&
                (youtubeVideo->url() != QUrl(""))
              )
            {
                youtubeVideoBorder->setMinimumSize( maximumImageWidthMaximised + 18, maximumImageHeightMaximised + 18 );
                youtubeVideoBorder->setMaximumSize( maximumImageWidthMaximised + 18, maximumImageHeightMaximised + 18 );
                youtubeVideo->setMaximumSize( maximumImageWidthMaximised, maximumImageHeightMaximised );
                youtubeVideoBorder->repaint();
            }
            else
            {
                // Do nothing
            }
        }
        // We must be in normal mode
        else
        {
            // If there is an icon in use
            if( *currentIconPath != "" )
            {
                // When using a toggling image and screenshot, may need to change currentIconPath
                QPixmap pic(*currentIconPath);
                gameImage->setPixmap( pic.scaled( maximumImageWidthMinimised, maximumImageHeightMinimised, Qt::KeepAspectRatio ) );
                gameImageBorder->repaint( );

                if( youtubeVideo != nullptr )
                {
                    youtubeVideoBorder->setMinimumSize( gameImage->pixmap()->width() + 18, gameImage->pixmap()->height() + 18 );
                    youtubeVideoBorder->setMaximumSize( gameImage->pixmap()->width() + 18, gameImage->pixmap()->height() + 18 );
                    youtubeVideo->setMaximumSize( gameImage->pixmap()->width(), gameImage->pixmap()->height() );
                    youtubeVideoBorder->repaint();
                }
                else
                {
                    // Do nothing
                }
            }
            // If there is a youtube video in use
            else
            if(
                (youtubeVideo != nullptr)
                &&
                (youtubeVideo->url() != QUrl(""))
              )
            {
                youtubeVideoBorder->setMinimumSize( maximumImageWidthMinimised + 18, maximumImageHeightMinimised + 18 );
                youtubeVideoBorder->setMaximumSize( maximumImageWidthMinimised + 18, maximumImageHeightMinimised + 18 );
                youtubeVideo->setMaximumSize( maximumImageWidthMinimised, maximumImageHeightMinimised );
                youtubeVideoBorder->repaint();
            }
            else
            {
                // Do nothing
            }
        }
    }
}


/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      16/02/2020
 *
 *  \par       Description:
 *             Member function for changing the image widget
 */
void gamePrettyWidget::changeGameIconAndYtVideo( gameNameButtonWidget &buttonInformation )
{
    // Flags noting whether or not to add the widgets
    bool gameIconToAdd = false;
    bool videoToAdd = false;

    // Initially remove the image border
    gameImageBorder->hide();
    layout->removeWidget( gameImageBorder );

    // Only Add the picture if there is one assigned
    if( buttonInformation.gameIcon != "" )
    {
        QPixmap picture( buttonInformation.gameIcon );

        if(
            (lclMainWindow.isMaximized() != false)
            ||
            (lclMainWindow.isFullScreen() != false)
          )
        {
            gameImage->setPixmap( picture.scaled(maximumImageWidthMaximised, maximumImageHeightMaximised, Qt::KeepAspectRatio) );
        }
        else
        {
            gameImage->setPixmap( picture.scaled(maximumImageWidthMinimised, maximumImageHeightMinimised, Qt::KeepAspectRatio) );
        }

        gameIconToAdd = true;
    }
    else
    {
        QPixmap picture( "" );

        gameImage->setPixmap( picture );
    }

    // Set the current icon path
    *currentIconPath = buttonInformation.gameIcon;

    // Delete any present youtube videos widgets
    if( youtubeVideo != nullptr )
    {
        layout->removeWidget( youtubeVideoBorder );
        layout->removeWidget( youtubeVideo );
        delete youtubeVideo;
        youtubeVideo = nullptr;
    }
    else
    {
        // Do nothing
    }

    // Only add the youtube video if there is one assigned
    if( buttonInformation.youtubeVideoID != "" )
    {
        // This is a requirement for the QWebEngineView to allow it to be interacted with,
        // i.e. it needs to be deleted, then new'd.
        youtubeVideo = new QWebEngineView;

        // Load the URL
        youtubeVideo->load(QUrl(*URLString1 + buttonInformation.youtubeVideoID + *URLString2NoAutoplay ));

        // Constrain the size of the youtube video to the size of the game image
        if( gameIconToAdd != false )
        {
            youtubeVideoBorder->setMinimumSize( gameImage->pixmap()->width() + 18, gameImage->pixmap()->height() + 18 );
            youtubeVideo->setMaximumSize( gameImage->pixmap()->width(), gameImage->pixmap()->height() );
        }
        else
        {
            if(
                ( lclMainWindow.isMaximized() != false )
                ||
                ( lclMainWindow.isFullScreen() != false )
              )
            {
                youtubeVideoBorder->setMinimumSize( maximumImageWidthMaximised + 18, maximumImageHeightMaximised + 18 );
                youtubeVideo->setMaximumSize( maximumImageWidthMaximised, maximumImageHeightMaximised );
            }
            else
            {
                youtubeVideoBorder->setMinimumSize( maximumImageWidthMinimised + 18, maximumImageHeightMinimised + 18 );
                youtubeVideo->setMaximumSize( maximumImageWidthMinimised, maximumImageHeightMinimised );
            }

        }

        // Show the border
        youtubeVideoBorder->show();

        // Make a note to add the video
        videoToAdd = true;
    }
    else
    {

    }

    // Now add the widgets
    if(
        (gameIconToAdd != false)
        &&
        (videoToAdd != false)
      )
    {
        // Add the widgets
        layout->addWidget( gameImageBorder, 1, 0, 1, 2, Qt::AlignCenter );
        layout->addWidget( youtubeVideoBorder, 1, 2, 1, 2, Qt::AlignCenter );
        layout->addWidget( youtubeVideo, 1, 2, 1, 2, Qt::AlignCenter );

        gameImageBorder->show();
    }
    else
    if(
        (gameIconToAdd != false)
        &&
        (videoToAdd == false)
      )
    {
        // Add the widgets
        layout->addWidget( gameImageBorder, 1, 1, 1, 2, Qt::AlignCenter );

        // Show the image
        gameImageBorder->show();
    }
    else
    if(
        (gameIconToAdd == false)
        &&
        (videoToAdd != false)
      )
    {
        // Add the widgets
        layout->addWidget( youtubeVideoBorder, 1, 1, 1, 2, Qt::AlignCenter );
        layout->addWidget( youtubeVideo, 1, 1, 1, 2, Qt::AlignCenter );
    }
    else
    {
        // Do nothing
    }
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      19/04/2020
 *
 *  \par       Description:
 *             Function for updating the wallpaper and text color
 */
void gamePrettyWidget::updateTheme( gameNameButtonWidget &buttonInformation )
{
    // Initially set-up the theme in line with the current selection
    if( lclTheme.current_theme_e == DARK )
    {
        QFile file(":/dark.qss");
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream stream(&file);
        setStyleSheet(stream.readAll());
    }
    else
    if( lclTheme.current_theme_e == LIGHT )
    {
        QFile file(":/light.qss");
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream stream(&file);
        setStyleSheet(stream.readAll());
    }
    else
    {
        // Do nothing
    }


    // Configure the style sheets of all widgets
    gameDescriptionBox->setStyleSheet("background-color:rgba(255,255,255,30);");
    playTimeBox->setStyleSheet("background-color:rgba(255,255,255,30);");
    launchButton->setStyleSheet("background-color:rgba(255,255,255,30);");
    gameInformation->setStyleSheet("background-color:rgba(255,255,255,0);");
    playTime->setStyleSheet("background-color:rgba(255,255,255,0);");
    gameImageBorder->setStyleSheet("background-color:rgba(0,0,0,80);");
    youtubeVideoBorder->setStyleSheet("background-color:rgba(0,0,0,80);");

    QString styleText;
    prepTextColourStlSht( styleText, buttonInformation.gameTextColor, buttonInformation.gameWallpaper );

    // Set the background image
    setStyleSheet( styleText );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      04/01/2021
 *
 *  \par       Description:
 *             Function for preparing a stylesheet for updating the game wallpaper and text colour
 */
void gamePrettyWidget::prepTextColourStlSht( QString &styleText, const QString &Colour , const QString &Wallpaper )
{
    if( Wallpaper != "\0" )
    {
        styleText = "gamePrettyWidget{background-image:url(\"" + Wallpaper + "\"); background-position: center;} ";
    }
    else
    {
        // Do nothing
    }

    if( Colour != "\0" )
    {
        styleText += "QLabel{color: " + Colour + ";} ";

        styleText += "QPushButton{color: " + Colour + ";} ";

        styleText += "QGroupBox{color: " + Colour+ ";} ";
    }
    else
    {
        // Do nothing, no text color demanded
    }
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
    delete gameImageVLayout;
    delete launchButton;
    delete gameImage;
    delete gameImageBorder;
    delete gameInformation;
    delete currentIconPath;
    if( youtubeVideo != nullptr )
    {
        delete youtubeVideo;
    }
    delete youtubeVideoBorder;
    delete URLString1;
    delete URLString2NoAutoplay;
    delete URLString2Autoplay;
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
 *             Slot function for opening a game parameters edit dialog.
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
    // Get the filename alone from the full icon start path
    QString fileName( fullStartPath.fileName( ) );
    // Setup a start directory string
    QString startDirectory( lclParent->gameIcon );
    // Remove the filename from the string
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

    // Set the screenshot image name
    lclEditDialogUi->gameScreenshot->setText( lclParent->gameScreenshot );

    // Set the game text colour    
    int index = lclEditDialogUi->textColorComboBox->findText( lclParent->gameTextColor );
    if ( index != -1 ) { // -1 for not found
       lclEditDialogUi->textColorComboBox->setCurrentIndex(index);
    }

    // Set the wallpaper image name
    lclEditDialogUi->gameWallpaper->setText( lclParent->gameWallpaper );

    // Set the youtube video ID
    lclEditDialogUi->youtubeID->setText( lclParent->youtubeVideoID );

    // Show the dialog
    gameEditDialog->show( );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      14/04/2020
 *
 *  \par       Description:
 *             Slot function for opening acking an accepted game data change.
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
    gameInformation->gameScreenShot = lclEditDialogUi->gameScreenshot->text( );
    gameInformation->GameWallpaper = lclEditDialogUi->gameWallpaper->text( );
    gameInformation->youtubeVideoID = lclEditDialogUi->youtubeID->text( );
    gameInformation->gameTextColor = lclEditDialogUi->textColorComboBox->currentText();

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
