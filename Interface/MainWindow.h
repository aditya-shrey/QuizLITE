#ifndef QUIZLITE_MAINWINDOW_H
#define QUIZLITE_MAINWINDOW_H

#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include "CreateSetPage.h"
#include "LibraryPage.h"
#include "AddQuestionsPage.h"
#include "EnterSetPage.h"
#include "MCPage.h"
#include "InverseMCPage.h"
#include "FlashcardPage.h"
#include <iostream>
#include "../User/UserSession.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QApplication;
class QWidget;
class QVBoxLayout;
class QStackedWidget;
class QPushButton;
class QLineEdit;
class QListWidget;
QT_END_NAMESPACE

class CreateSetPage;
class LibraryPage;
class AddQuestionsPage;
class EnterSetPage;
class MCPage;
class InverseMCPage;
class FlashcardsPage;

/**
 * @class MainWindow
 * @brief The main window for the QuizLITE application.
 */
class MainWindow : public QMainWindow {
Q_OBJECT
public:
    /**
     * @brief Constructor for MainWindow.
     *
     * @param parent The parent widget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    /**
     * @brief Shows the CreateSetPage.
     */
    void showCreatePageSet();

    /**
     * @brief Shows the AddQuestionsPage for the specified set.
     *
     * @param setName The name of the set to add questions to.
     */
    void showAddQuestionsPage(const QString &setName);

    /**
     * @brief Adds a question and answer to the current set.
     *
     * @param question The question text.
     * @param answer The answer text.
     */
    void addToSet(const QString &question, const QString &answer);

    /**
     * @brief Finalizes the current set and saves it.
     */
    void finishSet();

    /**
     * @brief Opens the specified set in the EnterSetPage.
     *
     * @param setName The name of the set to open.
     */
    void openSet(const QString &setName);

    /**
     * @brief Shows the LibraryPage.
     */
    void showLibraryPage();

    /**
     * @brief Handles the deletion of a set.
     * s
     * @param setName The name of the set to delete.
     */
    void handleDeleteSet(const QString &setName);

private:
    QStackedWidget *pageStack;
    LibraryPage *libraryPage;
    CreateSetPage *createSetPage;
    AddQuestionsPage *addQuestionsPage;
    EnterSetPage *enterSetPage;
    MCPage *mcPage;
    InverseMCPage *inverseMCPage;
    FlashcardPage *flashcardPage;
    QVector<QPair<QString, QString>> currentSetQA;
    QString currentSetName;
    QMap<QString, QListWidget*> setWidgets;
    QPushButton backToLibrary;
};

#endif // QUIZLITE_MAINWINDOW_H
