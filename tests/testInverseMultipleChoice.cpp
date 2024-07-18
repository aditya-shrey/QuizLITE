#include "../StudyingMethods/InverseMultipleChoice.h"
#include "../User/UserSession.h"
#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

class InverseMultipleChoiceTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        auto userSession = UserSession::getUserSession();
        userSession->createStudySet("History");
        userSession->addToStudySet("History", "1776", "Independence of USA");
        userSession->addToStudySet("History", "1945", "End of WWII");
        userSession->addToStudySet("History", "1969", "Moon Landing");
    }

    void TearDown() override
    {
        auto userSession = UserSession::getUserSession();
        userSession->deleteStudySet("History");
    }
};

class TestableInverseMultipleChoice : public InverseMultipleChoice {
public:
    TestableInverseMultipleChoice(const std::string& setName,
        int numLowestAccuracies, int numRandomEntries)
        : InverseMultipleChoice(setName, numLowestAccuracies, numRandomEntries)
    {
        // Bypass shuffling for test predictability
    }

    const std::vector<std::pair<std::string, std::string>>& getKeyValues() const
    {
        return keyValues;
    }
};

TEST_F(InverseMultipleChoiceTest, TestGetQuestionAndAnswer)
{
    TestableInverseMultipleChoice inverseMultipleChoice(
        "History", 3, 0); // 3 lowest accuracy entries, no random entries

    std::unordered_set<std::string> expectedQuestions = { "1776", "1945", "1969" };
    std::unordered_set<std::string> expectedAnswers = {
        "Independence of USA", "End of WWII", "Moon Landing"
    };

    for (int i = 0; i < 3; ++i) {
        std::string question = inverseMultipleChoice.getQuestion();
        std::string answer = inverseMultipleChoice.getAnswer();
        ASSERT_TRUE(expectedQuestions.find(answer) != expectedQuestions.end());
        ASSERT_TRUE(expectedAnswers.find(question) != expectedAnswers.end());
        expectedQuestions.erase(question);
        expectedAnswers.erase(answer);
        inverseMultipleChoice.goToNextQuestion();
    }
}

TEST_F(InverseMultipleChoiceTest, TestUpdateScoresAndOrder)
{
    auto userSession = UserSession::getUserSession();
    TestableInverseMultipleChoice inverseMultipleChoice(
        "History", 3, 0); // 3 lowest accuracy entries, no random entries

    for (int i = 0; i < 3; ++i) {
        std::string question = inverseMultipleChoice.getQuestion();
        std::string correctAnswer = inverseMultipleChoice.getAnswer();

        if (question == "1776") {
            inverseMultipleChoice.updateScoresInTable(false); // Incorrect answer
        } else {
            inverseMultipleChoice.updateScoresInTable(true); // Correct answer
        }

        inverseMultipleChoice.goToNextQuestion();
    }

    // Print the accuracy table before reinitialization
    std::cout << "Accuracy table before reinitialization:" << std::endl;
    userSession->printDatabaseTable("History");

    // Reinitialize to pick up updated scores
    TestableInverseMultipleChoice updatedInverseMultipleChoice("History", 1, 0);

    // Print the accuracy table after reinitialization
    std::cout << "Accuracy table after reinitialization:" << std::endl;
    userSession->printDatabaseTable("History");

    // The next question should be the one with the lowest accuracy
    ASSERT_EQ(updatedInverseMultipleChoice.getQuestion(), "Independence of USA");
    ASSERT_EQ(updatedInverseMultipleChoice.getAnswer(), "1776");
}
