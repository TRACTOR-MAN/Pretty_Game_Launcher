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
    }

    // Show the file dialog
    fileDialog->show( );
}