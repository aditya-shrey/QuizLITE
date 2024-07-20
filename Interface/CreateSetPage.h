//
// Created by Fardeen Bablu on 7/13/24.
//

#ifndef QUIZLITE_CREATESETPAGE_H
#define QUIZLITE_CREATESETPAGE_H

#include "MainWindow.h"


class CreateSetPage : public QWidget {
Q_OBJECT

QPushButton *backToLibraryButton;

public:
    CreateSetPage(QWidget *parent = nullptr);


signals:
    void setNameConfirmed(const QString &setName);
    void backToLibraryClicked();

public slots:
    void setupBackToLibrary();


private:
    QVBoxLayout *ui;
    QLabel *pageLabel;
    QLabel *setNameLabel;
    QLineEdit *setNameInput;
    QPushButton *confirmButton;
};


#endif //QUIZLITE_CREATESETPAGE_H
