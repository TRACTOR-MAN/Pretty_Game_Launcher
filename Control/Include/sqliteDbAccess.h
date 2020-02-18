#ifndef SQ_LITE_DB_ACCESS_H
#define SQ_LITE_DB_ACCESS_H

// Forward decleration of the QSqlDatabase class
class QSqlDatabase;


// Structure containing the information to display in the GUI
struct GUI_game_information_st
{
    QString gameName;
    QString gameIconPath;
    QString gameDescription;
    QString playTime;
};

/*! 
 *  \author    Thomas Sutton
 *  \version   1.0
 *  \date      02/02/2020
 * 
 *  \par       Description:
 *             This class contains the interface between the sqLite database
 *             and the Qt qui application.
 */

class sqLiteDbInterface
{
    public:
        sqLiteDbInterface( );
        ~sqLiteDbInterface( );

        // Read in the information that we need to display for each game
        void readGameGuiInformation( );
        
        // Constant pointer to an sqlite database
        QSqlDatabase * const my_db;
        // Constant pointer to a vector containing the information to display in the GUI
        std::vector<GUI_game_information_st> * const displayData_vp;

    private:
        // Copy constructor defined but not used, to protect against undefined 
        // side effects
        sqLiteDbInterface( const sqLiteDbInterface & obj );
};

#endif
