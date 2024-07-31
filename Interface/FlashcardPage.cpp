#include "FlashcardPage.h"
#include <QMessageBox>
#include "../User/UserSession.h"

FlashcardPage::FlashcardPage(QWidget *parent) : QWidget(parent), fc(nullptr), currentIndex(0), totalFlashcards(0) {
    setupUI();
}

void FlashcardPage::startFlashcardQuiz(const QString &setName) {
    currentSetName = setName;
    resetFlashcardSession();
    fc = new Flashcards(setName.toStdString());

    // FEELS DIRTY :O
    // Note: Get flashcards directly from the session to count them
    auto flashCardsPairs = UserSession::getUserSession()->getTableKeyValues(setName.toStdString());
    totalFlashcards = flashCardsPairs.size();
    std::cout << totalFlashcards << std::endl;


    showNextFlashcard();
}

void FlashcardPage::resetFlashcardSession() {
    currentIndex = 0;
    flashcardLabel->clear();
    showAnswerButton->show();
    nextButton->hide();
    finishButton->hide();
    backToSetButton->hide();
}

void FlashcardPage::finishFlashcardSession() {
    QMessageBox::information(this, "Session Finished", "You have reviewed all flashcards in the set.");
    finishButton->hide();
    nextButton->hide();
    backToSetButton->show();
}

void FlashcardPage::setupUI() {
    ui = new QVBoxLayout(this);
    flashcardLabel = new QLabel(this);
    flashcardLabel->setStyleSheet("font-size: 20px; color: #FFFFFF;");
    flashcardLabel->setAlignment(Qt::AlignCenter);
    ui->addWidget(flashcardLabel);

    showAnswerButton = new QPushButton("Show Answer", this);
    showAnswerButton->setStyleSheet(
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

    ui->addWidget(showAnswerButton);
    ui->addWidget(nextButton);
    ui->addWidget(finishButton);
    ui->addWidget(backToSetButton);

    connect(showAnswerButton, &QPushButton::clicked, this, &FlashcardPage::showAnswer);
    connect(nextButton, &QPushButton::clicked, this, &FlashcardPage::showNextFlashcard);
    connect(finishButton, &QPushButton::clicked, this, &FlashcardPage::finishFlashcardSession);

    setupBackToSetButton();
    nextButton->hide();
    finishButton->hide();
    backToSetButton->hide();
    setLayout(ui);
}

void FlashcardPage::showNextFlashcard() {
    if (!fc->goToNextQuestion()) {
        finishFlashcardSession();
        return;
    }

    flashcardLabel->setText(QString::fromStdString(fc->getQuestion()));
    showAnswerButton->show();
    nextButton->hide();
    finishButton->hide();
    ++currentIndex;
}

void FlashcardPage::showAnswer() {
    flashcardLabel->setText(QString::fromStdString(fc->getAnswer()));
    showAnswerButton->hide();
    nextButton->show();
}

void FlashcardPage::setupBackToSetButton() {
    connect(backToSetButton, &QPushButton::clicked, this, [this]() {
        emit backToSetClicked();
    });
}
