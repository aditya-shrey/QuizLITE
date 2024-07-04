//
// Created by Aditya Shrey on 7/4/24.
//

#ifndef QUIZLITE_INVERSEMULTIPLECHOICE_H
#define QUIZLITE_INVERSEMULTIPLECHOICE_H

#include "StudyMethods.h"
#include "../User/UserSessionInfo.h"
#include <vector>
#include <random>
#include <algorithm>

class InverseMultipleChoice : public StudyMethods {
private:
    std::vector<std::pair<std::string, std::string>> keyValues;
    size_t currentIndex;
    std::string setName;
    std::vector<std::pair<std::string, std::string>> options;

public:
    InverseMultipleChoice(const std::string& setName);
    void startStudying() override;
    void endStudying() override;
    void displayQuestion() override;
    std::string revealAnswer() override;
    void goToNextQuestion() override;
    void updateScoresInTable(bool isCorrect);
    void generateOptions();
};

#endif //QUIZLITE_INVERSEMULTIPLECHOICE_H
