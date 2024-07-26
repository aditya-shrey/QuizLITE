//
// Created by Fardeen Bablu on 7/13/24.
//

#include "CreateSetPage.h"

CreateSetPage::CreateSetPage(QWidget *parent) :
        QWidget(parent),
        backToLibraryButton(new QPushButton("< Back to Library", this)),
        ui(new QVBoxLayout(this)),
        pageLabel(new QLabel("Name your Set")),
        setNameLabel(new QLabel("Set Name:", this)),
        setNameInput(new QLineEdit(this)),
        confirmButton(new QPushButton("Confirm", this)) {

    ui->addWidget(pageLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    ui->addWidget(setNameLabel);
    ui->addWidget(setNameInput);
    ui->addWidget(confirmButton);
    ui->addWidget(backToLibraryButton);
    setupBackToLibrary();
    // Connects hitting the confirm button, and takes the "this" pointer into a
    // lambda function, which then emits setNameConfirmed signal with text
    // provided [still a little confusing, but just "emitting the signal"
    connect(confirmButton, &QPushButton::clicked, [this]() {
        emit setNameConfirmed(setNameInput->text());
        setNameInput->clear();
    });
}


void CreateSetPage::setupBackToLibrary() {
    connect(backToLibraryButton, &QPushButton::clicked, this, [this]() {
        emit backToLibraryClicked();
        setNameInput->clear();
    });
}



