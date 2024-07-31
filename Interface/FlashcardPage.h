//
// Created by Fardeen Bablu on 7/30/24.
//

#ifndef FLASHCARD_PAGE_H
#define FLASHCARD_PAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../StudyingMethods/Flashcards.h"

class FlashcardPage : public QWidget {
Q_OBJECT

public:
    explicit FlashcardPage(QWidget *parent = nullptr);

public slots:
    void startFlashcardQuiz(const QString &setName);

private slots:
    void setupUI();
    void showNextFlashcard();
    void showAnswer();
    void finishFlashcardSession();
    void resetFlashcardSession();
    void setupBackToSetButton();

signals:
    void backToSetClicked();

private:
    QVBoxLayout *ui;
    QLabel *flashcardLabel;
    QPushButton *showAnswerButton;
    QPushButton *nextButton;
    QPushButton *finishButton;
    QPushButton *backToSetButton;

    Flashcards *fc;
    QString currentSetName;
    int currentIndex;
    int totalFlashcards;
};

#endif // FLASHCARD_PAGE_H

