#ifndef LAUNCH_COMMAND_EDIT_H
#define LAUNCH_COMMAND_EDIT_H

#include <QDialog>

namespace Ui {
class launch_command_edit;
}

class launch_command_edit : public QDialog
{
    Q_OBJECT

public:
    explicit launch_command_edit(QWidget *parent = nullptr);
    ~launch_command_edit();

    void updateDispLaunchCommand( const QString &text );

private:
    Ui::launch_command_edit *ui;

public slots:
    void acceptButtonPressed(  );

signals:
    void updateLaunchCommand( const QString &text );
};

#endif // LAUNCH_COMMAND_EDIT_H
