#include "InverseMultipleChoice.h"

InverseMultipleChoice::InverseMultipleChoice(const std::string& setName) : currentIndex(0), setName(setName) {
    keyValues = UserSessionInfo::getUserSessionInfo()->getTableKeyValues(setName);
}

void InverseMultipleChoice::startStudying() {
    currentIndex = 0;
    std::cout << "Started studying inverse multiple choice." << std::endl;
}

void InverseMultipleChoice::endStudying() {
    std::cout << "Finished studying inverse multiple choice." << std::endl;
}

void InverseMultipleChoice::generateOptions() {
    options.clear();
    std::sample(keyValues.begin(), keyValues.end(), std::back_inserter(options),
                4, std::mt19937{std::random_device{}()});
    if (std::find(options.begin(), options.end(), keyValues[currentIndex]) == options.end()) {
        options[0] = keyValues[currentIndex]; // Ensure the correct answer is one of the options
    }
    std::shuffle(options.begin(), options.end(), std::mt19937{std::random_device{}()});
}

void InverseMultipleChoice::displayQuestion() {
    if (currentIndex < keyValues.size()) {
        generateOptions();
        std::cout << "Option: " << keyValues[currentIndex].second << std::endl;
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << "Question " << i + 1 << ": " << options[i].first << std::endl;
        }
    } else {
        std::cout << "No more questions." << std::endl;
    }
}

std::string InverseMultipleChoice::revealAnswer() {
    if (currentIndex < keyValues.size()) {
        std::string correctQuestion = keyValues[currentIndex].first;

        std::cout << "Enter the number of the correct question: ";
        int userAnswer;
        std::cin >> userAnswer;

        bool isCorrect = (options[userAnswer - 1].first == correctQuestion);
        if (isCorrect) {
            std::cout << "Correct!" << std::endl;
        } else {
            std::cout << "Incorrect. The correct question is: " << correctQuestion << std::endl;
        }

        updateScoresInTable(isCorrect);

        std::string result = "option=" + keyValues[currentIndex].second + "&correctQuestion=" + correctQuestion;
        return result;
    }
    return "option=&correctQuestion=";
}

void InverseMultipleChoice::goToNextQuestion() {
    if (currentIndex < keyValues.size()) {
        currentIndex++;
    } else {
        std::cout << "End of inverse multiple choice questions." << std::endl;
    }
}

void InverseMultipleChoice::updateScoresInTable(bool isCorrect) {
    if (currentIndex < keyValues.size()) {
        UserSessionInfo::getUserSessionInfo()->updateScore(setName, keyValues[currentIndex].first, isCorrect);
    }
}
