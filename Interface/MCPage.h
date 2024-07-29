//
// Created by Fardeen Bablu on 7/26/24.
//

#ifndef QUIZLITE_MCPAGE_H
#define QUIZLITE_MCPAGE_H

#include "EnterSetPage.h"
#include "../StudyingMethods/MultipleChoice.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>

class MCPage : public QWidget {
Q_OBJECT
public:
    MCPage(QWidget *parent = nullptr);


signals:
    void openMCPage();
    void backToSetClicked();

public slots:
    void startMCQuiz(const QString &setName);

private:
    QString currentSetName;
    MultipleChoice *mc;
    QVBoxLayout *ui;
    QLabel *questionLabel;
    QButtonGroup *answerGroup;
    QRadioButton *answerButtons[4];
    QPushButton *submitButton;
    QPushButton *nextButton;
    QPushButton *finishButton;

    int currentScore;
    int totalQuestions;

    void setupUI();
    void showQuestion();
    void checkAnswer();
    void showNextQuestion();
    void finishQuiz();
};

#endif //QUIZLITE_MCPAGE_H