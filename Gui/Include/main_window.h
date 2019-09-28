#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    // Macro to allow the QT meta object compiler to convert this 
    // class allong with the associated form to machine generated code.
    Q_OBJECT

public:
    // The explicit keyword here, prevents an object from being created
    // with the wrong type passed in, it prevents implicit type casting.
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// This custom keyword allows the QT meta object compiler to 
// be aware of the slots
private slots:
    // Custom Slot for button click
    void CustomFunction( void );


private:
    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
