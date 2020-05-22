#-------------------------------------------------
#
# Project created by QtCreator 2019-09-12T22:10:01
#
#-------------------------------------------------

QT       += core gui widgets sql webenginewidgets

greaterThan(QT_MAJOR_VERSION, 5)

TARGET = Pretty_Game_Launcher
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 \
          qtquickcompiler

SOURCES += \
        ../Gui/main.cpp \
        ../Gui/main_window.cpp \
        ../Gui/add_new_game_dialogue.cpp \
        ../Control/sqliteDbAccess.cpp \
        ../Gui/game_data_gui.cpp

HEADERS += \
        ../Gui/Include/main_window.h \
        ../Gui/Include/add_new_game_dialogue.h \
        ../Control/Include/sqliteDbAccess.h \
        ../Gui/Include/game_data_gui.h \
        ../Gui/Include/main.h

INCLUDEPATH += \
        ../Gui/Include \
        ../Control/Include

FORMS += \
        ../UI/mainwindow.ui \
        ../UI/add_new_game_dialogue.ui

RESOURCES += \
       ../Icons/icons.qrc \
       ./Style_Sheets/breeze.qrc

