//
// Created by Fardeen Bablu on 7/2/24.
//

#ifndef QUIZLITE_MAINWINDOW_H
#define QUIZLITE_MAINWINDOW_H

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


protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU


    // Slots and signals are Qt's version of function callbacks
    // https://doc.qt.io/qt-5/signalsandslots.html
private slots:
    void newFile();
    void open();
    void save();
    void undo();
    void redo();
    void cut();
//    void copy();
//    void paste();
//    void bold();
//    void italic();
//    void leftAlign();
//    void rightAlign();
//    void justify();
//    void center();
//    void setLineSpacing();
//    void setParagraphSpacing();
//    void about();
//    void aboutQt();


private:
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *editMenu;
//    QMenu *formatMenu;
//    QMenu *helpMenu;
//
//    QActionGroup *alignmentGroup;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
//    QAction *copyAct;
//    QAction *pasteAct;
//    QAction *boldAct;
//    QAction *italicAct;
//    QAction *leftAlignAct;
//    QAction *rightAlignAct;
//    QAction *justifyAct;
//    QAction *centerAct;
//    QAction *setLineSpacingAct;
//    QAction *setParagraphSpacingAct;
//    QAction *aboutAct;
//    QAction *aboutQtAct;
    QLabel *infoLabel;
};


#endif //QUIZLITE_MAINWINDOW_H
