#include "LibraryPage.h"
#include "../User/UserSession.h"
#include <QWidgetItem>

LibraryPage::LibraryPage(QWidget *parent) :
        QWidget(parent),
        ui(new QVBoxLayout(this)),
        pageLabel(new QLabel("Your Library", this)),
        createSetButton(new QPushButton("+ Create Set", this)) {

    // Adding components to the UI
    ui->addWidget(pageLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    ui->addWidget(createSetButton, 0, Qt::AlignTop | Qt::AlignHCenter);

    // Connecting createSetButton signal to the createSetClicked slot
    connect(createSetButton, &QPushButton::clicked, this, &LibraryPage::createSetClicked);
    setLayout(ui);
}

void LibraryPage::addSetButton(const QString &setName) {
    QPushButton *setButton = new QPushButton(setName, this);
    connect(setButton, &QPushButton::clicked, [this, setName]() {
        emit openSetClicked(setName);
    });
    ui->addWidget(setButton);
}

void LibraryPage::populateLibrary() {
    UserSession *session = UserSession::getUserSession();

    // Clear existing widgets except for the first two (pageLabel and createSetButton)
    QLayoutItem *item;
    while ((item = ui->takeAt(2)) != nullptr) {
        delete item->widget();  // Delete the widget
        delete item;  // Delete the layout item
    }

    auto setNamesTable = session->getMainTable();
    for (const auto &row : setNamesTable) {
        QString setName = QString::fromStdString(row.at("name"));
        addSetButton(setName);
    }
}
