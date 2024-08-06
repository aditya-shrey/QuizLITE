#include "Shortcuts.h"
#include <QKeySequence>

Shortcuts::Shortcuts(MainWindow *mainWindow, EnterSetPage *enterSetPage)
        : QObject(mainWindow), mainWindow(mainWindow), enterSetPage(enterSetPage) {
    setupShortcuts();
}

void Shortcuts::setupShortcuts()
{
    newSetShortcut = new QShortcut(QKeySequence::New, mainWindow);
    connect(newSetShortcut, &QShortcut::activated, mainWindow, &MainWindow::showCreateSetPage);

    mcShortcut = new QShortcut(Qt::Key_M, enterSetPage);
    connect(mcShortcut, &QShortcut::activated, enterSetPage, &EnterSetPage::openMCPage);

    inverseMCShortcut = new QShortcut(Qt::Key_I, enterSetPage);
    connect(inverseMCShortcut, &QShortcut::activated, enterSetPage, &EnterSetPage::openInversePage);

    flashcardShortcut = new QShortcut(Qt::Key_F, enterSetPage);
    connect(flashcardShortcut, &QShortcut::activated, enterSetPage, &EnterSetPage::openFlashcardsPage);
}

void Shortcuts::setCurrentSetName(const QString &setName)
{
    m_currentSetName = setName;
}

QString Shortcuts::currentSetName() const
{
    return m_currentSetName;
}