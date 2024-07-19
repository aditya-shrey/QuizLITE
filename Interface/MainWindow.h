//
// Created by Fardeen Bablu on 7/13/24.
//
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
#include "CreateSetPage.h"
#include "LibraryPage.h"
#include "AddQuestionsPage.h"
#include "EnterSetPage.h"

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


class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void showCreatePageSet();
    void showAddQuestionsPage(const QString &setName);
    void addToSet(const QString &question, const QString &answer);
    void finishSet();
    void openSet(const QString &setName);
    void showLibraryPage();

private:
    QStackedWidget *pageStack;
    LibraryPage *libraryPage;
    CreateSetPage *createSetPage;
    AddQuestionsPage *addQuestionsPage;
    EnterSetPage *enterSetPage;
    QVector<QPair<QString, QString>> currentSetQA;
    QString currentSetName;
    QMap<QString, QListWidget*> setWidgets;
    QPushButton backToLibrary;

};
#endif //QUIZLITE_MAINWINDOW_H


//EXTRA GOODIES DELETE LATER
//
//class MainWindow : public QMainWindow
//{
//    Q_OBJECT
//
//public:
//    MainWindow(QWidget *parent = nullptr);
//
//private slots:
//    void newFile();
//    void open();
//    void save();
//    void undo();
//    void redo();
//    void switchPage();
//
//private:
//    void createMenuActions();
//    void addMenuActions();
//
//    QMenu *fileMenu;
//    QMenu *editMenu;
//
//    QAction *newAct;
//    QAction *openAct;
//    QAction *saveAct;
//    QAction *exitAct;
//    QAction *undoAct;
//    QAction *redoAct;
//
//    QStackedWidget *m_stack;
//    QPushButton *switchButton;
//};
//
//#endif // QUIZLITE_MAINWINDOW_H
