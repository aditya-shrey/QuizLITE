#include "MultipleChoice.h"

MultipleChoice::MultipleChoice(const std::string& setName)
    : currentIndex(0)
    , setName(setName)
{
    keyValues = UserSessionInfo::getUserSessionInfo()->getTableKeyValues(setName);
}

void MultipleChoice::startStudying()
{
    currentIndex = 0;
    std::cout << "Started studying multiple choice." << std::endl;
}

void MultipleChoice::endStudying()
{
    std::cout << "Finished studying multiple choice." << std::endl;
}

void MultipleChoice::generateOptions()
{
    options.clear();
    std::sample(keyValues.begin(), keyValues.end(), std::back_inserter(options),
        4, std::mt19937 { std::random_device {}() });
    if (std::find(options.begin(), options.end(), keyValues[currentIndex]) == options.end()) {
        options[0] = keyValues[currentIndex]; // Ensure the correct answer is one of the options
    }
    std::shuffle(options.begin(), options.end(), std::mt19937 { std::random_device {}() });
}

void MultipleChoice::displayQuestion()
{
    if (currentIndex < keyValues.size()) {
        generateOptions();
        std::cout << "Question: " << keyValues[currentIndex].first << std::endl;
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << "Option " << i + 1 << ": " << options[i].second << std::endl;
        }
    } else {
        std::cout << "No more questions." << std::endl;
    }
}

std::string MultipleChoice::revealAnswer()
{
    if (currentIndex < keyValues.size()) {
        std::string correctAnswer = keyValues[currentIndex].second;

        std::cout << "Enter the number of the correct option: ";
        int userAnswer;
        std::cin >> userAnswer;

        bool isCorrect = (options[userAnswer - 1].second == correctAnswer);
        if (isCorrect) {
            std::cout << "Correct!" << std::endl;
        } else {
            std::cout << "Incorrect. The correct answer is: " << correctAnswer << std::endl;
        }

        updateScoresInTable(isCorrect);

        std::string result = "question=" + keyValues[currentIndex].first + "&correctAnswer=" + correctAnswer;
        return result;
    }
    return "question=&correctAnswer=";
}

void MultipleChoice::goToNextQuestion()
{
    if (currentIndex < keyValues.size()) {
        currentIndex++;
    } else {
        std::cout << "End of multiple choice questions." << std::endl;
    }
}

void MultipleChoice::updateScoresInTable(bool isCorrect)
{
    if (currentIndex < keyValues.size()) {
        UserSessionInfo::getUserSessionInfo()->updateScore(setName, keyValues[currentIndex].first, isCorrect);
    }
}
