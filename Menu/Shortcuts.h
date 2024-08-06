#ifndef QUIZLITE_SHORTCUTS_H
#define QUIZLITE_SHORTCUTS_H

#include <QObject>
#include <QShortcut>
#include <QString>

class MainWindow;

class Shortcuts : public QObject {
Q_OBJECT

public:
    explicit Shortcuts(MainWindow *mainWindow);

    void setCurrentSetName(const QString &setName);
    QString currentSetName() const;

private:
    MainWindow *m_mainWindow;
    QString m_currentSetName;

    QShortcut *m_newSetShortcut;
    QShortcut *m_mcShortcut;
    QShortcut *m_inverseMCShortcut;
    QShortcut *m_flashcardShortcut;

    void setupShortcuts();
};

#endif // QUIZLITE_SHORTCUTS_H