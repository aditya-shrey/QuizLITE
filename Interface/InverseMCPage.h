//
// Created by Fardeen Bablu on 7/30/24.
//

#ifndef QUIZLITE_INVERSEMCPAGE_H
#define QUIZLITE_INVERSEMCPAGE_H


#include "EnterSetPage.h"
#include "../StudyingMethods/InverseMultipleChoice.h"
#include <QtWidgets>
#include <QtCore>
class InverseMCPage : public QWidget {
Q_OBJECT

public:
    explicit InverseMCPage(QWidget *parent = nullptr);

public slots:
    void startInverseMCQuiz(const QString &setName);
    void resetQuiz();


private slots:
    void setupUI();
    void showQuestion();
    void checkAnswer();
    void showNextQuestion();
    void finishQuiz();
    void setupBackToSetButton();

signals:
    void backToSetClicked();

private:
    QVBoxLayout *ui;
    QLabel *questionLabel;
    QButtonGroup *answerGroup;
    QVector<QRadioButton*> answerButtons;
    QPushButton *submitButton;
    QPushButton *nextButton;
    QPushButton *finishButton;
    QPushButton *backToSetButton;


    InverseMultipleChoice *imc;
    QString currentSetName;
    int currentScore;
    int totalQuestions;
    int setSize;


};

#endif // INVERSE_MC_PAGE_H