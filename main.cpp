#include <iostream>
#include <thread>
#include <chrono>
#include "User/UserSession.h"
#include "StudyingMethods/Flashcards.h"
#include "StudyingMethods/MultipleChoice.h"
#include "StudyingMethods/InverseMultipleChoice.h"


//Interface
#include "Interface/MainWindow.h"
#include <QApplication>
#include <QPushButton>

void populateDatabase() {
    auto userSession = UserSession::getUserSession();

    // Create study sets
    userSession->createStudySet("Math");
    userSession->createStudySet("Science");

    // Add entries to "Math" set
    userSession->addToStudySet("Math", "2+2", "4");
    userSession->addToStudySet("Math", "3*3", "9");
    userSession->addToStudySet("Math", "sqrt(16)", "4");

    // Add entries to "Science" set
    userSession->addToStudySet("Science", "H2O", "Water");
    userSession->addToStudySet("Science", "CO2", "Carbon Dioxide");
    userSession->addToStudySet("Science", "NaCl", "Salt");
}

void interactiveFlashcards() {
    std::string setName;
    std::cout << "Enter the name of the study set for Flashcards: ";
    std::cin >> setName;

    Flashcards flashcards(setName);
    std::cout << "Flashcards for " << setName << ":" << std::endl;

    std::string question = flashcards.getQuestion();
    while (!question.empty()) {
        std::cout << "Q: " << question << std::endl;
        std::string answer;
        std::cout << "Your answer: ";
        std::cin >> answer;
        std::cout << "Correct answer: " << flashcards.getAnswer() << std::endl;
        flashcards.goToNextQuestion();
        question = flashcards.getQuestion();
    }
}

void interactiveMultipleChoice() {
    std::string setName;
    int numLowestAccuracies, numRandomEntries;
    std::cout << "Enter the name of the study set for Multiple Choice: ";
    std::cin >> setName;
    std::cout << "Enter the number of lowest accuracy entries to include: ";
    std::cin >> numLowestAccuracies;
    std::cout << "Enter the number of random entries to include: ";
    std::cin >> numRandomEntries;

    MultipleChoice multipleChoice(setName, numLowestAccuracies, numRandomEntries);
    std::cout << "Multiple Choice for " << setName << ":" << std::endl;

    std::string question = multipleChoice.getQuestion();
    while (!question.empty()) {
        std::cout << "Q: " << question << std::endl;
        auto options = multipleChoice.generateOptions();
        std::cout << "Options: " << std::endl;
        std::cout << "1: " << std::get<0>(options) << std::endl;
        std::cout << "2: " << std::get<1>(options) << std::endl;
        std::cout << "3: " << std::get<2>(options) << std::endl;
        std::cout << "4: " << std::get<3>(options) << std::endl;

        int choice;
        std::cout << "Your choice (1-4): ";
        std::cin >> choice;

        bool isCorrect = (choice == 1 && std::get<0>(options) == multipleChoice.getAnswer()) ||
                         (choice == 2 && std::get<1>(options) == multipleChoice.getAnswer()) ||
                         (choice == 3 && std::get<2>(options) == multipleChoice.getAnswer()) ||
                         (choice == 4 && std::get<3>(options) == multipleChoice.getAnswer());

        multipleChoice.updateScoresInTable(isCorrect);
        std::cout << (isCorrect ? "Correct!" : "Wrong!") << std::endl;

        multipleChoice.goToNextQuestion();
        question = multipleChoice.getQuestion();
    }
}

void interactiveInverseMultipleChoice() {
    std::string setName;
    int numLowestAccuracies, numRandomEntries;
    std::cout << "Enter the name of the study set for Inverse Multiple Choice: ";
    std::cin >> setName;
    std::cout << "Enter the number of lowest accuracy entries to include: ";
    std::cin >> numLowestAccuracies;
    std::cout << "Enter the number of random entries to include: ";
    std::cin >> numRandomEntries;

    InverseMultipleChoice inverseMultipleChoice(setName, numLowestAccuracies, numRandomEntries);
    std::cout << "Inverse Multiple Choice for " << setName << ":" << std::endl;

    std::string question = inverseMultipleChoice.getQuestion();
    while (!question.empty()) {
        std::cout << "Q: " << question << std::endl;
        auto options = inverseMultipleChoice.generateOptions();
        std::cout << "Options: " << std::endl;
        std::cout << "1: " << std::get<0>(options) << std::endl;
        std::cout << "2: " << std::get<1>(options) << std::endl;
        std::cout << "3: " << std::get<2>(options) << std::endl;
        std::cout << "4: " << std::get<3>(options) << std::endl;

        int choice;
        std::cout << "Your choice (1-4): ";
        std::cin >> choice;

        bool isCorrect = (choice == 1 && std::get<0>(options) == inverseMultipleChoice.getAnswer()) ||
                         (choice == 2 && std::get<1>(options) == inverseMultipleChoice.getAnswer()) ||
                         (choice == 3 && std::get<2>(options) == inverseMultipleChoice.getAnswer()) ||
                         (choice == 4 && std::get<3>(options) == inverseMultipleChoice.getAnswer());

        inverseMultipleChoice.updateScoresInTable(isCorrect);
        std::cout << (isCorrect ? "Correct!" : "Wrong!") << std::endl;

        inverseMultipleChoice.goToNextQuestion();
        question = inverseMultipleChoice.getQuestion();
    }
}

int main(int argc, char **argv) {
    populateDatabase();

    int choice;
    do {
        std::cout << "Choose an option:" << std::endl;
        std::cout << "1. Flashcards" << std::endl;
        std::cout << "2. Multiple Choice" << std::endl;
        std::cout << "3. Inverse Multiple Choice" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cin >> choice;

        switch (choice) {
            case 1:
                interactiveFlashcards();
                break;
            case 2:
                interactiveMultipleChoice();
                break;
            case 3:
                interactiveInverseMultipleChoice();
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);


    // SELECT 4 to exit studying methods CLI to enter application
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
//    QWidget *wdg = new QWidget;
//    wdg->show();
//    window.close();//this will disappear main window4
//
//    wdg->close(); window.show();

    return app.exec();
}
