//
// Created by Fardeen Bablu on 7/17/24.
//

#ifndef QUIZLITE_ADDQUESTIONSPAGE_H
#define QUIZLITE_ADDQUESTIONSPAGE_H

#include "MainWindow.h"

class AddQuestionsPage : public QWidget {
    Q_OBJECT
    QPushButton *backToLibraryButton;
public:
    AddQuestionsPage(QWidget *parent = nullptr);
    QListWidget *getQAListWidget() const { return qaListWidget; }

signals:
    void addToSetClicked(const QString &question, const QString &answer);
    void finishedClicked();
    void backToLibraryClicked();

public slots:
    void setupBackToLibrary();

private slots:
    void addToSet();

private:
    QVBoxLayout *ui;
    QLabel *pageLabel;
    QLineEdit *questionInput;
    QLineEdit *answerInput;
    QPushButton *addToSetButton;
    QPushButton *finishButton;
    QListWidget *qaListWidget;
};

#endif //QUIZLITE_ADDQUESTIONSPAGE_H