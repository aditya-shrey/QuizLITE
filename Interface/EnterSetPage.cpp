#include "EnterSetPage.h"



EnterSetPage::EnterSetPage(QWidget *parent) :
        QWidget(parent),
        backToLibraryButton(new QPushButton("Back to Library", this)),
        setNameLabel(new QLabel(this)),
        pageLabel(new QLabel("Set Content", this)),
        qaListWidget(new QListWidget(this)),
        scrollArea(new QScrollArea(this)),
        studyMethodsPageStack(new QStackedWidget(this)),
        mcButton(new QPushButton("Multiple Choice", this)),
        inverseMCButton(new QPushButton("Inverse Multiple Choice", this)),
        flashcardsButton(new QPushButton("Flashcards")),
        studyMethodsLabel(new QLabel("Studying Methods", this)),
        m_shortcuts(reinterpret_cast<Shortcuts *>(new QShortcut(this))),
        setSize(0)
{
    // Set stylesheets for the widgets
    this->setStyleSheet("background-color: #000000;");
    setNameLabel->setStyleSheet("color: #32CD32; font-size: 30px; font-weight: bold;");
    pageLabel->setStyleSheet("color: #FFFFFF; font-size: 24px; font-weight: bold;");
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

    QHBoxLayout *topRowLayout = new QHBoxLayout();
    topRowLayout->addStretch(1);
    topRowLayout->addWidget(studyMethodsLabel, 0, Qt::AlignLeft);
    topRowLayout->addWidget(mcButton, 0, Qt::AlignRight);
    topRowLayout->addWidget(inverseMCButton, 0, Qt::AlignRight);
    topRowLayout->addWidget(flashcardsButton, 0, Qt::AlignRight);
    mcButton->setStyleSheet(
            "QPushButton {"
            "background-color: #00A7E1;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #00A7E1;"
            "}"
            "QPushButton:hover {"
            "background-color: #6BCDEE;"
            "border: 2px solid #6BCDEE;"
            "}"
    );

    inverseMCButton->setStyleSheet(
            "QPushButton {"
            "background-color: #C55ADD;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #C55ADD;"
            "}"
            "QPushButton:hover {"
            "background-color: #D88BE9;"
            "border: 2px solid #D88BE9;"
            "}"
    );

    flashcardsButton->setStyleSheet(
            "QPushButton {"
            "background-color: #E9A003;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #E9A003;"
            "}"
            "QPushButton:hover {"
            "background-color: #E9AE30;"
            "border: 2px solid #E9AE30;"
            "}"
    );

    studyMethodsLabel->setStyleSheet("color: #FFFFFF; font-size: 18px; font-weight: normal; padding: 10px");


    QPushButton *addQuestionButton = new QPushButton("Add to Set", this);
    addQuestionButton->setStyleSheet(
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

    QPushButton *deleteSetButton = new QPushButton("Delete Set", this);
    deleteSetButton->setStyleSheet(
            "QPushButton {"
            "background-color: #ed583e;"
            "color: #000000;"
            "font-size: 18px;"
            "padding: 5px;"
            "border-radius: 15px;"
            "border: 2px solid #ed583e;"
            "}"
            "QPushButton:hover {"
            "background-color: #FF6347;"
            "border: 2px solid #FF6347;"
            "}"
    );

    // Create the main layout for the entire page
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(10);
    mainLayout->addWidget(setNameLabel, 0, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(pageLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->addLayout(topRowLayout);

    // Create a scroll area for the QA list
    scrollArea->setWidgetResizable(true);
    QWidget *scrollAreaContent = new QWidget(scrollArea);
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout(scrollAreaContent);
    scrollAreaLayout->addWidget(qaListWidget);
    scrollAreaContent->setLayout(scrollAreaLayout);
    scrollArea->setWidget(scrollAreaContent);

    mainLayout->addWidget(scrollArea);
    mainLayout->addStretch(1);
    mainLayout->addWidget(addQuestionButton, 0, Qt::AlignBottom);

    // Create a horizontal layout for the bottom buttons
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(backToLibraryButton, 0, Qt::AlignLeft);
    bottomLayout->addStretch(1);
    bottomLayout->addWidget(deleteSetButton, 0, Qt::AlignRight);

    mainLayout->addLayout(bottomLayout);

    // Create a QWidget for the scroll area content
    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    // Set the mainWidget to the scroll area
    QScrollArea *pageScrollArea = new QScrollArea(this);
    pageScrollArea->setWidgetResizable(true);
    pageScrollArea->setWidget(mainWidget);

    // Create a main layout for the EnterSetPage
    QVBoxLayout *pageLayout = new QVBoxLayout(this);
    pageLayout->addWidget(pageScrollArea);
    setLayout(pageLayout);

    // Connect signals
    connect(addQuestionButton, &QPushButton::clicked, this, &EnterSetPage::showAddQuestionPage);
    connect(deleteSetButton, &QPushButton::clicked, [this]() {
        emit confirmDeleteSet(currentSetName);
    });

    mainLayout->addWidget(studyMethodsPageStack);
    setupStudyMethodButtons();
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

        int itemHeight = 95; // Estimated height for each item
        int totalItems = qaList.size();
        int height = totalItems * itemHeight;

        // Adjust the height of the scrollArea based on the calculated height
        scrollArea->setMinimumHeight(height);

        for (const auto &qa : qaList) {
            QString key = QString::fromStdString(qa.first);
            QString value = QString::fromStdString(qa.second);

            QWidget *qaWidget = new QWidget(this);
            QHBoxLayout *qaLayout = new QHBoxLayout(qaWidget);
            qaLayout->setSpacing(2);

            QLabel *keyLabel = new QLabel(key, this);
            keyLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #FFFFFF;");
            keyLabel->setAlignment(Qt::AlignLeft);
            keyLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

            QLabel *valueLabel = new QLabel(value, this);
            valueLabel->setStyleSheet("font-size: 16px; color: #FFFFFF;");
            valueLabel->setAlignment(Qt::AlignLeft);
            valueLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

            // Create a container widget to apply background color
            QWidget *containerWidget = new QWidget(this);
            QHBoxLayout *containerLayout = new QHBoxLayout(containerWidget);
            containerWidget->setStyleSheet(
                    "background-color: #403e3e; "
                    "border-radius: 10px; "
                    "padding: 5px; "
                    "margin: 2px 0;"
            );

            QPushButton *deleteButton = new QPushButton(this);
            deleteButton->setIcon(QIcon("../icons/trash.png"));
            deleteButton->setIconSize(QSize(20, 20)); // Adjust icon size
            deleteButton->setStyleSheet("background-color: transparent; border: none;");
            deleteButton->setFixedSize(30, 30);
            connect(deleteButton, &QPushButton::clicked, [this, setName, key, qaWidget]() {
                deleteKeyValuePair(setName, key);
                qaWidget->deleteLater();
            });

            QPushButton *adjustButton = new QPushButton(this);
            adjustButton->setIcon(QIcon("../icons/pencil.png"));
            adjustButton->setIconSize(QSize(20, 20)); // Adjust icon size
            adjustButton->setStyleSheet("background-color: transparent; border: none;");
            adjustButton->setFixedSize(30, 30);
            connect(adjustButton, &QPushButton::clicked, [this, setName, key, value]() {
                bool ok;
                QString newValue = QInputDialog::getText(this, tr("Adjust Value"),
                                                         tr("New value for %1:").arg(key), QLineEdit::Normal,
                                                         value, &ok);
                if (ok && !newValue.isEmpty()) {
                    adjustKeyValuePair(setName, key, newValue);
                }
            });

            // Add event filters for hover effects
            deleteButton->installEventFilter(this);
            adjustButton->installEventFilter(this);

            containerLayout->addWidget(keyLabel, 1); // First third
            containerLayout->addWidget(valueLabel, 2); // Second third
            containerLayout->addStretch(1);
            containerLayout->addWidget(adjustButton);
            containerLayout->addWidget(deleteButton);
            containerWidget->setLayout(containerLayout);

            qaLayout->addWidget(containerWidget);
            qaWidget->setLayout(qaLayout);

            QListWidgetItem *item = new QListWidgetItem(qaListWidget);
            item->setSizeHint(qaWidget->sizeHint());
            qaListWidget->addItem(item);
            qaListWidget->setItemWidget(item, qaWidget);
        }
    }

    updateSetSize();
}

bool EnterSetPage::eventFilter(QObject *watched, QEvent *event) {
    QPushButton *button = qobject_cast<QPushButton *>(watched);
    if (button) {
        if (event->type() == QEvent::Enter) {
            button->setIconSize(QSize(24, 24));
        } else if (event->type() == QEvent::Leave) {
            button->setIconSize(QSize(20, 20));
        }
    }
    return QWidget::eventFilter(watched, event);
}

void EnterSetPage::clearAllEntries() {
    std::cout << "Clearing all entries" << std::endl;
    qaListWidget->clear();
    updateSetSize();
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

    if (session->deleteStudySet(setName.toStdString())) {
        emit deleteSetClicked(setName);
        auto it = setWidgets.find(setName);
        if (it != setWidgets.end()) {
            it->second->deleteLater();
            setWidgets.erase(it);
        }
    } else {
        msgBox.setText("Failed to delete set.");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }

    updateSetSize();
}

void EnterSetPage::deleteKeyValuePair(const QString &setName, const QString &key) {
    std::cout << "Deleting key-value pair: " << key.toStdString() << " from set: " << setName.toStdString() << std::endl;
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

    if (session->deleteFromStudySet(setName.toStdString(), key.toStdString())) {
        emit deleteKeyValuePairClicked(setName, key);
    } else {
        msgBox.setText("Failed to delete key-value pair.");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }

    updateSetSize();
}

void EnterSetPage::adjustKeyValuePair(const QString &setName, const QString &key, const QString &newValue) {
    std::cout << "Adjusting key-value pair: " << key.toStdString() << " to new value: " << newValue.toStdString() << " in set: " << setName.toStdString() << std::endl;
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

    if (session->deleteFromStudySet(setName.toStdString(), key.toStdString()) &&
        session->addToStudySet(setName.toStdString(), key.toStdString(), newValue.toStdString())) {
        emit adjustKeyValuePairClicked(setName, key, newValue);
        setQAList(setName);  // Refresh the QA list to reflect the changes
    } else {
        msgBox.setText("Failed to adjust key-value pair.");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }

    updateSetSize();
}

void EnterSetPage::showAddQuestionPage() {
    std::cout << "Showing add question page for set: " << currentSetName.toStdString() << std::endl;
    bool ok;

    QInputDialog inputDialog;
    inputDialog.setStyleSheet(
            "QInputDialog {"
            "background-color: #2b2b2b;"
            "color: #ffffff;"
            "font-size: 16px;"
            "}"
            "QLineEdit {"
            "background-color: #454545;"
            "color: #ffffff;"
            "border: 1px solid #5a5a5a;"
            "font-size: 14px;"
            "padding: 5px;"
            "border-radius: 5px;"
            "}"
            "QLabel {"
            "color: #ffffff;"
            "font-size: 16px;"
            "}"
            "QPushButton {"
            "font-size: 14px;"
            "padding: 5px;"
            "border-radius: 5px;"
            "}"
    );

    QString key = inputDialog.getText(this, tr("New Question"),
                                      tr("Enter new question:"), QLineEdit::Normal,
                                      QString(), &ok);

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

    if (!ok || key.isEmpty() || key == "set_names") {
        msgBox.setText("The key is invalid.");
        msgBox.setWindowTitle("Invalid Key");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }

    UserSession *session = UserSession::getUserSession();
    if (session->existsStudySet(currentSetName.toStdString())) {
        auto qaList = session->getTableKeyValues(currentSetName.toStdString());
        for (const auto &qa : qaList) {
            if (QString::fromStdString(qa.first) == key) {
                msgBox.setText("This key already exists in the set.");
                msgBox.setWindowTitle("Duplicate Key");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.exec();
                return;
            }
        }
    }

    QString value = inputDialog.getText(this, tr("New Answer"),
                                        tr("Enter new answer:"), QLineEdit::Normal,
                                        QString(), &ok);
    if (ok && !value.isEmpty()) {
        session->addToStudySet(currentSetName.toStdString(), key.toStdString(), value.toStdString());
        setQAList(currentSetName);  // Refresh the QA list to reflect the changes
    } else {
        msgBox.setText("The value cannot be empty.");
        msgBox.setWindowTitle("Invalid Value");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }

    updateSetSize();
}

void EnterSetPage::setupStudyMethodButtons() {
    auto mcSignal = [this] { emit openMCPageClicked(currentSetName); };
    auto inverseMcSignal = [this] { emit openInverseMCPageClicked(currentSetName); };
    auto flashcardsSignal = [this] { emit openFlashcardsPageClicked(currentSetName); };

    connect(mcButton, &QPushButton::clicked, this, [this, mcSignal] {
        checkSetSizeAndEmitSignal(mcSignal);
    });
    connect(inverseMCButton, &QPushButton::clicked, this, [this, inverseMcSignal] {
        checkSetSizeAndEmitSignal(inverseMcSignal);
    });
    connect(flashcardsButton, &QPushButton::clicked, this, [this, flashcardsSignal] {
        checkSetSizeAndEmitSignal(flashcardsSignal);
    });
}

void EnterSetPage::updateSetSize() {
    UserSession *session = UserSession::getUserSession();
    setSize = session->getStudySetSize(currentSetName.toStdString());
}

void EnterSetPage::checkSetSizeAndEmitSignal(const std::function<void()>& emitSignal) {
    if (setSize == 0) {
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
        msgBox.setText("The set is empty. Please add elements to the set before proceeding.");
        msgBox.setWindowTitle("Empty Set");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    } else {
        emitSignal();
    }
}

void EnterSetPage::openMCPage() {
    emit openMCPageClicked(currentSetName);
}

void EnterSetPage::openInversePage() {
    emit openInverseMCPageClicked(currentSetName);
}

void EnterSetPage::openFlashcardsPage() {
    emit openFlashcardsPageClicked(currentSetName);
}


void EnterSetPage::setShortcuts(Shortcuts *shortcuts) {
    m_shortcuts = shortcuts;
}