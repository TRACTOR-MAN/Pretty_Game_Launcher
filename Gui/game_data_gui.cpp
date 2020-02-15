#include <QtCore>
#include <QPushButton>

#include "sqliteDbAccess.h"
#include "game_data_gui.h"


/**************** Globals ****************/
static sqLiteDbInterface my_games_database;

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
    horizLayout_p( new QHBoxLayout ),
    gameNameWidget( new gameTitleWidget( *this )),
    prettyWidget( new gamePrettyWidget( *this ))
{
    // Add the widgets to the main view
    horizLayout_p->addWidget( gameNameWidget );
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
}

/*!
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      08/02/2020
 *
 *  \par       Description:
 *             Constructor for the gameTitleWidget class
 */
gameTitleWidget::gameTitleWidget( QWidget &parent, int maximum_width ) :
    QWidget( &parent ),
    layout( new QVBoxLayout(this) )
{
    GUI_game_information_st *lcl_GUI_game_information_p = &my_games_database.displayData_vp->operator[](0);


    QPushButton *button_1 = new QPushButton( lcl_GUI_game_information_p->gameName );

    layout->addWidget( button_1 );

    // Set the maximum width of the game name
    max_width = maximum_width;
    this->setMaximumWidth( max_width );

    this->setLayout( layout );

    this->show( );
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
    layout( new QGridLayout(this) )
{
    QPushButton *button_1 = new QPushButton( "grid" );
    QPushButton *button_2 = new QPushButton( "layout" );

    layout->addWidget(button_1, 0, 0, 1, 1);
    layout->addWidget(button_2, 0, 1, 1, 1);

    this->setLayout(layout);
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

}
