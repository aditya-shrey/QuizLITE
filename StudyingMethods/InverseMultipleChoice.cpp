#include "InverseMultipleChoice.h"
#include <unordered_set>
#include <random>
#include <algorithm>
#include <iostream>

// Hash function for std::pair to be used in std::unordered_set
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

InverseMultipleChoice::InverseMultipleChoice(const std::string& setName, int numLowestAccuracies, int numRandomEntries)
        : currentIndex(0)
        , setName(setName)
        , setSize(0)
{
    auto userSession = UserSession::getUserSession();

    setSize = userSession->getStudySetSize(setName);

    std::unordered_set<std::pair<std::string, std::string>, pair_hash> uniqueEntries;

    if (setSize <= 4) {
        numLowestAccuracies = setSize;
        numRandomEntries = 0;
    }

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

    // Collect all possible answers
    allAnswers.reserve(setSize);
    std::vector<std::pair<std::string, std::string>> tableValues;
    tableValues = UserSession::getUserSession()->getTableKeyValues(setName);
    for (const auto& entry : tableValues) {
        allAnswers.push_back(entry.first);
    }
}

std::string InverseMultipleChoice::getQuestion()
{
    if (currentIndex < keyValues.size()) {
        return keyValues[currentIndex].second;
    }
    return "";
}

std::string InverseMultipleChoice::getAnswer()
{
    if (currentIndex < keyValues.size()) {
        return keyValues[currentIndex].first;
    }
    return "";
}

bool InverseMultipleChoice::goToNextQuestion()
{
    if (currentIndex + 1 < keyValues.size()) {
        ++currentIndex;
        return true;
    }
    return false;
}

std::tuple<std::string, std::string, std::string, std::string> InverseMultipleChoice::generateOptions() {
    std::vector<std::string> options;
    std::random_device rd;
    std::mt19937 gen(rd());

    if (setSize <= 4) {
        std::unordered_set<std::string> uniqueOptions(allAnswers.begin(), allAnswers.end());

        for (int i = uniqueOptions.size(); i < 4; ++i) {
            uniqueOptions.emplace("");
        }

        options.assign(uniqueOptions.begin(), uniqueOptions.end());
    } else {
        std::unordered_set<std::string> optionSet;

        while (optionSet.size() < 3) {
            std::uniform_int_distribution<> dis(0, allAnswers.size() - 1);
            auto sampled = allAnswers[dis(gen)];
            if (sampled != keyValues[currentIndex].first) {
                optionSet.insert(sampled);
            }
        }

        optionSet.insert(keyValues[currentIndex].first);
        options.assign(optionSet.begin(), optionSet.end());
    }

    std::shuffle(options.begin(), options.end(), gen);

    while (options.size() < 4) {
        options.emplace_back("");
    }

    return std::make_tuple(options[0], options[1], options[2], options[3]);
}


void InverseMultipleChoice::updateScoresInTable(bool isCorrect)
{
    if (currentIndex < keyValues.size()) {
        UserSession::getUserSession()->updateScore(setName, keyValues[currentIndex].first, isCorrect);
    }
}