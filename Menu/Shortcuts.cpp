//
// Created by Fardeen Bablu on 8/4/24.
//

#include "Shortcuts.h"
#include <QMenu>

Shortcuts::Shortcuts(QWidget *parent) :  QWidget(parent) {
    createActions();
    createMenus();
}

void Shortcuts::createActions() {
    newSetAct = new QAction(tr("&New Set"), this);
    connect(newSetAct, &QAction::triggered, this, &Shortcuts::newSetCmd);

    mcAct = new QAction(tr("&Multiple Choice"), this);
    connect(mcAct,  &QAction::triggered, this, &Shortcuts::mcCmd);

    imcAct = new QAction(tr("&Inverse Multiple Choice"), this);
    connect(imcAct, &QAction::triggered, this, &Shortcuts::imcCmd);

    flashAct = new QAction(tr("&Flashcards"), this);
    connect(flashAct, &QAction::triggered, this, &Shortcuts::flashCmd);

    searchAct = new QAction(tr("&Search"), this);
    connect(searchAct, &QAction::triggered, this, &Shortcuts::searchCmd);

}

void Shortcuts::createMenus() {
    setMenu = new QMenu(tr("&Sets"));
    setMenu->addAction(newSetAct);

    studyMethodsMenu = new QMenu(tr("&Study"));
    studyMethodsMenu->addAction(mcAct);
    studyMethodsMenu->addAction(imcAct);
    studyMethodsMenu->addAction(flashAct);
    studyMethodsMenu->addAction(searchAct);
}


void Shortcuts::newSetCmd() {
}




