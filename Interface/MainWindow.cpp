//
// Created by Fardeen Bablu on 7/13/24.
//

#include "MainWindow.h"
#include "../User/UserSession.h"


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

    //Connect pages and buttons that have been clicked, then set current page to library
    connect(libraryPage, &LibraryPage::createSetClicked, this,
            &MainWindow::showCreatePageSet);
    connect(createSetPage, &CreateSetPage::setNameConfirmed, this,
            &MainWindow::showAddQuestionsPage);
    connect(addQuestionsPage, &AddQuestionsPage::addToSetClicked, this,
            &MainWindow::addToSet);
    connect(addQuestionsPage, &AddQuestionsPage::finishedClicked, this,
            &MainWindow::finishSet);
    connect(enterSetPage, &EnterSetPage::openSetClicked, this, &MainWindow::openSet);
    connect(libraryPage, &LibraryPage::openSetClicked, this, &MainWindow::openSet);
//    connect(enterSetPage, &EnterSetPage::backClicked, this, &MainWindow::goBackToLibrary);

    pageStack->setCurrentWidget(libraryPage);
}


void MainWindow::showCreatePageSet() {
    pageStack->setCurrentWidget(createSetPage);
}

void MainWindow::showAddQuestionsPage(const QString &setName) {
    currentSetName = setName;
    currentSetQA.clear();
    pageStack->setCurrentWidget(addQuestionsPage);
}

void MainWindow::addToSet(const QString &question, const QString &answer) {
    currentSetQA.append(qMakePair(question, answer));
}


void MainWindow::openSet(const QString &setName) {
    UserSession *session = UserSession::getUserSession();
    auto qaList = session->getTableKeyValues(setName.toStdString());

    QList<QPair<QString, QString>> qaPairList;
    for (const auto &qa : qaList) {
        qaPairList.append(qMakePair(QString::fromStdString(qa.first), QString::fromStdString(qa.second)));
    }

    enterSetPage->setSetName(setName);
    enterSetPage->setQAList(qaPairList);
    pageStack->setCurrentWidget(enterSetPage);
}

void MainWindow::finishSet() {
    UserSession *session = UserSession::getUserSession();
    session->createStudySet(currentSetName.toStdString());

    //auto here is the vector<pair<string1, string2>>
    // Go through the qaWidgetList and add it to userSession
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
}
