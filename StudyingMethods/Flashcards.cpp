#include "Flashcards.h"

Flashcards::Flashcards(const std::string& setName)
    : currentIndex(0)
    , setName(setName)
{
    keyValues = UserSession::getUserSession()->getTableKeyValues(setName);
}

std::string Flashcards::getQuestion()
{
    if (currentIndex < keyValues.size()) {
        return keyValues[currentIndex].first;
    }
    return "";
}

std::string Flashcards::getAnswer()
{
    if (currentIndex < keyValues.size()) {
        return keyValues[currentIndex].second;
    }
    return "";
}

bool Flashcards::goToNextQuestion()
{
    if (currentIndex + 1 < keyValues.size()) {
        ++currentIndex;
        return true;
    }
    return false;
}

bool Flashcards::goToPrevQuestion()
{
    if (currentIndex >= 1) {
        --currentIndex;
        return true;
    }
    return false;
}

void Flashcards::resetIndex() {
    currentIndex = 0;
}

void Flashcards::setToLastIndex() {
    currentIndex = keyValues.size() - 1;
}