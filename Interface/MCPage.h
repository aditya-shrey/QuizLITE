#ifndef QUIZLITE_MCPAGE_H
#define QUIZLITE_MCPAGE_H

#include "EnterSetPage.h"
#include "../StudyingMethods/MultipleChoice.h"
#include <QtWidgets>
#include <QtCore>

class MCPage : public QWidget {
Q_OBJECT
public:
    MCPage(QWidget *parent = nullptr);
    void startMCQuiz(const QString &setName);
    void resetQuiz();

signals:
    void openMCPage();
    void backToSetClicked();

private:
    QString currentSetName;
    MultipleChoice *mc;
    QVBoxLayout *ui;
    QLabel *questionLabel;
    QButtonGroup *answerGroup;
    QVector<QRadioButton*> answerButtons;
    QPushButton *submitButton;
    QPushButton *nextButton;
    QPushButton *finishButton;
    QPushButton *backToSetButton;

    int currentScore;
    int totalQuestions;
    int setSize;

    void setupUI();
    void showQuestion();
    void checkAnswer();
    void showNextQuestion();
    void finishQuiz();
    void setupBackToSetButton();
};

#endif //QUIZLITE_MCPAGE_H
