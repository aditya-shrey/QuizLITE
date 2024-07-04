//
// Created by Aditya Shrey on 7/4/24.
//

#ifndef QUIZLITE_STUDYMETHODS_H
#define QUIZLITE_STUDYMETHODS_H

#include <vector>
#include <string>
#include <utility>
#include <iostream>

class StudyMethods {
public:
    virtual void startStudying() = 0;
    virtual void endStudying() = 0;
    virtual void displayQuestion() = 0;
    virtual std::string revealAnswer() = 0;
    virtual void goToNextQuestion() = 0;
    virtual ~StudyMethods() = default;
};

#endif //QUIZLITE_STUDYMETHODS_H
