//
// Created by Fardeen Bablu on 7/2/24.
//

#include <QtWidgets>
#include "MainWindow.h"

MainWindow::MainWindow() {
    //Creating new Widgets
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget();
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("Choose a menu option, or right click for a context menu"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);



    createActions();
    createMenus();

    QString msg = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(msg);

    setWindowTitle(tr("QuizLITE"));
    setMinimumSize(600, 500);
    resize(480, 320);
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

void MainWindow::about() {
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"), tr("This <b>Menu</b> shows how to make menu-bars and context menus"));
}

void MainWindow::createActions() {
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


}


void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);


}