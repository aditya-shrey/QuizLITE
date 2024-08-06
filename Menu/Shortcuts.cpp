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
    newSetAct->setShortcut(QKeySequence::New);

    searchAct = new QAction(tr("&Search"), this);
    searchAct->setShortcut(QKeySequence::Find);

    mcAct = new QAction(tr("&Multiple Choice"), this);
    mcAct->setShortcut(QKeySequence(Qt::Key_M));

    inverseMCAct = new QAction(tr("&Inverse Multiple Choice"), this);
    inverseMCAct->setShortcut(QKeySequence(Qt::Key_I));

    flashAct = new QAction(tr("&Flashcards"), this);
    flashAct->setShortcut(QKeySequence(Qt::Key_F));
}



void Shortcuts::createMenus() {
    setMenu = new QMenu(tr("&Sets"));
    setMenu->addAction(newSetAct);
    setMenu->addAction(searchAct);


    studyMenu = new QMenu(tr("&Study"));
    studyMenu->addAction(mcAct);
    studyMenu->addAction(inverseMCAct);
    studyMenu->addAction(flashAct);
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




