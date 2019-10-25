/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionTest_1;
    QAction *actionAdd_New_Game;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *taskMenu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1057, 774);
#ifndef QT_NO_TOOLTIP
        MainWindow->setToolTip(QString::fromUtf8(""));
#endif // QT_NO_TOOLTIP
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setInputMethodHints(Qt::ImhNone);
        actionTest_1 = new QAction(MainWindow);
        actionTest_1->setObjectName(QString::fromUtf8("actionTest_1"));
        actionTest_1->setCheckable(false);
        actionTest_1->setEnabled(false);
        actionAdd_New_Game = new QAction(MainWindow);
        actionAdd_New_Game->setObjectName(QString::fromUtf8("actionAdd_New_Game"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1057, 22));
        taskMenu = new QMenu(menuBar);
        taskMenu->setObjectName(QString::fromUtf8("taskMenu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setMouseTracking(true);
        statusBar->setTabletTracking(false);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(taskMenu->menuAction());
        taskMenu->addAction(actionAdd_New_Game);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Pretty Game Launcher", nullptr));
        actionTest_1->setText(QApplication::translate("MainWindow", "Test_1", nullptr));
        actionAdd_New_Game->setText(QApplication::translate("MainWindow", "Add New Game", nullptr));
        taskMenu->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
