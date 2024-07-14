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

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QApplication;
class QWidget;
class QVBoxLayout;
class QStackedWidget;
class QPushButton;
QT_END_NAMESPACE


class LibraryPage : public QWidget {
    Q_OBJECT
public:
    LibraryPage(QWidget *parent = nullptr);

};


class CreateSetPage : public QWidget {
    Q_OBJECT
public:
    CreateSetPage(QWidget *parent = nullptr);
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void newSet();

};


#endif //QUIZLITE_MAINWINDOW_H



//
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
