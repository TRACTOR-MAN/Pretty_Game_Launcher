// Forward decleration of the QSqlDatabase class
class QSqlDatabase;

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
        
        // Constant pointer to a database
        QSqlDatabase * const my_db;

    private:
        // Copy constructor defined but not used, to protect against undefined 
        // side effects
        sqLiteDbInterface( const sqLiteDbInterface & obj );
};