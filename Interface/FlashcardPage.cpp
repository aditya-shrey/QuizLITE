#include "FlashcardPage.h"
#include <QMessageBox>
#include "../User/UserSession.h"

FlashcardPage::FlashcardPage(QWidget *parent) : QWidget(parent), fc(nullptr), currentIndex(0), totalFlashcards(0), isAnswerShown(false) {
    setupUI();
}

void FlashcardPage::startFlashcardQuiz(const QString &setName) {
    currentSetName = setName;
    resetFlashcardSession();
    fc = new Flashcards(setName.toStdString());

    auto flashCardsPairs = UserSession::getUserSession()->getTableKeyValues(setName.toStdString());
    totalFlashcards = flashCardsPairs.size();
    std::cout << totalFlashcards << std::endl;

    showNextFlashcard();
}

void FlashcardPage::resetFlashcardSession() {
    currentIndex = 0;
    isAnswerShown = false;
    flashcardButton->setText("");
    nextButton->show();
    prevButton->show();
    finishButton->hide();
    backToSetButton->show();
}

void FlashcardPage::finishFlashcardSession() {
    QMessageBox::information(this, "Session Finished", "You have reviewed all flashcards in the set.");
    finishButton->hide();
    nextButton->hide();
    prevButton->hide();
    backToSetButton->show();
}

void FlashcardPage::setupUI() {
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

    flashcardButton = new QPushButton(this);
    flashcardButton->setStyleSheet(
            "QPushButton {"
            "background-color: #FFFFFF;"
            "color: #000000;"
            "font-size: 20px;"
            "padding: 10px;"
            "border: 2px solid #2bb52b;"
            "border-radius: 15px;"
            "}"
            "QPushButton:hover {"
            "background-color: #F0F0F0;"
            "border: 2px solid #32CD32;"
            "}"
    );
    connect(flashcardButton, &QPushButton::clicked, this, &FlashcardPage::toggleFlashcard);
    ui->addWidget(flashcardButton, 0, Qt::AlignCenter);

    QHBoxLayout *navigationLayout = new QHBoxLayout;

    prevButton = new QPushButton("<", this);
    prevButton->setStyleSheet(
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
    connect(prevButton, &QPushButton::clicked, this, &FlashcardPage::showPreviousFlashcard);
    navigationLayout->addWidget(prevButton);

    nextButton = new QPushButton(">", this);
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
    connect(nextButton, &QPushButton::clicked, this, &FlashcardPage::showNextFlashcard);
    navigationLayout->addWidget(nextButton);

    ui->addLayout(navigationLayout);

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
    connect(finishButton, &QPushButton::clicked, this, &FlashcardPage::finishFlashcardSession);
    ui->addWidget(finishButton);

    nextButton->show();
    prevButton->show();
    finishButton->hide();
    backToSetButton->hide();
    setLayout(ui);
}

void FlashcardPage::showNextFlashcard() {
    if (!fc->goToNextQuestion()) {
        fc->resetIndex();
    }
    isAnswerShown = false;
    flashcardButton->setText(QString::fromStdString(fc->getQuestion()));
}

void FlashcardPage::showPreviousFlashcard() {
    if (!fc->goToPrevQuestion()) {
        fc->setToLastIndex();
    }
    isAnswerShown = false;
    flashcardButton->setText(QString::fromStdString(fc->getQuestion()));
}

void FlashcardPage::toggleFlashcard() {
    if (isAnswerShown) {
        flashcardButton->setText(QString::fromStdString(fc->getQuestion()));
    } else {
        flashcardButton->setText(QString::fromStdString(fc->getAnswer()));
    }
    isAnswerShown = !isAnswerShown;
}

void FlashcardPage::setupBackToSetButton() {
    connect(backToSetButton, &QPushButton::clicked, this, [this]() {
        emit backToSetClicked();
    });
}

void FlashcardPage::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    int screenHeight = QApplication::primaryScreen()->size().height();
    int maxHeight = screenHeight * 0.8;

    int width = this->width() - 40;
    int height = width * 0.6;
    if (height > maxHeight * 0.95) {
        height = maxHeight;
        width = height / 0.6;
    }
    flashcardButton->setFixedSize(width, height);
    flashcardButton->move((this->width() - width) / 2, flashcardButton->y());
}
