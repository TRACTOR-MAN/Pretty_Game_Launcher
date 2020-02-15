#ifndef GAME_DATA_GUI_H
#define GAME_DATA_GUI_H

#include <QWidget>
#include <QFormLayout>
#include <QHBoxLayout>

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
    gameTitleWidget( QWidget &parent, int maximum_width = 200 );
    ~gameTitleWidget( );

    // Layout object
    QVBoxLayout *layout;

    // Maximum width of the object
    int max_width;
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

    // Layout objects
    QHBoxLayout *horizLayout_p;

    // Widget objects for the game data GUI
    gameTitleWidget *gameNameWidget;
    gamePrettyWidget *prettyWidget;

};

#endif // GAME_DATA_GUI_H
