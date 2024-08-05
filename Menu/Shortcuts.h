//
// Created by Fardeen Bablu on 8/4/24.
//

#ifndef QUIZLITE_SHORTCUTS_H
#define QUIZLITE_SHORTCUTS_H

#include "../Interface/MainWindow.h"


class Shortcuts : public QWidget {
    Q_OBJECT

public:
    explicit Shortcuts(QWidget *parent = nullptr);

    void createActions();
    void createMenus();
    void addMenutoMainWindow(QMainWindow *mainWindow);

private slots:
    void newSetCmd();
    void mcCmd();
    void imcCmd();
    void flashCmd();
    void searchCmd();

private:
    QMenu *setMenu;
    QMenu *studyMethodsMenu;
    QAction *newSetAct;
    QAction *mcAct;
    QAction *imcAct;
    QAction *flashAct;
    QAction *searchAct;




    /**
     * shortcuts to add
     *
     *
     * new set
     * "m" for mc
     * "i" for imc
     * "f" for flashcards
     * tabbing support?
     * cmd+f for search
     *
     *
     *
     * cool small things
     *
     * different ways to view set in LibraryPage: in a row like Nintendo DSI
     * upload header image to represent each set
     *
     *
     */




};


#endif //QUIZLITE_SHORTCUTS_H
