#include "EnterSetPage.h"
#include "../User/UserSession.h"
#include <iostream>

EnterSetPage::EnterSetPage(QWidget *parent) :
        QWidget(parent),
        backToLibraryButton(new QPushButton("Back to Library", this)),
        ui(new QVBoxLayout(this)),
        setNameLabel(new QLabel(this)),
        pageLabel(new QLabel("Set Content", this)),
        qaListWidget(new QListWidget(this)) {

    // Set stylesheets for the widgets
    this->setStyleSheet("background-color: #000000;");
    setNameLabel->setStyleSheet("color: #32CD32; font-size: 30px; font-weight: bold;");
    pageLabel->setStyleSheet("color: #FFFFFF; font-size: 24px; font-weight: bold;");
    backToLibraryButton->setStyleSheet("background-color: #90EE90; color: #000000; font-size: 18px; padding: 10px; border-radius: 15px; border: 2px solid #5DF779;");

    QPushButton *addQuestionButton = new QPushButton("Add to Set", this);
    addQuestionButton->setStyleSheet("background-color: #32CD32; color: #000000; font-size: 18px; padding: 5px; border-radius: 15px; border: 2px solid #32CD32;");
    QPushButton *deleteSetButton = new QPushButton("Delete Set", this);
    deleteSetButton->setStyleSheet("background-color: #FF6347; color: #000000; font-size: 18px; padding: 5px; border-radius: 15px; border: 2px solid #FF6347;");

    // Create layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(10);
    mainLayout->addWidget(setNameLabel, 0, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(pageLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->addWidget(qaListWidget);
    mainLayout->addWidget(addQuestionButton);
    mainLayout->addWidget(deleteSetButton);
    mainLayout->addStretch(1); // Add a stretch to push the elements up
    mainLayout->addWidget(backToLibraryButton, 0, Qt::AlignLeft | Qt::AlignBottom);

    // Set the layout to the main UI
    ui->addLayout(mainLayout);
    setLayout(ui);

    // Connect signals
    connect(addQuestionButton, &QPushButton::clicked, this, &EnterSetPage::showAddQuestionPage);
    connect(deleteSetButton, &QPushButton::clicked, [this]() {
        emit confirmDeleteSet(currentSetName);
    });

    setupBackButton();
}

void EnterSetPage::addSet(const QString &setName) {
    std::cout << "Adding set: " << setName.toStdString() << std::endl;
    QWidget *setWidget = new QWidget(this);
    QHBoxLayout *setLayout = new QHBoxLayout(setWidget);

    QPushButton *setButton = new QPushButton(setName, this);
    connect(setButton, &QPushButton::clicked, [this, setName]() {
        emit openSetClicked(setName);
    });

    QPushButton *deleteButton = new QPushButton("Delete", this);
    connect(deleteButton, &QPushButton::clicked, [this, setName]() {
        emit confirmDeleteSet(setName);
    });

    setLayout->addWidget(setButton);
    setLayout->addWidget(deleteButton);

    ui->addWidget(setWidget);
    setWidgets[setName] = setWidget;
}

void EnterSetPage::setSetName(const QString &setName) {
    std::cout << "Setting set name: " << setName.toStdString() << std::endl;
    currentSetName = setName;
    setNameLabel->setText(setName);
}

void EnterSetPage::setQAList(const QString& setName) {
    std::cout << "Setting QA list for set: " << setName.toStdString() << std::endl;
    UserSession *session = UserSession::getUserSession();
    qaListWidget->clear();

    if (session->existsStudySet(setName.toStdString())) {
        auto qaList = session->getTableKeyValues(setName.toStdString());

        for (const auto &qa : qaList) {
            QString key = QString::fromStdString(qa.first);
            QString value = QString::fromStdString(qa.second);

            QWidget *qaWidget = new QWidget(this);
            QHBoxLayout *qaLayout = new QHBoxLayout(qaWidget);

            QLabel *qaLabel = new QLabel("Q: " + key + " - A: " + value, this);

            QPushButton *deleteButton = new QPushButton("Delete", this);
            deleteButton->setFixedHeight(25);
            connect(deleteButton, &QPushButton::clicked, [this, setName, key, qaWidget]() {
                deleteKeyValuePair(setName, key);
                qaWidget->deleteLater();
            });

            QPushButton *adjustButton = new QPushButton("Adjust", this);
            adjustButton->setFixedHeight(25);
            connect(adjustButton, &QPushButton::clicked, [this, setName, key, value]() {
                bool ok;
                QString newValue = QInputDialog::getText(this, tr("Adjust Value"),
                                                         tr("New value for %1:").arg(key), QLineEdit::Normal,
                                                         value, &ok);
                if (ok && !newValue.isEmpty()) {
                    adjustKeyValuePair(setName, key, newValue);
                }
            });

            qaLayout->addWidget(qaLabel);
            qaLayout->addWidget(deleteButton);
            qaLayout->addWidget(adjustButton);

            QListWidgetItem *item = new QListWidgetItem(qaListWidget);
            item->setSizeHint(qaWidget->sizeHint());
            qaListWidget->addItem(item);
            qaListWidget->setItemWidget(item, qaWidget);
        }
    }
}

void EnterSetPage::clearAllEntries() {
    std::cout << "Clearing all entries" << std::endl;
    qaListWidget->clear();
}

void EnterSetPage::setupBackButton() {
    std::cout << "Setting up back button" << std::endl;
    connect(backToLibraryButton, &QPushButton::clicked, this, [this]() {
        std::cout << "Back to Library button clicked" << std::endl;
        emit backToLibraryClicked();
    });
}

void EnterSetPage::deleteSet(const QString &setName) {
    std::cout << "Deleting set: " << setName.toStdString() << std::endl;
    UserSession *session = UserSession::getUserSession();
    if (session->deleteStudySet(setName.toStdString())) {
        emit deleteSetClicked(setName);
        auto it = setWidgets.find(setName);
        if (it != setWidgets.end()) {
            it->second->deleteLater();
            setWidgets.erase(it);
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete set.");
    }
}

void EnterSetPage::deleteKeyValuePair(const QString &setName, const QString &key) {
    std::cout << "Deleting key-value pair: " << key.toStdString() << " from set: " << setName.toStdString() << std::endl;
    UserSession *session = UserSession::getUserSession();
    if (session->deleteFromStudySet(setName.toStdString(), key.toStdString())) {
        emit deleteKeyValuePairClicked(setName, key);
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete key-value pair.");
    }
}

void EnterSetPage::adjustKeyValuePair(const QString &setName, const QString &key, const QString &newValue) {
    std::cout << "Adjusting key-value pair: " << key.toStdString() << " to new value: " << newValue.toStdString() << " in set: " << setName.toStdString() << std::endl;
    UserSession *session = UserSession::getUserSession();
    if (session->deleteFromStudySet(setName.toStdString(), key.toStdString()) &&
        session->addToStudySet(setName.toStdString(), key.toStdString(), newValue.toStdString())) {
        emit adjustKeyValuePairClicked(setName, key, newValue);
        setQAList(setName);  // Refresh the QA list to reflect the changes
    } else {
        QMessageBox::warning(this, "Error", "Failed to adjust key-value pair.");
    }
}

void EnterSetPage::showAddQuestionPage() {
    std::cout << "Showing add question page for set: " << currentSetName.toStdString() << std::endl;
    bool ok;
    QString key = QInputDialog::getText(this, tr("New Question"),
                                        tr("Enter new question:"), QLineEdit::Normal,
                                        QString(), &ok);
    if (!ok || key.isEmpty() || key == "set_names") {
        QMessageBox::warning(this, "Invalid Key", "The key is invalid.");
        return;
    }

    UserSession *session = UserSession::getUserSession();
    if (session->existsStudySet(currentSetName.toStdString())) {
        auto qaList = session->getTableKeyValues(currentSetName.toStdString());
        for (const auto &qa : qaList) {
            if (QString::fromStdString(qa.first) == key) {
                QMessageBox::warning(this, "Duplicate Key", "This key already exists in the set.");
                return;
            }
        }
    }

    QString value = QInputDialog::getText(this, tr("New Answer"),
                                          tr("Enter new answer:"), QLineEdit::Normal,
                                          QString(), &ok);
    if (ok && !value.isEmpty()) {
        session->addToStudySet(currentSetName.toStdString(), key.toStdString(), value.toStdString());
        setQAList(currentSetName);  // Refresh the QA list to reflect the changes
    } else {
        QMessageBox::warning(this, "Invalid Value", "The value cannot be empty.");
    }
}
