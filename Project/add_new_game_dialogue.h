#ifndef ADD_NEW_GAME_DIALOGUE_H
#define ADD_NEW_GAME_DIALOGUE_H

#include <QDialog>

namespace Ui {
class Add_New_Game_Dialogue;
}

class Add_New_Game_Dialogue : public QDialog
{
    Q_OBJECT

public:
    explicit Add_New_Game_Dialogue(QWidget *parent = nullptr);
    ~Add_New_Game_Dialogue();

private:
    Ui::Add_New_Game_Dialogue *ui;
};

#endif // ADD_NEW_GAME_DIALOGUE_H
