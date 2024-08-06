//
// Created by Fardeen Bablu on 8/4/24.
//

#ifndef QUIZLITE_SHORTCUTS_H
#define QUIZLITE_SHORTCUTS_H

#include "../Interface/MainWindow.h"
#include "../Interface/EnterSetPage.h"


class Shortcuts : public QObject {
    Q_OBJECT

public:
    explicit Shortcuts(QObject *parent = nullptr);

    QMenu   *setMenu;
    QAction *searchAct;

    QMenu   *studyMenu;
    QAction *newSetAct;         //Cmd+N
    QAction *mcAct;             //M
    QAction *inverseMCAct;      //I
    QAction *flashAct;          //F


public slots:
    void    createActions();
    void    createMenus();
//    QAction *searchAct;



private slots:
    void newSetCmd();
    void mcCmd();
    void inverseMCCmd();
    void flashCmd();







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
