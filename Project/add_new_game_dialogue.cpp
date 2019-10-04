#include "add_new_game_dialogue.h"
#include "ui_add_new_game_dialogue.h"

Add_New_Game_Dialogue::Add_New_Game_Dialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_New_Game_Dialogue)
{
    ui->setupUi(this);
}

Add_New_Game_Dialogue::~Add_New_Game_Dialogue()
{
    delete ui;
}
