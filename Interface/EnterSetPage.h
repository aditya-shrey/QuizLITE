#ifndef QUIZLITE_ENTERSETPAGE_H
#define QUIZLITE_ENTERSETPAGE_H

#include <QtWidgets>
#include <QtCore>
#include "MCPage.h"
#include <map>
#include <iostream>
#include "../User/UserSession.h"
#include "../Menu/Shortcuts.h"


class Shortcuts;

/**
 * @class EnterSetPage
 * @brief A widget for managing and interacting with a specific quiz set.
 */
class EnterSetPage : public QWidget {
Q_OBJECT
    QPushButton *backToLibraryButton;

public:

    /**
     * @brief Constructor for EnterSetPage.
     *
     * @param parent The parent widget.
     */
    EnterSetPage(QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal emitted when a set is opened.
     *
     * @param setName The name of the set to be opened.
     */
    void openSetClicked(const QString &setName);

    /**
     * @brief Signal emitted when the back to library button is clicked.
     */
    void backToLibraryClicked();

    /**
     * @brief Signal emitted when the multiple choice button is clicked.
     *
     * @param setName The name of the set to start quiz.
     */
    void openMCPageClicked(const QString &setName);

    /**
     * @brief Signal emitted when the inverse multiple choice button is clicked.
     *
     * @param setName The name of the set to start quiz.
     */
    void openInverseMCPageClicked(const QString &setName);

    /**
     * @brief Signal emitted when the flashcards button is clicked.
     *
     * @param setname The name of the set to start quiz.
     */
    void openFlashcardsPageClicked(const QString &setname);

    /**
     * @brief Signal emitted when a set is deleted.
     *
     * @param setName The name of the set to be deleted.
     */
    void deleteSetClicked(const QString &setName);

    /**
     * @brief Signal emitted when a key-value pair is deleted from a set.
     *
     * @param setName The name of the set.
     * @param key The key of the key-value pair to be deleted.
     */
    void deleteKeyValuePairClicked(const QString &setName, const QString &key);

    /**
     * @brief Signal emitted when a key-value pair is adjusted in a set.
     *
     * @param setName The name of the set.
     * @param key The key of the key-value pair to be adjusted.
     * @param newValue The new value of the key-value pair.
     */
    void adjustKeyValuePairClicked(const QString &setName, const QString &key, const QString &newValue);

    /**
     * @brief Signal emitted to confirm deletion of a set.
     *
     * @param setName The name of the set to be deleted.
     */
    void confirmDeleteSet(const QString &setName);



public slots:
    /**
     * @brief Adds a new set to the page.
     *
     * @param setName The name of the set to be added.
     */
    void addSet(const QString &setName);

    /**
     * @brief Sets the name of the current set.
     *
     * @param setName The name of the current set.
     */
    void setSetName(const QString &setName);

    /**
     * @brief Sets the QA list for the specified set.
     *
     * @param setName The name of the set.
     */
    void setQAList(const QString &setName);

    /**
     * @brief Clears all entries from the QA list.
     */
    void clearAllEntries();

    /**
     * @brief Shows the add question page.
     */
    void showAddQuestionPage();

    /**
     * @brief Deletes a specified set.
     *
     * @param setName The name of the set to be deleted.
     */
    void deleteSet(const QString &setName);

    /**
     * @brief Deletes a key-value pair from a specified set.
     *
     * @param setName The name of the set.
     * @param key The key of the key-value pair to be deleted.
     */
    void deleteKeyValuePair(const QString &setName, const QString &key);

    /**
     * @brief Adjusts a key-value pair in a specified set.
     *
     * @param setName The name of the set.
     * @param key The key of the key-value pair to be adjusted.
     * @param newValue The new value of the key-value pair.
     */
    void adjustKeyValuePair(const QString &setName, const QString &key, const QString &newValue);

    /**
     * @brief Gets the current set name.
     * @return returns a QString of the current setName;
     */
    QString getCurrentSetName() const { return currentSetName; }

    /**
     * @brief Parameter-less public slot so that shortcut can open MC page
     */
    void openMCPage();

    /**
     * @brief Parameter-less public slot so that shortcut can open MC page
     */
    void openInversePage();

    /**
     * @brief Parameter-less public slot so that shortcut can open MC page
     */
    void openFlashcardsPage();


    void setShortcuts(Shortcuts *shortcuts);

protected:
    /**
     * @brief Event filter for handling custom events.
     *
     * @param watched The watched object.
     * @param event The event to be processed.
     * @return True if the event was handled; otherwise false.
     */
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QVBoxLayout *ui;
    QLabel *setNameLabel;
    QLabel *pageLabel;
    QListWidget *qaListWidget;
    QString currentSetName;
    std::map<QString, QWidget*> setWidgets;
    QScrollArea *scrollArea;
    QStackedWidget *studyMethodsPageStack;
    QPushButton *mcButton;
    QPushButton *inverseMCButton;
    QPushButton *flashcardsButton;
    QLabel *studyMethodsLabel;
    Shortcuts *m_shortcuts;

    void setupStudyMethodButtons();
    void setupBackButton();
    void updateSetSize();
    void checkSetSizeAndEmitSignal(const std::function<void()>& emitSignal);

    int setSize;
};

#endif // QUIZLITE_ENTERSETPAGE_H
