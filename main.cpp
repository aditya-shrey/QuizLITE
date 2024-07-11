#include <iostream>
#include <thread>
#include <chrono>
#include "User/UserSessionInfo.h"
#include "StudyingMethods/Flashcards.h"
#include "StudyingMethods/MultipleChoice.h"
#include "StudyingMethods/InverseMultipleChoice.h"



void populateDatabase() {
    UserSessionInfo* session = UserSessionInfo::getUserSessionInfo();
    std::string setName = "AnimalQuiz";

    if (!session->existsStudySet(setName)) {
        if (session->createStudySet(setName)) {
            std::cout << "Study set " << setName << " created." << std::endl;

            session->addToStudySet(setName, "What is the largest land animal?", "Elephant");
            session->addToStudySet(setName, "What is the fastest land animal?", "Cheetah");
            session->addToStudySet(setName, "What is the tallest animal?", "Giraffe");
            session->addToStudySet(setName, "What animal is known as the King of the Jungle?", "Lion");
            session->addToStudySet(setName, "What is the largest marine mammal?", "Blue Whale");

            std::cout << "Study set " << setName << " populated with quiz data." << std::endl;
        } else {
            std::cerr << "Failed to create study set " << setName << "." << std::endl;
        }
    } else {
        std::cout << "Study set " << setName << " already exists." << std::endl;
    }
}

void studyWithFlashcards() {
    std::string setName = "AnimalQuiz";
    Flashcards flashcards(setName);

    flashcards.startStudying();

    while (true) {
        flashcards.displayQuestion();

        std::cout << "Press Enter to reveal the answer or 'q' to quit...";
        std::string input;
        std::getline(std::cin, input);
        if (input == "q") {
            break;
        }

        std::string answerFormat = flashcards.revealAnswer();
//        std::cout << "Answer in key-value format: " << answerFormat << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));

        flashcards.goToNextQuestion();

        if (flashcards.revealAnswer() == "question=&answer=") {
            std::cout << "End of flashcards." << std::endl;
            break;
        }
    }

    flashcards.endStudying();
}

void studyWithMultipleChoice() {
    std::string setName = "AnimalQuiz";
    MultipleChoice multipleChoice(setName);

    multipleChoice.startStudying();

    while (true) {
        multipleChoice.displayQuestion();

        std::cout << "Press Enter to reveal the answer or 'q' to quit...";
        std::string input;
        std::getline(std::cin, input);
        if (input == "q") {
            break;
        }

        std::string answerFormat = multipleChoice.revealAnswer();
//        std::cout << "Answer in key-value format: " << answerFormat << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));

        multipleChoice.goToNextQuestion();

        if (multipleChoice.revealAnswer() == "question=&correctAnswer=") {
            std::cout << "End of multiple choice questions." << std::endl;
            break;
        }
    }

    multipleChoice.endStudying();
}

void studyWithInverseMultipleChoice() {
    std::string setName = "AnimalQuiz";
    InverseMultipleChoice inverseMultipleChoice(setName);

    inverseMultipleChoice.startStudying();

    while (true) {
        inverseMultipleChoice.displayQuestion();

        std::cout << "Press Enter to reveal the answer or 'q' to quit...";
        std::string input;
        std::getline(std::cin, input);
        if (input == "q") {
            break;
        }

        std::string answerFormat = inverseMultipleChoice.revealAnswer();
//        std::cout << "Answer in key-value format: " << answerFormat << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));

        inverseMultipleChoice.goToNextQuestion();

        if (inverseMultipleChoice.revealAnswer() == "option=&correctQuestion=") {
            std::cout << "End of inverse multiple choice questions." << std::endl;
            break;
        }
    }

    inverseMultipleChoice.endStudying();
}

int main() {
    populateDatabase();

    std::cout << "Choose a study method:\n";
    std::cout << "1. Flashcards\n";
    std::cout << "2. Multiple Choice\n";
    std::cout << "3. Inverse Multiple Choice\n";
    std::cout << "Enter the number of your choice: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(); // Ignore the newline character left in the input buffer

    switch (choice) {
        case 1:
            studyWithFlashcards();
            break;
        case 2:
            studyWithMultipleChoice();
            break;
        case 3:
            studyWithInverseMultipleChoice();
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
    }

    return 0;
}
