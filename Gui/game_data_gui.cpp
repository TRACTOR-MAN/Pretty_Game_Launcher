#include <QtCore>
#include <QPushButton>

#include "game_data_gui.h"


/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      07/02/2020
 *
 *  \par       Description:
 *             Constructor for the gameDatauiWidget class
 */
gameDataGuiWidget::gameDataGuiWidget( QWidget &parent, sqLiteDbInterface &psdDatabase  ) :
    QWidget(&parent),
    scrollAreaMaxWidth( 200 ),
    horizLayout_p( new QHBoxLayout ),
    scrollArea( new QScrollArea ),
    gameNameWidget( new gameTitleWidget( *this, (scrollAreaMaxWidth - 15) )),
    prettyWidget( new gamePrettyWidget( *this )),
    lclDatabase( psdDatabase )
{
    connect( gameNameWidget, SIGNAL(updatePrettyInformation( gameNameButtonWidget &)), this, SLOT(redrawPrettyInformation( gameNameButtonWidget &)) );

    // If there is data to process
    if(  lclDatabase.displayData_v.empty( ) != false )
    {
        // Itterate through the entire database, and add every game name
        for( uint16_t i = 0U; i < lclDatabase.displayData_v.size(); i++ )
        {
            gameNameWidget->addGameTitle( *lclDatabase.displayData_v[i] );
        }
    }
    else
    {
        // Do nothing
    }

    // Add the game name widget to the scroll area
    scrollArea->setMaximumWidth( scrollAreaMaxWidth );
    scrollArea->setWidget( gameNameWidget );

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
    prettyWidget->launchButton->launchScript = buttonInformation.launchScript;
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
    layout( new QVBoxLayout(this) )
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

    // Update the metadata with the metatata for this record
    nameButton->gameDescription = guiInformation.gameDescription;
    nameButton->playTime = guiInformation.playTime;
    nameButton->gameIcon = guiInformation.gameIconPath;
    nameButton->launchScript = guiInformation.LaunchScript;
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
 *  \date      07/02/2020
 *
 *  \par       Description:
 *             Destructor for the gameTitleWidget class
 */
gameTitleWidget::~gameTitleWidget( )
{
    delete layout;

    // Clean up all button objects
    for ( uint16_t i = 0; i < buttonPtrList.size(); i++)
    {
        delete buttonPtrList[i];
    }
}

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
    layout( new QGridLayout(this) )
{
    // Set the info widget to wrap text
    gameInformation->setWordWrap(true);
    // Set the maximum size of the launch button
    launchButton->setMinimumSize( 160, 40 );
    // Set the minimum size of the game time widget
    playTime->setMinimumSize( 160, 40 );
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

        gameImage->setPixmap( picture );
    }
    else
    {
        QPixmap picture( "" );

        gameImage->setPixmap( picture );
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
    delete launchButton;
    delete gameImage;
    delete gameInformation;
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Constructor for the gameNameButtonWidget class
 */
gameNameButtonWidget::gameNameButtonWidget( const QString & text ) :
    QPushButton( text )
{
    // Connect the signal to the slot for this button
    connect( this, SIGNAL(clicked( )), this, SLOT(buttonClicked( )) );
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      23/02/2020
 *
 *  \par       Description:
 *             Slot function to emit button clicked information
 */
void gameNameButtonWidget::buttonClicked( )
{
    emit nameBtnclicked( *this );
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

}

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

        proc_and_thread_data_ps->process->start( launchCommand );

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
