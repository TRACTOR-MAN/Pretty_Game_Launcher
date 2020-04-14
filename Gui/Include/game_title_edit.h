#ifndef GAME_TITLE_EDIT_H
#define GAME_TITLE_EDIT_H

#include <QDialog>

namespace Ui {
class game_title_edit;
}

class game_title_edit : public QDialog
{
    Q_OBJECT

public:
    explicit game_title_edit(QWidget *parent = nullptr);
    ~game_title_edit();

    void setGameNameText( QString &text );

signals:
    void gameTitleAccepted( const QString string );

private slots:
    void acceptButtonPressed(  );

private:
    Ui::game_title_edit *ui;
};

#endif // GAME_TITLE_EDIT_H
