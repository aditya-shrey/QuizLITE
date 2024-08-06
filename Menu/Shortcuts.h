#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include "../Interface/MainWindow.h"
#include "../Interface/EnterSetPage.h"
#include <QObject>
#include <QShortcut>

class MainWindow;
class EnterSetPage;

class Shortcuts : public QObject
{
Q_OBJECT

public:
    explicit Shortcuts(MainWindow *mainWindow, EnterSetPage *enterSetPage);
    void setCurrentSetName(const QString &setName);
    QString currentSetName() const;

private:
    void setupShortcuts();

    MainWindow *mainWindow;
    EnterSetPage *enterSetPage;
    QShortcut *newSetShortcut;
    QShortcut *mcShortcut;
    QShortcut *inverseMCShortcut;
    QShortcut *flashcardShortcut;
    QString m_currentSetName;
};

#endif // SHORTCUTS_H