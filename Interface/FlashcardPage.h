//
// Created by Fardeen Bablu on 7/30/24.
//

#ifndef FLASHCARD_PAGE_H
#define FLASHCARD_PAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QApplication>
#include "../StudyingMethods/Flashcards.h"

class FlashcardPage : public QWidget {
Q_OBJECT

public:
    explicit FlashcardPage(QWidget *parent = nullptr);
    void startFlashcardQuiz(const QString &setName);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void setupUI();
    void resetFlashcardSession();
    void finishFlashcardSession();
    void showNextFlashcard();
    void showPreviousFlashcard();
    void toggleFlashcard();
    void setupBackToSetButton();

    QVBoxLayout *ui;
    QPushButton *flashcardButton;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QPushButton *finishButton;
    QPushButton *backToSetButton;

    QString currentSetName;
    Flashcards *fc;
    int currentIndex;
    int totalFlashcards;
    bool isAnswerShown;

signals:
    void backToSetClicked();
};

#endif // FLASHCARD_PAGE_H
