//
// Created by Fardeen Bablu on 7/2/24.
//

#include <QtWidgets>
#include "MainWindow.h"
#include "../User/UserSessionInfo.h"

MainWindow::MainWindow() {
    //make user session
    UserSessionInfo *userSession = UserSessionInfo::getUserSessionInfo();

    //Creating new Widgets
    QWidget *widget = new QWidget;

    QPushButton *createSet_butt = new QPushButton("Create set");
    QPushButton *search_butt = new QPushButton("Search for anything");

    // button layout
    QVBoxLayout *button_layout = new QVBoxLayout();
    button_layout->addWidget(createSet_butt);
    button_layout->addWidget(search_butt);
    button_layout->setContentsMargins(0, 0, 0, 0);
    button_layout->setSpacing(0);

    // main layout
    QVBoxLayout *main_layout = new QVBoxLayout(widget);
    main_layout->addLayout(button_layout, Qt::AlignTop);
    main_layout->addStretch(); // Add stretch to push buttons to the top

    setCentralWidget(widget);

    QWidget *topFiller = new QWidget();
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("Choose a menu option, or right click for a context menu"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *actionPingLayout = new QVBoxLayout;
    actionPingLayout->setContentsMargins(5, 5, 5, 5);
    actionPingLayout->addWidget(topFiller);
    actionPingLayout->addWidget(infoLabel);
    actionPingLayout->addWidget(bottomFiller);
    widget->setLayout(actionPingLayout);

    createActions();
    createMenus();

    QString msg = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(msg);

    setWindowTitle(tr("QuizLITE"));
    setMinimumSize(300, 300);
    resize(480, 320);
}

void MainWindow::createSet() {

}



void MainWindow::startSearch() {

}





void MainWindow::newFile() {
    infoLabel->setText(tr("Invoked <b>File|New</b>"));
}

void MainWindow::open() {
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void MainWindow::save() {
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void MainWindow::undo() {
    infoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
}

void MainWindow::redo() {
    infoLabel->setText(tr("Invoked <b>Edt|Redo</b>"));
}


void MainWindow::createMenuActions() {
    newAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    exitAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit), tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Ext the application"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);

    undoAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::EditUndo), tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last action"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::EditRedo), tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last action"));
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

}


void MainWindow::addMenuActions() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
}



