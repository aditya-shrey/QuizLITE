//
// Created by Fardeen Bablu on 7/17/24.
//

#include "AddQuestionsPage.h"

AddQuestionsPage::AddQuestionsPage(QWidget *parent) :
        QWidget(parent),
        backToLibraryButton(new QPushButton("Back to Library", this)),
        ui(new QVBoxLayout(this)),
        pageLabel(new QLabel("Populate your Set", this)),
        questionInput(new QLineEdit(this)),
        answerInput(new QLineEdit(this)),
        addToSetButton(new QPushButton("Add to Set", this)),
        finishButton(new QPushButton("Finish", this)),
        qaListWidget(new QListWidget(this)),
        addedQuestions(new QSet<QString>) { // Initialize the QSet

    // Set stylesheets for the widgets
    this->setStyleSheet("background-color: #000000;");
    pageLabel->setStyleSheet("color: #5DF779; font-size: 24px; font-weight: bold;");
    questionInput->setStyleSheet("font-size: 18px;");
    answerInput->setStyleSheet("font-size: 18px;");
    addToSetButton->setStyleSheet(
            "QPushButton {"
            "background-color: #32CD32;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #32CD32;"
            "}"
            "QPushButton:hover {"
            "background-color: #26de26;"
            "border: 2px solid #26de26;"
            "}"
    );
    finishButton->setStyleSheet(
            "QPushButton {"
            "background-color: #90EE90;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #90EE90;"
            "}"
            "QPushButton:hover {"
            "background-color: #80ed80;"
            "border: 2px solid #80ed80;"
            "}"
    );
    backToLibraryButton->setStyleSheet(
            "QPushButton {"
            "background-color: #7bd17b;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #7bd17b;"
            "}"
            "QPushButton:hover {"
            "background-color: #90EE90;"
            "border: 2px solid #90EE90;"
            "}"
    );

    // Create layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(10);
    mainLayout->addWidget(pageLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->addWidget(new QLabel("Question:", this));
    mainLayout->addWidget(questionInput);
    mainLayout->addWidget(new QLabel("Answer:", this));
    mainLayout->addWidget(answerInput);
    mainLayout->addWidget(addToSetButton);
    mainLayout->addWidget(finishButton);
    mainLayout->addWidget(qaListWidget);
    mainLayout->addStretch(1); // Add a stretch to push the elements up
    mainLayout->addWidget(backToLibraryButton, 0, Qt::AlignLeft | Qt::AlignBottom);

    // Set the layout to the main UI
    ui->addLayout(mainLayout);
    setLayout(ui);

    // Connect signals
    connect(addToSetButton, &QPushButton::clicked, this, &AddQuestionsPage::addToSet);
    connect(finishButton, &QPushButton::clicked, [this]() {
        emit finishedClicked();
        qaListWidget->clear();
        addedQuestions->clear();
    });

    setupBackToLibrary();
}

void AddQuestionsPage::addToSet() {
    QString question = questionInput->text();
    QString answer = answerInput->text();

    QMessageBox msgBox;
    msgBox.setStyleSheet(
            "QMessageBox {"
            "background-color: #2b2b2b;"
            "color: #ffffff;"
            "font-size: 16px;"
            "}"
            "QPushButton {"
            "font-size: 14px;"
            "padding: 5px;"
            "border-radius: 5px;"
            "}"
    );

    if (question.isEmpty() || answer.isEmpty()) {
        msgBox.setText("Both question and answer must be non-empty.");
        msgBox.setWindowTitle("Empty Entry");
        msgBox.exec();
    } else if (addedQuestions->contains(question)) {
        msgBox.setText("This question has already been added.");
        msgBox.setWindowTitle("Duplicate Entry");
        msgBox.exec();
    } else {
        addedQuestions->insert(question);
        emit addToSetClicked(question, answer);
        qaListWidget->addItem("Q: " + question + " | A: " + answer);
        questionInput->clear();
        answerInput->clear();
    }
}

void AddQuestionsPage::setupBackToLibrary() {
    connect(backToLibraryButton, &QPushButton::clicked, this, [this]() {
        emit backToLibraryClicked();
        questionInput->clear();
        answerInput->clear();
        addedQuestions->clear();
    });
}