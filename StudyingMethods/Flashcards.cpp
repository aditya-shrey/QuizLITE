#include "Flashcards.h"

Flashcards::Flashcards(const std::string& setName) : currentIndex(0), setName(setName) {
    keyValues = UserSessionInfo::getUserSessionInfo()->getTableKeyValues(setName);
}

void Flashcards::startStudying() {
    currentIndex = 0;
    std::cout << "Started studying flashcards." << std::endl;
}

void Flashcards::endStudying() {
    std::cout << "Finished studying flashcards." << std::endl;
}

void Flashcards::displayQuestion() {
    if (currentIndex < keyValues.size()) {
        std::cout << "Question: " << keyValues[currentIndex].first << std::endl;
    } else {
        std::cout << "No more questions." << std::endl;
    }
}

std::string Flashcards::revealAnswer() {
    if (currentIndex < keyValues.size()) {
        std::string answer = keyValues[currentIndex].second;
        std::cout << "Answer: " << answer << std::endl;

        std::string result = "question=" + keyValues[currentIndex].first + "&answer=" + answer;
        return result;
    }
    return "question=&answer=";
}

void Flashcards::goToNextQuestion() {
    if (currentIndex < keyValues.size()) {
        currentIndex++;
    } else {
        std::cout << "End of flashcards." << std::endl;
    }
}
