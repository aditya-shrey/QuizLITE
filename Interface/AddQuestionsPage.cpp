//
// Created by Fardeen Bablu on 7/17/24.
//

#include "AddQuestionsPage.h"
#include "CreateSetPage.h"


AddQuestionsPage::AddQuestionsPage(QWidget *parent) :
        QWidget(parent),
        backToLibraryButton(new QPushButton("< Back to Library", this)),
        ui(new QVBoxLayout(this)),
        pageLabel(new QLabel("Populate your Set")),
        questionInput(new QLineEdit(this)),
        answerInput(new QLineEdit(this)),
        addToSetButton(new QPushButton("Add to Set", this)),
        finishButton(new QPushButton("Finish", this)),
        qaListWidget(new QListWidget(this)) {

    ui->addWidget(pageLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    ui->addWidget(new QLabel("Question:", this));
    ui->addWidget(questionInput);
    ui->addWidget(new QLabel("Answer:", this));
    ui->addWidget(answerInput);
    ui->addWidget(addToSetButton);
    ui->addWidget(finishButton);
    ui->addWidget(qaListWidget);

    //only need to connect these buttons, not the inputs. The buttons
    // basically do all the work by taking in what's in the input
    connect(addToSetButton, &QPushButton::clicked, this,&AddQuestionsPage::addToSet);
    connect(finishButton, &QPushButton::clicked, [this]() {
        emit finishedClicked();
        qaListWidget->clear();
    });

    ui->addWidget(backToLibraryButton);
    setupBackToLibrary();
    setLayout(ui);
}


void AddQuestionsPage::addToSet() {
    QString question = questionInput->text();
    QString answer = answerInput->text();
    if (question.isEmpty() || answer.isEmpty()) {
        QMessageBox::information(this, "Empty Entry", "Both question and answer must be non-empty.");
    } else {
        emit addToSetClicked(question, answer);
        qaListWidget->addItem("Q: " + question + " - A: " + answer);
        questionInput->clear();
        answerInput->clear();
    }
}

void AddQuestionsPage::setupBackToLibrary() {
    connect(backToLibraryButton, &QPushButton::clicked, this, [this]() {
        emit backToLibraryClicked();
        questionInput->clear();
        answerInput->clear();
    });
}