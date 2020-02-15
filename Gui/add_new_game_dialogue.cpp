#include "add_new_game_dialogue.h"
#include "ui_add_new_game_dialogue.h"

Add_New_Game_Dialogue::Add_New_Game_Dialogue( QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::Add_New_Game_Dialogue),
    fileDialog(nullptr)
{
    ui->setupUi(this);
}

Add_New_Game_Dialogue::~Add_New_Game_Dialogue( )
{
    delete ui;
    delete fileDialog;
}

void Add_New_Game_Dialogue::searchForFile( )
{
    if( fileDialog == nullptr )
    {
        fileDialog = new( QFileDialog );
        // Ensure that file open events are connected to a callback function
        connect( fileDialog, SIGNAL(fileSelected( QString )), this, SLOT(updateSelectedFile( QString )) );
    }

    // Show the file dialog
    fileDialog->show( );
}

void Add_New_Game_Dialogue::updateSelectedFile( const QString selectedFile )
{
    // Emit the textChanged signal, passing in the selected file.
    emit textChanged( selectedFile );
}
