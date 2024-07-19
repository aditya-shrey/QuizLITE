//
// Created by Fardeen Bablu on 7/18/24.
//

#include "EnterSetPage.h"
#include "../User/UserSession.h"

EnterSetPage::EnterSetPage(QWidget *parent) :
        QWidget(parent),
        backToLibraryButton(new QPushButton("< Back to Library", this)),
        ui(new QVBoxLayout(this)),
        setNameLabel(new QLabel(this)),
        pageLabel(new QLabel(this)),
        qaListWidget(new QListWidget(this)) {

    ui->addWidget(setNameLabel);
    ui->addWidget(pageLabel);
    ui->addWidget(qaListWidget);
    ui->addWidget(backToLibraryButton);
    setupBackButton();
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

void EnterSetPage::setQAList(const QString& setName) {
    UserSession *session = UserSession::getUserSession();
    qaListWidget->clear();

    if (session->existsStudySet(setName.toStdString())) {
        auto qaList = session->getTableKeyValues(setName.toStdString());

        for (const auto &qa : qaList) {
            QString key = QString::fromStdString(qa.first);
            QString value = QString::fromStdString(qa.second);
            qaListWidget->addItem("Q: " + key + " - A: " + value);
        }
    }
}

void EnterSetPage::clearAllEntries() {
    qaListWidget->clear();
}

//CREATE A BACKTO LIBRARY BUTTON THAT ONCE CLICKED GOES BACK TO THE LIBRARY PAGE
void EnterSetPage::setupBackButton() {
    connect(backToLibraryButton, &QPushButton::clicked, this, [this]() {
        emit backToLibraryClicked();
    });
}