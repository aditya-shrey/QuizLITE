#include "InverseMCPage.h"
#include "../User/UserSession.h"
#include <QMessageBox>

InverseMCPage::InverseMCPage(QWidget *parent) : QWidget(parent), imc(nullptr), currentScore(0), totalQuestions(0), setSize(0) {
    setupUI();
}

void InverseMCPage::startInverseMCQuiz(const QString &setName) {
    currentSetName = setName;
    resetQuiz();

    UserSession* currentSession = UserSession::getUserSession();

    auto qaPair = currentSession->getTableKeyValues(setName.toStdString());
    int totalPairs = qaPair.size();
    if (totalPairs % 2 == 0) {
        imc = new InverseMultipleChoice(setName.toStdString(), totalPairs/2, totalPairs/2);
    } else {
        --totalPairs;
        imc = new InverseMultipleChoice(setName.toStdString(), totalPairs/2, (totalPairs/2)+1);
    }
    showQuestion();

    setSize = currentSession->getStudySetSize(setName.toStdString());
}

void InverseMCPage::resetQuiz() {
    currentScore = 0;
    totalQuestions = 0;
    questionLabel->clear();
    for (auto &button : answerButtons) {
        button->hide();
        button->setChecked(false);
        button->setStyleSheet(
                "QRadioButton {"
                "font-size: 18px;"
                "color: #FFFFFF;"
                "background-color: #403e3e;"
                "border-radius: 10px;"
                "padding: 5px;"
                "margin: 2px 0;"
                "}"
        );
    }
    submitButton->show();
    nextButton->hide();
    finishButton->hide();
    backToSetButton->show();
}

void InverseMCPage::finishQuiz() {
    float accuracy = (totalQuestions > 0) ? (static_cast<float>(currentScore) / totalQuestions * 100) : 0;

    QMessageBox::information(this,
                             "Quiz Finished",
                             "Your score: " + QString::number(currentScore) + "/" + QString::number(totalQuestions) + "\nAccuracy: " + QString::number(accuracy) + "%");

    emit backToSetClicked();  // Emit signal to navigate back to the set screen
}

void InverseMCPage::setupUI() {
    ui = new QVBoxLayout(this);

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
    setupBackToSetButton();
    ui->addWidget(backToSetButton, 0, Qt::AlignLeft);

    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->addItem(spacer); // Add a spacer to push the elements down

    questionLabel = new QLabel(this);
    questionLabel->setStyleSheet("font-size: 20px; color: #FFFFFF;");
    questionLabel->setAlignment(Qt::AlignCenter);
    ui->addWidget(questionLabel);

    answerGroup = new QButtonGroup(this);

    QVBoxLayout* answerLayout = new QVBoxLayout(); // New layout for answer buttons
    for (int i = 0; i < 4; ++i) {
        auto answerButton = new QRadioButton(this);
        answerButton->setStyleSheet(
                "QRadioButton {"
                "font-size: 18px;"
                "color: #FFFFFF;"
                "background-color: #403e3e;"
                "border-radius: 10px;"
                "padding: 5px;"
                "margin: 2px 0;"
                "}"
        );
        answerButtons.append(answerButton);
        answerLayout->addWidget(answerButton, 0, Qt::AlignBottom);
        answerGroup->addButton(answerButton, i);
    }

    spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->addItem(spacer); // Add a spacer to push the elements down

    ui->addLayout(answerLayout); // Add the answerLayout to the main layout

    QVBoxLayout* bottomLayout = new QVBoxLayout(); // New layout for the bottom buttons
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
    bottomLayout->addWidget(submitButton, 0, Qt::AlignBottom);

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
    bottomLayout->addWidget(nextButton, 0, Qt::AlignBottom);

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
    bottomLayout->addWidget(finishButton, 0, Qt::AlignBottom);

    ui->addLayout(bottomLayout); // Add the bottomLayout to the main layout

    connect(submitButton, &QPushButton::clicked, this, &InverseMCPage::checkAnswer);
    connect(nextButton, &QPushButton::clicked, this, &InverseMCPage::showNextQuestion);
    connect(finishButton, &QPushButton::clicked, this, &InverseMCPage::finishQuiz);

    nextButton->hide();
    finishButton->hide();
    backToSetButton->hide();
    setLayout(ui);
}

void InverseMCPage::showQuestion() {
    std::string question = imc->getQuestion();
    if (question.empty()) {
        finishQuiz();
        return;
    }

    questionLabel->setText(QString::fromStdString(question));
    auto options = imc->generateOptions();

    // Hide all existing buttons first
    for (auto &button : answerButtons) {
        button->hide();
    }

    // Create buttons only for non-empty options
    if (!std::get<0>(options).empty()) {
        if (answerButtons.size() <= 0) {
            auto answerButton = new QRadioButton(this);
            answerButton->setStyleSheet(
                    "QRadioButton {"
                    "font-size: 18px;"
                    "color: #FFFFFF;"
                    "background-color: #403e3e;"
                    "border-radius: 10px;"
                    "padding: 5px;"
                    "margin: 2px 0;"
                    "}"
            );
            answerButtons.append(answerButton);
            ui->addWidget(answerButton);
            answerGroup->addButton(answerButton, 0);
        }
        answerButtons[0]->setText(QString::fromStdString(std::get<0>(options)));
        answerButtons[0]->show();
    }
    if (!std::get<1>(options).empty()) {
        if (answerButtons.size() <= 1) {
            auto answerButton = new QRadioButton(this);
            answerButton->setStyleSheet(
                    "QRadioButton {"
                    "font-size: 18px;"
                    "color: #FFFFFF;"
                    "background-color: #403e3e;"
                    "border-radius: 10px;"
                    "padding: 5px;"
                    "margin: 2px 0;"
                    "}"
            );
            answerButtons.append(answerButton);
            ui->addWidget(answerButton);
            answerGroup->addButton(answerButton, 1);
        }
        answerButtons[1]->setText(QString::fromStdString(std::get<1>(options)));
        answerButtons[1]->show();
    }
    if (!std::get<2>(options).empty()) {
        if (answerButtons.size() <= 2) {
            auto answerButton = new QRadioButton(this);
            answerButton->setStyleSheet(
                    "QRadioButton {"
                    "font-size: 18px;"
                    "color: #FFFFFF;"
                    "background-color: #403e3e;"
                    "border-radius: 10px;"
                    "padding: 5px;"
                    "margin: 2px 0;"
                    "}"
            );
            answerButtons.append(answerButton);
            ui->addWidget(answerButton);
            answerGroup->addButton(answerButton, 2);
        }
        answerButtons[2]->setText(QString::fromStdString(std::get<2>(options)));
        answerButtons[2]->show();
    }
    if (!std::get<3>(options).empty()) {
        if (answerButtons.size() <= 3) {
            auto answerButton = new QRadioButton(this);
            answerButton->setStyleSheet(
                    "QRadioButton {"
                    "font-size: 18px;"
                    "color: #FFFFFF;"
                    "background-color: #403e3e;"
                    "border-radius: 10px;"
                    "padding: 5px;"
                    "margin: 2px 0;"
                    "}"
            );
            answerButtons.append(answerButton);
            ui->addWidget(answerButton);
            answerGroup->addButton(answerButton, 3);
        }
        answerButtons[3]->setText(QString::fromStdString(std::get<3>(options)));
        answerButtons[3]->show();
    }

    answerGroup->setExclusive(false);
    for (auto &button : answerButtons) {
        button->setChecked(false);
    }
    submitButton->show();
    nextButton->hide();
    finishButton->hide();
    ++totalQuestions;
    answerGroup->setExclusive(true);
}

void InverseMCPage::checkAnswer() {
    int selectedAnswer = answerGroup->checkedId();
    if (selectedAnswer == -1) {
        QMessageBox::warning(this, "No Selection", "Select an answer before submitting");
        return;
    }
    std::string correctAnswer = imc->getAnswer();
    bool isCorrect = (answerButtons[selectedAnswer])->text() == QString::fromStdString(correctAnswer);

    if (isCorrect) {
        ++currentScore;
    }

    imc->updateScoresInTable(isCorrect);
    submitButton->hide();
    if (imc->goToNextQuestion()) {
        for (auto &button : answerButtons) {
            button->setChecked(false);
        }
        nextButton->show();
    } else {
        finishButton->show();
    }

    for (auto &button : answerButtons) {
        if (button->text() == QString::fromStdString(correctAnswer)) {
            button->setStyleSheet(
                    "QRadioButton {"
                    "font-size: 18px;"
                    "color: #FFFFFF;"
                    "background-color: green;"
                    "border-radius: 10px;"
                    "padding: 5px;"
                    "margin: 2px 0;"
                    "}"
            );
        } else if (button == answerButtons[selectedAnswer]) {
            button->setStyleSheet(
                    "QRadioButton {"
                    "font-size: 18px;"
                    "color: #FFFFFF;"
                    "background-color: red;"
                    "border-radius: 10px;"
                    "padding: 5px;"
                    "margin: 2px 0;"
                    "}"
            );
        }
    }
}

void InverseMCPage::showNextQuestion() {
    answerGroup->setExclusive(false);
    for (auto &button : answerButtons) {
        button->setChecked(false);
        button->setStyleSheet(
                "QRadioButton {"
                "font-size: 18px;"
                "color: #FFFFFF;"
                "background-color: #403e3e;"
                "border-radius: 10px;"
                "padding: 5px;"
                "margin: 2px 0;"
                "}"
        );
    }
    answerGroup->setExclusive(true);
    showQuestion();
}

void InverseMCPage::setupBackToSetButton() {
    connect(backToSetButton, &QPushButton::clicked, this, [this]() {
        emit backToSetClicked();
    });
}
