//
// Created by Fardeen Bablu on 7/26/24.
//

#include "MCPage.h"
#include "../User/UserSession.h"
#include <QMessageBox>

MCPage::MCPage(QWidget *parent) : QWidget(parent), mc(nullptr), currentScore(0), totalQuestions(0) {
    setupUI();
}

void MCPage::setupUI() {
    ui = new QVBoxLayout(this);
    questionLabel = new QLabel(this);
    ui->addWidget(questionLabel);

    //Create MC answer ticks
    answerGroup = new QButtonGroup(this);
    for (int i = 0; i < 4; ++i) {
        answerButtons[i] = new QRadioButton(this);
        ui->addWidget(answerButtons[i]);
        answerGroup->addButton(answerButtons[i],i);
    }

    submitButton = new QPushButton("Submit", this);
    nextButton = new QPushButton("Next", this);
    finishButton = new QPushButton("Finish", this);

    ui->addWidget(submitButton);
    ui->addWidget(nextButton);
    ui->addWidget(finishButton);

    connect(submitButton, &QPushButton::clicked, this, &MCPage::checkAnswer);
    connect(nextButton, &QPushButton::clicked, this, &MCPage::showNextQuestion);
    connect(finishButton, &QPushButton::clicked, this, &MCPage::finishQuiz);

    nextButton->hide();
    finishButton->hide();
    setLayout(ui);
}

void MCPage::startMCQuiz(const QString &setName) {
//    UserSession *session = UserSession::getUserSession();
    currentSetName = setName;

    mc = new MultipleChoice(setName.toStdString(), 5, 5);
    currentScore = totalQuestions = 0;
    showQuestion();
}

void MCPage::showQuestion() {
    std::string question = mc->getQuestion();
    if (question.empty()) {
        finishQuiz();
        return;
    }



    questionLabel->setText(QString::fromStdString(question));
    auto options = mc->generateOptions();
    answerButtons[0]->setText(QString::fromStdString(std::get<0>(options)));
    answerButtons[1]->setText(QString::fromStdString(std::get<1>(options)));
    answerButtons[2]->setText(QString::fromStdString(std::get<2>(options)));
    answerButtons[3]->setText(QString::fromStdString(std::get<3>(options)));



    for (int i = 0; i < 4; ++i) {
        answerButtons[i]->setChecked(false);
    }

    submitButton->show();
    nextButton->hide();
    finishButton->hide();
    ++totalQuestions;
}

void MCPage::checkAnswer() {
    int selectedAnswer = answerGroup->checkedId();
    if (selectedAnswer == -1) {
        QMessageBox::warning(this, "No Selection", "Selection an answer before before submitting");
        return;
    }
    std::string correctAnswer = mc->getAnswer();
    bool isCorrect = (answerButtons[selectedAnswer])->text() == QString::fromStdString(correctAnswer);

    if (isCorrect) {
        ++currentScore;
    }

    mc->updateScoresInTable(isCorrect);
    submitButton->hide();
    if (mc->goToNextQuestion()) {
        nextButton->show();
    } else {
        finishButton->show();
    }

    for (int i = 0; i < 4; ++i) {
        if (answerButtons[i]->text() == QString::fromStdString(correctAnswer)) {
            answerButtons[i]->setStyleSheet("background-color: green;");
        } else if (i == selectedAnswer) {
            answerButtons[i]->setStyleSheet("background-color: red;");
        }
    }
}

void MCPage::showNextQuestion() {
    for (int i = 0; i < 4; ++i) {
        answerButtons[i]->setStyleSheet("");
    } showQuestion();
}

void MCPage::finishQuiz() {
    float accuracy;
    if (totalQuestions > 0) {
        accuracy = static_cast<float>(currentScore) / totalQuestions * 100;
    } else { accuracy = 0; }

    QString resultMsg = QString("Quiz Complete\n Score: %1/%2\nAccuracy: %3%")
            .arg(currentScore)
            .arg(totalQuestions)
            .arg(accuracy, 0, 'f', 2);

    QMessageBox::information(this, "Quiz Results", resultMsg);
    QPushButton *backToSetButton = new QPushButton("< Back to Set", this);
    connect(backToSetButton, &QPushButton::clicked, this, &MCPage::backToSetClicked);

    delete mc;
    mc = nullptr;
}
