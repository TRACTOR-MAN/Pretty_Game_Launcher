# Pretty_Game_Launcher
Qt Custom Game Launcher for launching games on Linux and Windows.

# Building ....
Currently the only dependancy, is Qt. Any version 5 of Qt will work.

Once the project has been cloned using git clone https://github.com/TRACTOR-MAN/Pretty_Game_Launcher.git the next steps are:
    * cd Pretty_Game-Launcher
    * Run git submodule update --init to update the project submodules
    * mkdir Build
    * cd Build
    # For Linux
    * qmake ../Project -spec linux-g++
    # For Windows
    * qmake ../Project -spec win32-g++
    # Finally
    * make

With the project Built, simply run ./Pretty_Game_Launcher to proceed.

The project is still under development, but games are added by clicking file->Add New Game then filling in the dialog boxes as stated.
