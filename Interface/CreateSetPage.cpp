//
// Created by Fardeen Bablu on 7/13/24.
//

#include "CreateSetPage.h"

CreateSetPage::CreateSetPage(QWidget *parent) :
        QWidget(parent),
        backToLibraryButton(new QPushButton("Back to Library", this)),
        ui(new QVBoxLayout(this)),
        pageLabel(new QLabel("Create New Set", this)),
        setNameLabel(new QLabel("Set Name:", this)),
        setNameInput(new QLineEdit(this)),
        confirmButton(new QPushButton("Confirm", this)) {

    // Set stylesheets for the widgets
    this->setStyleSheet("background-color: #000000;");
    pageLabel->setStyleSheet("color: #5DF779; font-size: 24px; font-weight: bold;");
    setNameLabel->setStyleSheet("color: #FFFFFF; font-size: 20px;");
    setNameInput->setStyleSheet("font-size: 18px;");
    confirmButton->setStyleSheet(
            "QPushButton {"
            "background-color: #4bd664;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #4bd664;"
            "}"
            "QPushButton:hover {"
            "background-color: #5DF779;"
            "border: 2px solid #5DF779;"
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
    mainLayout->addWidget(setNameLabel, 0, Qt::AlignLeft);
    mainLayout->addWidget(setNameInput);
    mainLayout->addWidget(confirmButton);
    mainLayout->addStretch(1); // Add a stretch to push the elements up
    mainLayout->addWidget(backToLibraryButton, 0, Qt::AlignLeft | Qt::AlignBottom);

    // Set the layout to the main UI
    ui->addLayout(mainLayout);
    setLayout(ui);

    // Connect the confirm button signal
    connect(confirmButton, &QPushButton::clicked, [this]() {
        QString setName = setNameInput->text();
        UserSession *session = UserSession::getUserSession();

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

        if (setName.isEmpty()) {
            msgBox.setText("The set name must be non-empty.");
            msgBox.setWindowTitle("Empty Set Name");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        } else if (setName == "set_names") {
            msgBox.setText("'set_names' is reserved.");
            msgBox.setWindowTitle("Invalid set name");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        } else if (session->existsStudySet(setName.toStdString())) {
            msgBox.setText("The set name " + setName + " has already been created.");
            msgBox.setWindowTitle("Invalid set name");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        } else {
            emit setNameConfirmed(setName);
            setNameInput->clear();
        }
    });

    setupBackToLibrary();
}

void CreateSetPage::setupBackToLibrary() {
    connect(backToLibraryButton, &QPushButton::clicked, this, [this]() {
        emit backToLibraryClicked();
        setNameInput->clear();
    });
}



