//
// Created by Fardeen Bablu on 8/4/24.
//

#ifndef QUIZLITE_NEWSET_H
#define QUIZLITE_NEWSET_H

#include "../Interface/MainWindow.h"
class NewSet : public QObject {
    Q_OBJECT

public:
    explicit NewSet(QObject *parent = nullptr);

private slots:
    void newSetCmd();
    void mcCmd();
    void imcCmd();
    void flashCmd();
    void searchCmd();

private:
    void createActions();
    void createMenus();

    QMenu *setMenu;           // Sets
    QMenu *studyMethodsMenu;  // Study

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


#endif //QUIZLITE_NEWSET_H
