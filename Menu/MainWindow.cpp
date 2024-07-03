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
    setMinimumSize(160, 160);
    resize(480, 320);
}



// IDK why there is ifndef here. This is just if you right-click on blank page it opens a small menu
#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.addAction(cutAct);
//    menu.addAction(copyAct);
//    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU


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

void MainWindow::cut() {
    infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}

//void MainWindow::copy() {
//    infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
//}
//
//void MainWindow::paste(){
//    infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
//}
//
//void MainWindow::bold() {
//    infoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
//}
//
//void MainWindow::italic() {
//    infoLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));
//}
//
//void MainWindow::leftAlign() {
//    infoLabel->setText(tr("Invoked <b>Edit|Format|Left Align</b>"));
//}
//
//void MainWindow::rightAlign() {
//    infoLabel->setText(tr("Invoked <b>Edit|Format|Right Align</b>"));
//}
//
//void MainWindow::justify() {
//    infoLabel->setText(tr("Invoked <b>Edit|Format|Justify</b>"));
//}
//
//void MainWindow::center() {
//    infoLabel->setText(tr("Invoked <b>Edit|Format|Center</b>"));
//}
//
//void MainWindow::setLineSpacing() {}() {
//    infoLabel->setText(tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));
//}
//
//void MainWindow::setParagraphSpacing() {}() {
//    infoLabel->setText(tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));
//}
//
//void MainWindow::about() {
//    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
//    QMessageBox::about(this, tr("About Menu"), tr("This <b>Menu</b> shows how to make menu-bars and context menus");
//}

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

    undoAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::EditUndo), tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last action"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);


    redoAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::EditRedo), tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last action"));
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    cutAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::EditCut), tr("&Cut)"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut last action"));
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

    /**
     * Remaining actions
     *
     * copy
     * paste
     * bold
     * italic
     * setlinespacing
     * setparagraphspacing
     * about tab
     * left, right, justify, center alignment
     */
}


void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
//    editMenu->addAction(copyAct);
//    editMenu->addAction(pasteAct);
//    editMenu->addSeparator();

//    helpMenu = menuBar()->addMenu(tr("&Help"));
//    helpMenu->addAction(aboutAct);


//    formatMenu = menuBar()->addMenu(tr("&Format"));
    /*
    * Add formatMenu
    * bold, italic, alignment options...
    */
}