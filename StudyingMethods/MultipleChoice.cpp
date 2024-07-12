#include "MultipleChoice.h"

MultipleChoice::MultipleChoice(const std::string& setName, int numLowestAccuracies, int numRandomEntries)
    : currentIndex(0)
    , setName(setName)
{
    auto userSession = UserSessionInfo::getUserSessionInfo();

    auto lowestAccuracies = userSession->getLowestAccuracies(setName, numLowestAccuracies);
    for (const auto& entry : lowestAccuracies) {
        keyValues.emplace_back(std::get<0>(entry), std::get<1>(entry));
    }

    auto randomEntries = userSession->getRandomEntries(setName, numRandomEntries);
    keyValues.insert(keyValues.end(), randomEntries.begin(), randomEntries.end());

    std::shuffle(keyValues.begin(), keyValues.end(), std::mt19937 { std::random_device {}() });
}

std::string MultipleChoice::getQuestion()
{
    if (currentIndex < keyValues.size()) {
        return keyValues[currentIndex].first;
    }
    return "";
}

std::string MultipleChoice::getAnswer()
{
    if (currentIndex < keyValues.size()) {
        return keyValues[currentIndex].second;
    }
    return "";
}

bool MultipleChoice::goToNextQuestion()
{
    if (currentIndex + 1 < keyValues.size()) {
        ++currentIndex;
        return true;
    }
    return false;
}

std::tuple<std::string, std::string, std::string, std::string> MultipleChoice::generateOptions()
{
    std::vector<std::pair<std::string, std::string>> options;
    std::sample(keyValues.begin(), keyValues.end(), std::back_inserter(options),
        4, std::mt19937 { std::random_device {}() });
    if (std::find(options.begin(), options.end(), keyValues[currentIndex]) == options.end()) {
        options[0] = keyValues[currentIndex]; // Ensure the correct answer is one of the options
    }
    std::shuffle(options.begin(), options.end(), std::mt19937 { std::random_device {}() });

    return std::make_tuple(options[0].second, options[1].second, options[2].second, options[3].second);
}

void MultipleChoice::updateScoresInTable(bool isCorrect)
{
    if (currentIndex < keyValues.size()) {
        UserSessionInfo::getUserSessionInfo()->updateScore(setName, keyValues[currentIndex].first, isCorrect);
    }
}
