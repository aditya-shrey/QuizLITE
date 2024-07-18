//
// Created by Fardeen Bablu on 7/17/24.
//

#include "AddQuestionsPage.h"
#include "CreateSetPage.h"


AddQuestionsPage::AddQuestionsPage(QWidget *parent) :
        QWidget(parent),
        ui(new QVBoxLayout(this)),
        pageLabel(new QLabel("Populate your Set")),
        questionInput(new QLineEdit(this)),
        answerInput(new QLineEdit(this)),
        addToSetButton(new QPushButton("Add to Set", this)),
        finishButton(new QPushButton("Finish", this)),
        qaListWidget(new QListWidget(this))
{
    ui->addWidget(pageLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    ui->addWidget(new QLabel("Question 1:", this));
    ui->addWidget(questionInput);
    ui->addWidget(new QLabel("Answer 1:", this));
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
    setLayout(ui);
}


void AddQuestionsPage::addToSet() {
    QString question = questionInput->text();
    QString answer = answerInput->text();
    emit addToSetClicked(question, answer);
    qaListWidget->addItem("Q: " + question + " - A: " + answer);
    questionInput->clear();
    answerInput->clear();
}