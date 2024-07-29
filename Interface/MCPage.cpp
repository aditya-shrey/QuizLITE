//
// Created by Fardeen Bablu on 7/26/24.
//

#include "MCPage.h"
#include <QMessageBox>

MCPage::MCPage(QWidget *parent) : QWidget(parent), mc(nullptr), currentScore(0), totalQuestions(0) {
    setupUI();
}

void MCPage::setupUI() {
    ui = new QVBoxLayout(this);
    questionLabel = new QLabel(this);
    questionLabel->setStyleSheet("font-size: 20px; color: #FFFFFF;");
    questionLabel->setAlignment(Qt::AlignCenter);
    ui->addWidget(questionLabel);

    // Create MC answer ticks
    answerGroup = new QButtonGroup(this);
    for (int i = 0; i < 4; ++i) {
        answerButtons[i] = new QRadioButton(this);
        answerButtons[i]->setStyleSheet(
                "QRadioButton {"
                "font-size: 18px;"
                "color: #FFFFFF;"
                "background-color: #403e3e;"
                "border-radius: 10px;"
                "padding: 5px;"
                "margin: 2px 0;"
                "}"
                "QRadioButton::indicator {"
                "width: 20px;"
                "height: 20px;"
                "}"
                "QRadioButton::indicator:checked {"
                "background-color: #32CD32;"
                "}"
                "QRadioButton::indicator:unchecked {"
                "background-color: #FFFFFF;"
                "}"
        );
        ui->addWidget(answerButtons[i]);
        answerGroup->addButton(answerButtons[i], i);
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
        QMessageBox::warning(this, "No Selection", "Select an answer before submitting");
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
            answerButtons[i]->setStyleSheet(
                    "QRadioButton {"
                    "font-size: 18px;"
                    "color: #FFFFFF;"
                    "background-color: green;"
                    "border-radius: 10px;"
                    "padding: 5px;"
                    "margin: 2px 0;"
                    "}"
                    "QRadioButton::indicator {"
                    "width: 20px;"
                    "height: 20px;"
                    "}"
                    "QRadioButton::indicator:checked {"
                    "background-color: #32CD32;"
                    "}"
                    "QRadioButton::indicator:unchecked {"
                    "background-color: #FFFFFF;"
                    "}"
            );
        } else if (i == selectedAnswer) {
            answerButtons[i]->setStyleSheet(
                    "QRadioButton {"
                    "font-size: 18px;"
                    "color: #FFFFFF;"
                    "background-color: red;"
                    "border-radius: 10px;"
                    "padding: 5px;"
                    "margin: 2px 0;"
                    "}"
                    "QRadioButton::indicator {"
                    "width: 20px;"
                    "height: 20px;"
                    "}"
                    "QRadioButton::indicator:checked {"
                    "background-color: #32CD32;"
                    "}"
                    "QRadioButton::indicator:unchecked {"
                    "background-color: #FFFFFF;"
                    "}"
            );
        }
    }
}

void MCPage::showNextQuestion() {
    for (int i = 0; i < 4; ++i) {
        answerButtons[i]->setStyleSheet(
                "QRadioButton {"
                "font-size: 18px;"
                "color: #FFFFFF;"
                "background-color: #403e3e;"
                "border-radius: 10px;"
                "padding: 5px;"
                "margin: 2px 0;"
                "}"
                "QRadioButton::indicator {"
                "width: 20px;"
                "height: 20px;"
                "}"
                "QRadioButton::indicator:checked {"
                "background-color: #32CD32;"
                "}"
                "QRadioButton::indicator:unchecked {"
                "background-color: #FFFFFF;"
                "}"
        );
    }
    showQuestion();
}

void MCPage::finishQuiz() {
    float accuracy;
    if (totalQuestions > 0) {
        accuracy = static_cast<float>(currentScore) / totalQuestions * 100;
    } else {
        accuracy = 0;
    }

    QMessageBox::information(this, "Quiz Finished", "Your score: " + QString::number(currentScore) + "/" + QString::number(totalQuestions) + "\nAccuracy: " + QString::number(accuracy) + "%");

    questionLabel->clear();
    for (int i = 0; i < 4; ++i) {
        answerButtons[i]->setStyleSheet(
                "QRadioButton {"
                "font-size: 18px;"
                "color: #FFFFFF;"
                "background-color: #403e3e;"
                "border-radius: 10px;"
                "padding: 5px;"
                "margin: 2px 0;"
                "}"
                "QRadioButton::indicator {"
                "width: 20px;"
                "height: 20px;"
                "}"
                "QRadioButton::indicator:checked {"
                "background-color: #32CD32;"
                "}"
                "QRadioButton::indicator:unchecked {"
                "background-color: #FFFFFF;"
                "}"
        );
        answerButtons[i]->setText("");
    }

    submitButton->hide();
    nextButton->hide();
    finishButton->hide();
}