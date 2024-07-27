#include "LibraryPage.h"
#include "../User/UserSession.h"
#include <QWidgetItem>
#include <QResizeEvent>
#include <QPushButton>
#include <algorithm> // for std::as_const

LibraryPage::LibraryPage(QWidget *parent) :
        QWidget(parent),
        ui(new QVBoxLayout(this)),
        pageLabel(new QLabel("QuizLITE", this)),
        createSetButton(new QPushButton("+ Create Set", this)),
        yourSetsLabel(new QLabel("Your Sets", this)),
        setButtonsLayout(new QGridLayout()) // Grid layout for set buttons
{
    // Set stylesheets for the widgets
    pageLabel->setStyleSheet("color: #5DF779; font-size: 30px; font-weight: bold;");
    createSetButton->setStyleSheet(
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
    yourSetsLabel->setStyleSheet("color: #FFFFFF; font-size: 20px; font-weight: normal; padding: 10px");

    // Create a horizontal layout for the top row
    QHBoxLayout *topRowLayout = new QHBoxLayout();
    topRowLayout->addWidget(pageLabel, 0, Qt::AlignLeft | Qt::AlignTop);
    topRowLayout->addStretch(1);
    topRowLayout->addWidget(createSetButton, 0, Qt::AlignRight | Qt::AlignTop);

    // Create a vertical layout to stack the rows
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(0); // No spacing between elements
    mainLayout->addLayout(topRowLayout);
    mainLayout->addWidget(yourSetsLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->addLayout(setButtonsLayout); // Add the grid layout for set buttons
    mainLayout->addStretch(1); // Add a stretch at the bottom to push everything upwards

    // Set the layout to the main UI
    ui->addLayout(mainLayout);

    // Set the spacing for the set buttons layout
    setButtonsLayout->setHorizontalSpacing(20); // Set horizontal spacing between buttons
    setButtonsLayout->setVerticalSpacing(20); // Set vertical spacing between buttons
    setButtonsLayout->setContentsMargins(10, 10, 10, 10); // Optional: Set margins for the layout

    // Connecting createSetButton signal to the createSetClicked slot
    connect(createSetButton, &QPushButton::clicked, this, &LibraryPage::createSetClicked);

    setLayout(ui);
}

void LibraryPage::addSetButton(const QString &setName) {
    QPushButton *setButton = new QPushButton(setName, this);
    setButton->setStyleSheet(
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
    connect(setButton, &QPushButton::clicked, [this, setName]() {
        emit openSetClicked(setName);
    });
    setButtons.append(setButton); // Store the button in a list for layout management
    updateSetButtonsLayout();
}

void LibraryPage::populateLibrary() {
    UserSession *session = UserSession::getUserSession();

    // Clear existing widgets in the grid layout
    QLayoutItem *item;
    while ((item = setButtonsLayout->takeAt(0)) != nullptr) {
        delete item->widget();  // Delete the widget
        delete item;  // Delete the layout item
    }
    setButtons.clear(); // Clear the list of buttons

    auto setNamesTable = session->getMainTable();
    for (const auto &row : setNamesTable) {
        QString setName = QString::fromStdString(row.at("name"));
        addSetButton(setName);
    }
}

void LibraryPage::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updateSetButtonsLayout(); // Update layout on resize
}

void LibraryPage::updateSetButtonsLayout() {
    int maxColumns = 4;
    int columnCount = qMin(maxColumns, width() / 200);

    int row = 0;
    int column = 0;
    for (QPushButton *button : std::as_const(setButtons)) {
        setButtonsLayout->addWidget(button, row, column);
        column++;
        if (column >= columnCount) {
            column = 0;
            row++;
        }
    }
}
