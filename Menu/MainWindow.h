//
// Created by Fardeen Bablu on 7/2/24.
//

#ifndef QUIZLITE_MAINWINDOW_H
#define QUIZLITE_MAINWINDOW_H

#include "../User/UserSessionInfo.h"
#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QMenu>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

    // Slots and signals are Qt's version of function callbacks
    // https://doc.qt.io/qt-5/signalsandslots.html
private slots:
    void newFile();
    void open();
    void save();
    void undo();
    void redo();

private:
    void createMenuActions();
    void addMenuActions();
    void

    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QLabel *infoLabel;






};

#endif //QUIZLITE_MAINWINDOW_H