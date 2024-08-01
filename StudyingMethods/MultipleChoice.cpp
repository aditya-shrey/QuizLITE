#include "MultipleChoice.h"
#include <unordered_set>
#include <random>
#include <algorithm>

// Hash function for std::pair to be used in std::unordered_set
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

MultipleChoice::MultipleChoice(const std::string& setName, int numLowestAccuracies, int numRandomEntries)
        : currentIndex(0)
        , setName(setName)
{
    auto userSession = UserSession::getUserSession();

    std::unordered_set<std::pair<std::string, std::string>, pair_hash> uniqueEntries;

    auto lowestAccuracies = userSession->getLowestAccuracies(setName, numLowestAccuracies);
    for (const auto& entry : lowestAccuracies) {
        uniqueEntries.insert(std::make_pair(std::get<0>(entry), std::get<1>(entry)));
    }

    auto randomEntries = userSession->getRandomEntries(setName, numRandomEntries);
    for (const auto& entry : randomEntries) {
        uniqueEntries.insert(entry);
    }

    keyValues.assign(uniqueEntries.begin(), uniqueEntries.end());

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
    std::random_device rd;
    std::mt19937 gen(rd());

    if (keyValues.size() <= 4) {
        options = keyValues;
    } else {
        std::unordered_set<std::pair<std::string, std::string>, pair_hash> optionSet;
        while (optionSet.size() < 3) {
            std::uniform_int_distribution<> dis(0, keyValues.size() - 1);
            auto sampled = keyValues[dis(gen)];
            if (sampled != keyValues[currentIndex]) {
                optionSet.insert(sampled);
            }
        }
        optionSet.insert(keyValues[currentIndex]); // Ensure the correct answer is one of the options
        options.assign(optionSet.begin(), optionSet.end());
    }

    std::shuffle(options.begin(), options.end(), gen);

    while (options.size() < 4) {
        options.emplace_back("", "");
    }

    return std::make_tuple(options[0].second, options[1].second, options[2].second, options[3].second);
}

void MultipleChoice::updateScoresInTable(bool isCorrect)
{
    if (currentIndex < keyValues.size()) {
        UserSession::getUserSession()->updateScore(setName, keyValues[currentIndex].first, isCorrect);
    }
}
