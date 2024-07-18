//
// Created by Fardeen Bablu on 7/18/24.
//

#include "EnterSetPage.h"

EnterSetPage::EnterSetPage(QWidget *parent) :
        QWidget(parent),
        ui(new QVBoxLayout(this)),
        setNameLabel(new QLabel(this)),
        pageLabel(new QLabel(this)),
        qaListWidget(new QListWidget(this)) {

    ui->addWidget(setNameLabel);
    ui->addWidget(pageLabel);
    ui->addWidget(qaListWidget);
    setLayout(ui);
}

void EnterSetPage::addSet(const QString &setName) {
    QPushButton *setButton = new QPushButton(setName, this);
    connect(setButton, &QPushButton::clicked, [this, setName]() {
        emit openSetClicked(setName);
    });
    ui->addWidget(setButton);
}

void EnterSetPage::setSetName(const QString &setName) {
    setNameLabel->setText(setName);
}

void EnterSetPage::setQAList(const QList<QPair<QString, QString>> &qaList) {
    qaListWidget->clear();
    for (const auto &qa : qaList) {
        qaListWidget->addItem("Q: " + qa.first + " - A: " + qa.second);
    }
}

void EnterSetPage::clearAllEntries() {
    qaListWidget->clear();
}

//CREATE A BACKTO LIBRARY BUTTON THAT ONCE CLICKED GOES BACK TO THE LIBRARY PAGE