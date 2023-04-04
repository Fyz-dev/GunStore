#ifndef MAINWINDOWMEDIATOR_H
#define MAINWINDOWMEDIATOR_H

#include "mainmenuviewmodel.h"
#include "WindowState.h"

class MainWindow;

class MainWindowMediator
{
public:
    MainWindowMediator(MainMenuViewModel* mainMenuViewModel);

    void update(WindowState& windowState);
    void settingSignalSlots(MainWindow* mainWindow);

private:
    MainMenuViewModel* mainMenuViewModel;
};

#endif // MAINWINDOWMEDIATOR_H
