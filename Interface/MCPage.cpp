//
// Created by Fardeen Bablu on 7/26/24.
//

#include "MCPage.h"
#include <QMessageBox>

MCPage::MCPage(QWidget *parent) : QWidget(parent), mc(nullptr), currentScore(0), totalQuestions(0) {
    setupUI();
}

void MCPage::startMCQuiz(const QString &setName) {
    currentSetName = setName;
    resetQuiz();

    //if even number of question/answers, split between lowestAccuracies and randompair, if odd, split again but add +1 for random
    auto qaPair = UserSession::getUserSession()->getTableKeyValues(setName.toStdString());
    int totalPairs = qaPair.size();
    if (totalPairs % 2 == 0) {
        mc = new MultipleChoice(setName.toStdString(), totalPairs/2, totalPairs/2);
    } else {
        --totalPairs;
        mc = new MultipleChoice(setName.toStdString(), totalPairs/2, (totalPairs/2)+1);
    }
    showQuestion();
}
void MCPage::resetQuiz() {
    currentScore = 0;
    totalQuestions = 0;
    questionLabel->clear();
    for (uint i = 0; i < sizeof(answerButtons)/sizeof(answerButtons[0]); ++i) {
        answerButtons[i]->show();
        answerButtons[i]->setChecked(false);
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
    submitButton->show();
    nextButton->hide();
    finishButton->hide();
    backToSetButton->hide();
}

void MCPage::finishQuiz() {
    float accuracy = (totalQuestions > 0) ? (static_cast<float>(currentScore) / totalQuestions * 100) : 0;

    QMessageBox::information(this,
                             "Quiz Finished",
                             "Your score: " + QString::number(currentScore) + "/" + QString::number(totalQuestions) + "\nAccuracy: " + QString::number(accuracy) + "%");

    finishButton->hide();
    backToSetButton->show();
}

void MCPage::setupUI() {
    ui = new QVBoxLayout(this);
    questionLabel = new QLabel(this);
    questionLabel->setStyleSheet("font-size: 20px; color: #FFFFFF;");
    questionLabel->setAlignment(Qt::AlignCenter);
    ui->addWidget(questionLabel);

    // Create MC answer ticks
    answerGroup = new QButtonGroup(this);
    for (uint i = 0; i < sizeof(answerButtons)/sizeof(answerButtons[0]); ++i) {
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
    submitButton->setStyleSheet(
            "QPushButton {"
            "background-color: #2bb52b;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #2bb52b;"
            "}"
            "QPushButton:hover {"
            "background-color: #32CD32;"
            "border: 2px solid #32CD32;"
            "}"
            );
    nextButton = new QPushButton("Next", this);
    nextButton->setStyleSheet(
            "QPushButton {"
            "background-color: #2bb52b;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #2bb52b;"
            "}"
            "QPushButton:hover {"
            "background-color: #32CD32;"
            "border: 2px solid #32CD32;"
            "}"
    );
    finishButton = new QPushButton("Finish", this);
    finishButton->setStyleSheet(
            "QPushButton {"
            "background-color: #2bb52b;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #2bb52b;"
            "}"
            "QPushButton:hover {"
            "background-color: #32CD32;"
            "border: 2px solid #32CD32;"
            "}"
    );
    backToSetButton = new QPushButton("Back to Set", this);
    backToSetButton->setStyleSheet(
            "QPushButton {"
            "background-color: #2bb52b;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #2bb52b;"
            "}"
            "QPushButton:hover {"
            "background-color: #32CD32;"
            "border: 2px solid #32CD32;"
            "}"
    );



    ui->addWidget(submitButton);
    ui->addWidget(nextButton);
    ui->addWidget(finishButton);
    ui->addWidget(backToSetButton);

    connect(submitButton, &QPushButton::clicked, this, &MCPage::checkAnswer);
    connect(nextButton, &QPushButton::clicked, this, &MCPage::showNextQuestion);
    connect(finishButton, &QPushButton::clicked, this, &MCPage::finishQuiz);

    setupBackToSetButton();
    nextButton->hide();
    finishButton->hide();
    backToSetButton->hide();
    setLayout(ui);
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


    answerGroup->setExclusive(false);
    for (uint i = 0; i < sizeof(answerButtons)/sizeof(answerButtons[0]); ++i) {
        answerButtons[i]->setChecked(false);
    }

    submitButton->show();
    nextButton->hide();
    finishButton->hide();
    ++totalQuestions;
    answerGroup->setExclusive(true);
    std::cout << totalQuestions << std::endl;
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
        for (uint i = 0; i < sizeof(answerButtons)/sizeof(answerButtons[0]); ++i) {
            answerButtons[i]->setChecked(false);
        }
        nextButton->show();
    } else {
        finishButton->show();
    }

    for (uint i = 0; i < sizeof(answerButtons)/sizeof(answerButtons[0]); ++i) {
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
        } else if (i == static_cast<uint>(selectedAnswer)) {
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
    answerGroup->setExclusive(false);
    for (uint i = 0; i < sizeof(answerButtons)/sizeof(answerButtons[0]); ++i) {
        answerButtons[i]->setChecked(false);
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
                "QRadioButton::indicator:unchecked {"
                "background-color: #FFFFFF;"
                "}"
                "QRadioButton::indicator:checked {"
                "background-color: #32CD32;"
                "}"
        );
    }
    answerGroup->setExclusive(true);
    showQuestion();
}


void MCPage::setupBackToSetButton() {
    connect(backToSetButton, &QPushButton::clicked, this, [this]() {
        emit backToSetClicked();
    });
}