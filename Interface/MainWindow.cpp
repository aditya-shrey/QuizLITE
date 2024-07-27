#include "MainWindow.h"
#include <QMessageBox>
#include "../User/UserSession.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        pageStack(new QStackedWidget(this)),
        libraryPage(new LibraryPage(this)),
        createSetPage(new CreateSetPage(this)),
        addQuestionsPage(new AddQuestionsPage(this)),
        enterSetPage(new EnterSetPage(this)) {

    // Add pages onto pageStack
    pageStack->addWidget(libraryPage);
    pageStack->addWidget(createSetPage);
    pageStack->addWidget(addQuestionsPage);
    pageStack->addWidget(enterSetPage);
    setCentralWidget(pageStack);

    // Connect pages and buttons that have been clicked, then set current page to library
    connect(libraryPage, &LibraryPage::createSetClicked, this, &MainWindow::showCreatePageSet);
    connect(createSetPage, &CreateSetPage::setNameConfirmed, this, &MainWindow::showAddQuestionsPage);
    connect(addQuestionsPage, &AddQuestionsPage::addToSetClicked, this, &MainWindow::addToSet);
    connect(addQuestionsPage, &AddQuestionsPage::finishedClicked, this, &MainWindow::finishSet);
    connect(enterSetPage, &EnterSetPage::openSetClicked, this, &MainWindow::openSet);
    connect(libraryPage, &LibraryPage::openSetClicked, this, &MainWindow::openSet);
    connect(enterSetPage, &EnterSetPage::backToLibraryClicked, this, &MainWindow::showLibraryPage);
    connect(createSetPage, &CreateSetPage::backToLibraryClicked, this, &MainWindow::showLibraryPage);
    connect(addQuestionsPage, &AddQuestionsPage::backToLibraryClicked, this, &MainWindow::showLibraryPage);

    connect(enterSetPage, &EnterSetPage::confirmDeleteSet, this, &MainWindow::handleDeleteSet);

    pageStack->setCurrentWidget(libraryPage);
    libraryPage->populateLibrary(); // Populate library initially
}

void MainWindow::showCreatePageSet() {
    std::cout << "Showing create set page" << std::endl;
    pageStack->setCurrentWidget(createSetPage);
}

void MainWindow::showAddQuestionsPage(const QString &setName) {
    std::cout << "Showing add questions page for set: " << setName.toStdString() << std::endl;
    currentSetName = setName;
    currentSetQA.clear();
    pageStack->setCurrentWidget(addQuestionsPage);
}

void MainWindow::addToSet(const QString &question, const QString &answer) {
    std::cout << "Adding to set: " << currentSetName.toStdString() << " - Q: " << question.toStdString() << " A: " << answer.toStdString() << std::endl;
    currentSetQA.append(qMakePair(question, answer));
}

void MainWindow::openSet(const QString &setName) {
    std::cout << "Opening set: " << setName.toStdString() << std::endl;
    UserSession *session = UserSession::getUserSession();

    if (session->existsStudySet(setName.toStdString())) {
        enterSetPage->setSetName(setName);
        enterSetPage->setQAList(setName);
        pageStack->setCurrentWidget(enterSetPage);
    } else {
        QMessageBox::warning(this, "Set Not Found", "The selected study set does not exist.");
    }
}

void MainWindow::finishSet() {
    std::cout << "Finishing set: " << currentSetName.toStdString() << std::endl;
    UserSession *session = UserSession::getUserSession();
    session->createStudySet(currentSetName.toStdString());

    for (const auto &qa : currentSetQA) {
        session->addToStudySet(currentSetName.toStdString(), qa.first.toStdString(), qa.second.toStdString());
    }
    QListWidget *qaListWidget = new QListWidget();
    for (const auto &qa : currentSetQA) {
        QListWidgetItem *item = new QListWidgetItem("Q: " + qa.first + " - A: " + qa.second);
        qaListWidget->addItem(item);
    }
    setWidgets.insert(currentSetName, qaListWidget);
    libraryPage->addSetButton(currentSetName);
    currentSetName.clear();
    currentSetQA.clear();
    pageStack->setCurrentWidget(libraryPage);
    libraryPage->populateLibrary(); // Refresh the library page
}

void MainWindow::showLibraryPage() {
    std::cout << "Showing library page" << std::endl;
    libraryPage->populateLibrary(); // Refresh the library page each time it's shown
    pageStack->setCurrentWidget(libraryPage);
}

void MainWindow::handleDeleteSet(const QString &setName) {
    std::cout << "Handling delete set: " << setName.toStdString() << std::endl;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Set", "Are you sure you want to delete this set?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        enterSetPage->deleteSet(setName);
        showLibraryPage();
    }
}
