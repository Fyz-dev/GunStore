#include "mainwindowmediator.h"
#include "mainwindow.h"

MainWindowMediator::MainWindowMediator(MainMenuViewModel* mainMenuViewModel) :
    mainMenuViewModel(mainMenuViewModel)
{}

void MainWindowMediator::settingSignalSlots(MainWindow* mainWindow)
{
    MainWindow::connect(mainMenuViewModel, &MainMenuViewModel::modelChangedSignal, mainWindow, &MainWindow::modelChangedSlots);
    MainWindow::connect(mainMenuViewModel, &MainMenuViewModel::addCheckBoxSignal, mainWindow, &MainWindow::addCheckBoxSlots);
    MainWindow::connect(mainMenuViewModel, &MainMenuViewModel::clearCheckBoxSignal, mainWindow, &MainWindow::clearCheckBoxSlots);
}

void MainWindowMediator::update(WindowState& windowState)
{
    switch (windowState) {
    case WindowState::MainMenuWindow:
        mainMenuViewModel->update();
        break;
    }
}
