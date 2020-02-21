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
gameDataGuiWidget::gameDataGuiWidget( QWidget &parent ) :
    QWidget(&parent),
    scrollAreaMaxWidth( 200 ),
    horizLayout_p( new QHBoxLayout ),
    scrollArea( new QScrollArea ),
    gameNameWidget( new gameTitleWidget( *this, (scrollAreaMaxWidth - 15) )),
    prettyWidget( new gamePrettyWidget( *this )),
    myDatabase( new sqLiteDbInterface )
{
    // Only access the game, data, if it is present
    if( myDatabase->displayData_vp[0] != nullptr )
    {
        // Itterate through the entire database, and add every game name
        for( uint16_t i = 0U; i < myDatabase->displayData_vp.size(); i++ )
        {
            gameNameWidget->addGameTitle( *myDatabase->displayData_vp[i] );
        }

        // Set the initial image information for the pretty widget
        prettyWidget->changeGameIcon( *myDatabase->displayData_vp[0] );

        // Change the game information for the info widget
        prettyWidget->changeGameInfo( *myDatabase->displayData_vp[0] );

        // Change the play time
        prettyWidget->changePlayTime( *myDatabase->displayData_vp[0] );
    }

    // Add the game name widget to the scroll area
    scrollArea->setMaximumWidth( scrollAreaMaxWidth );
    scrollArea->setWidget( gameNameWidget );

    // Add the widgets to the main view
    horizLayout_p->addWidget( scrollArea );
    horizLayout_p->addWidget( prettyWidget );

    this->setLayout( horizLayout_p );

    this->show();
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
    delete myDatabase;
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
    QPushButton * pushButton = new QPushButton( guiInformation.gameName );

    // Add the push button to the layout
    layout->addWidget( pushButton );

    // Add the button pointer to the button pointer list
    buttonPtrList.push_back( pushButton );
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
    launchButton( new QPushButton("Launch Game") ),
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
void gamePrettyWidget::changeGameIcon( GUI_game_information_st &guiInformation )
{

    // Only Add the picture if there is one assigned
    if( guiInformation.gameIconPath != "" )
    {
        QPixmap picture( guiInformation.gameIconPath );

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
void gamePrettyWidget::changeGameInfo( GUI_game_information_st &guiInformation )
{
    // Only set the text if there is some to show
    if( guiInformation.gameDescription != "" )
    {
        gameInformation->setText( guiInformation.gameDescription );
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
void gamePrettyWidget::changePlayTime( GUI_game_information_st &guiInformation )
{
    // Only set the text if there is some to show
    if( guiInformation.playTime != "" )
    {
        playTime->setText( guiInformation.playTime );
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
