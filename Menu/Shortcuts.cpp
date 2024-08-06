#include "Shortcuts.h"
#include "../Interface/MainWindow.h"
#include <QKeySequence>

Shortcuts::Shortcuts(MainWindow *mainWindow)
        : QObject(mainWindow), m_mainWindow(mainWindow)
{
    setupShortcuts();
}

void Shortcuts::setupShortcuts()
{
    m_newSetShortcut = new QShortcut(QKeySequence::New, m_mainWindow);
    connect(m_newSetShortcut, &QShortcut::activated, m_mainWindow, &MainWindow::showCreateSetPage);

    m_mcShortcut = new QShortcut(QKeySequence(Qt::Key_M), m_mainWindow);
    connect(m_mcShortcut, &QShortcut::activated, this, [this]() {
        if (!m_currentSetName.isEmpty()) {
            m_mainWindow->showMCPage(m_currentSetName);
        }
    });

    m_inverseMCShortcut = new QShortcut(QKeySequence(Qt::Key_I), m_mainWindow);
    connect(m_inverseMCShortcut, &QShortcut::activated, this, [this]() {
        if (!m_currentSetName.isEmpty()) {
            m_mainWindow->showInverseMCPage(m_currentSetName);
        }
    });

    m_flashcardShortcut = new QShortcut(QKeySequence(Qt::Key_F), m_mainWindow);
    connect(m_flashcardShortcut, &QShortcut::activated, this, [this]() {
        if (!m_currentSetName.isEmpty()) {
            m_mainWindow->showFlashcardPage(m_currentSetName);
        }
    });
}

void Shortcuts::setCurrentSetName(const QString &setName)
{
    m_currentSetName = setName;
}

QString Shortcuts::currentSetName() const
{
    return m_currentSetName;
}