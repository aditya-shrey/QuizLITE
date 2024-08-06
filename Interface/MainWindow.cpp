#include "MainWindow.h"
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        pageStack(new QStackedWidget(this)),
        libraryPage(new LibraryPage(this)),
        createSetPage(new CreateSetPage(this)),
        addQuestionsPage(new AddQuestionsPage(this)),
        enterSetPage(new EnterSetPage(this)),
        mcPage(new MCPage(this)),
        inverseMCPage(new InverseMCPage(this)),
        flashcardPage(new FlashcardPage(this)),
        shortcuts(new Shortcuts(this, enterSetPage)) {

    this->setStyleSheet("background-color: #222222;");

    pageStack->addWidget(libraryPage);
    pageStack->addWidget(createSetPage);
    pageStack->addWidget(addQuestionsPage);
    pageStack->addWidget(enterSetPage);
    pageStack->addWidget(mcPage);
    pageStack->addWidget(inverseMCPage);
    pageStack->addWidget(flashcardPage);
    setCentralWidget(pageStack);

    connectSignalsAndSlots();

    pageStack->setCurrentWidget(libraryPage);
    libraryPage->populateLibrary();

    createMenus();
    updateMenus();
}

void MainWindow::connectSignalsAndSlots() {
    connect(libraryPage, &LibraryPage::createSetClicked, this, &MainWindow::showCreateSetPage);
    connect(createSetPage, &CreateSetPage::setNameConfirmed, this, &MainWindow::showAddQuestionsPage);
    connect(addQuestionsPage, &AddQuestionsPage::addToSetClicked, this, &MainWindow::addToSet);
    connect(addQuestionsPage, &AddQuestionsPage::finishedClicked, this, &MainWindow::finishSet);
    connect(enterSetPage, &EnterSetPage::openSetClicked, this, &MainWindow::openSet);
    connect(libraryPage, &LibraryPage::openSetClicked, this, &MainWindow::openSet);
    connect(enterSetPage, &EnterSetPage::backToLibraryClicked, this, &MainWindow::showLibraryPage);
    connect(createSetPage, &CreateSetPage::backToLibraryClicked, this, &MainWindow::showLibraryPage);
    connect(addQuestionsPage, &AddQuestionsPage::backToLibraryClicked, this, &MainWindow::showLibraryPage);
    connect(enterSetPage, &EnterSetPage::confirmDeleteSet, this, &MainWindow::handleDeleteSet);


    //
    connect(enterSetPage, &EnterSetPage::openSetClicked, shortcuts, &Shortcuts::setCurrentSetName);

    connect(enterSetPage, &EnterSetPage::openMCPageClicked, this, &MainWindow::showMCPage);
    connect(enterSetPage, &EnterSetPage::openInverseMCPageClicked, this, &MainWindow::showInverseMCPage);
    connect(enterSetPage, &EnterSetPage::openFlashcardsPageClicked, this, &MainWindow::showFlashcardPage);

    connect(mcPage, &MCPage::backToSetClicked, this, &MainWindow::showEnterSetPage);
    connect(inverseMCPage, &InverseMCPage::backToSetClicked, this, &MainWindow::showEnterSetPage);
    connect(flashcardPage, &FlashcardPage::backToSetClicked, this, &MainWindow::showEnterSetPage);

    connect(pageStack, &QStackedWidget::currentChanged, this, &MainWindow::updateMenus);
}

void MainWindow::createMenus() {
    QMenu *setMenu = menuBar()->addMenu(tr("&Set"));
    setMenu->addAction(tr("&New Set"),QKeySequence::New, this, &MainWindow::showCreateSetPage);

    QMenu *studyMenu = menuBar()->addMenu(tr("&Study"));
//    studyMenu->addAction(tr("&Multiple Choice"),Qt::Key_M, this, &EnterSetPage::openMCPage);
    studyMenu->addAction(tr("&Inverse Multiple Choice"), QKeySequence(Qt::Key_I), this, [this](){ showInverseMCPage(shortcuts->currentSetName());});
    studyMenu->addAction(tr("&Flashcards"), QKeySequence(Qt::Key_F),this, [this](){ showFlashcardPage(shortcuts->currentSetName()); });
}

void MainWindow::updateMenus() {
    QWidget *currentWidget = pageStack->currentWidget();
    bool isLibraryPage = (currentWidget == libraryPage);
    bool isEnterSetPage = (currentWidget == enterSetPage);

    menuBar()->actions().at(0)->menu()->actions().at(0)->setEnabled(isLibraryPage);
    menuBar()->actions().at(1)->menu()->setEnabled(isEnterSetPage);
}

void MainWindow::showCreateSetPage() {
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
    if (session->existsStudySet(setName.toStdString())) {
        enterSetPage->setSetName(setName);
        enterSetPage->setQAList(setName);
        pageStack->setCurrentWidget(enterSetPage);
    } else {
        QMessageBox::warning(this, "Set Not Found", "The selected study set does not exist.");
    }
}

void MainWindow::finishSet() {
    UserSession *session = UserSession::getUserSession();
    session->createStudySet(currentSetName.toStdString());

    for (const auto &qa : currentSetQA) {
        session->addToStudySet(currentSetName.toStdString(), qa.first.toStdString(), qa.second.toStdString());
    }
    libraryPage->addSetButton(currentSetName);
    currentSetName.clear();
    currentSetQA.clear();
    showLibraryPage();
}

void MainWindow::showLibraryPage() {
    libraryPage->populateLibrary();
    pageStack->setCurrentWidget(libraryPage);
}

void MainWindow::handleDeleteSet(const QString &setName) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Delete Set");
    msgBox.setText("Are you sure you want to delete this set?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setStyleSheet("QMessageBox { background-color: #2b2b2b; color: #ffffff; font-size: 16px; }");

    if (msgBox.exec() == QMessageBox::Yes) {
        enterSetPage->deleteSet(setName);
        showLibraryPage();
    }
}

void MainWindow::showMCPage(const QString &setName) {
    if (!setName.isEmpty()) {
        mcPage->resetQuiz();
        mcPage->startMCQuiz(setName);
        pageStack->setCurrentWidget(mcPage);
    }
}

void MainWindow::showInverseMCPage(const QString &setName) {
    if (!setName.isEmpty()) {
        inverseMCPage->resetQuiz();
        inverseMCPage->startInverseMCQuiz(setName);
        pageStack->setCurrentWidget(inverseMCPage);
    }
}

void MainWindow::showFlashcardPage(const QString &setName) {
    if (!setName.isEmpty()) {
        flashcardPage->startFlashcardQuiz(setName);
        pageStack->setCurrentWidget(flashcardPage);
    }
}

void MainWindow::showEnterSetPage() {
    pageStack->setCurrentWidget(enterSetPage);
    enterSetPage->setQAList(enterSetPage->getCurrentSetName());
}