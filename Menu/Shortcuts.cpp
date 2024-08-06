//
// Created by Fardeen Bablu on 8/4/24.
//

#include "Shortcuts.h"
#include <QMenu>

Shortcuts::Shortcuts(QObject *parent) :  QObject(parent) {
    createActions();

    createMenus();

    auto mainWindow = qobject_cast<MainWindow*>(parent);
    auto enterSet = qobject_cast<EnterSetPage*>(parent);

    if (mainWindow) {
        connect(newSetAct, &QAction::triggered, mainWindow, &MainWindow::showCreateSetPage);
//        connect(searchAct, &QAction::triggered, mainWindow, &MainWindow::showSearch);
    }
    else if (enterSet) {
        connect(mcAct, &QAction::triggered, enterSet, &EnterSetPage::openMCPage);
        connect(inverseMCAct, &QAction::triggered, enterSet, &EnterSetPage::openInversePage);
        connect(flashAct, &QAction::triggered, enterSet, &EnterSetPage::openFlashcardsPage);
    }
}

void Shortcuts::createActions() {
    newSetAct = new QAction(tr("&New Set"), this);
//    connect(newSetAct, &QAction::triggered, this, &Shortcuts::newSetCmd);
    mcAct = new QAction(tr("&Multiple Choice"), this);
//    connect(mcAct,  &QAction::triggered, this, &Shortcuts::mcCmd);
    inverseMCAct = new QAction(tr("&Inverse Multiple Choice"), this);
//    connect(inverseMCAct, &QAction::triggered, this, &Shortcuts::inverseMCCmd);
    flashAct = new QAction(tr("&Flashcards"), this);
//    connect(flashAct, &QAction::triggered, this, &Shortcuts::flashCmd);
    searchAct = new QAction(tr("&Search"), this);
//    connect(searchAct, &QAction::triggered, this, &Shortcuts::searchCmd);
}

void Shortcuts::createMenus() {
    setMenu = new QMenu(tr("&Sets"));
    setMenu->addAction(newSetAct);

    studyMethodsMenu = new QMenu(tr("&Study"));
    studyMethodsMenu->addAction(mcAct);
    studyMethodsMenu->addAction(inverseMCAct);
    studyMethodsMenu->addAction(flashAct);
    studyMethodsMenu->addAction(searchAct);
}




void Shortcuts::newSetCmd() {
    emit newSetAct->trigger();
}

void Shortcuts::mcCmd() {
    emit mcAct->trigger();
}

void Shortcuts::inverseMCCmd() {
    emit inverseMCAct->trigger();
}

void Shortcuts::flashCmd() {
    emit flashAct->trigger();
}

void Shortcuts::searchCmd() {
    emit searchAct->trigger();
}



