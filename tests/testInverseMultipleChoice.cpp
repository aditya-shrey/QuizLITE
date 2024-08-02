#include "../StudyingMethods/InverseMultipleChoice.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <string>

class InverseMultipleChoiceTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        UserSession::resetInstance();
        userSession = UserSession::getUserSession();
        userSession->createStudySet("TestSet");
        userSession->addToStudySet("TestSet", "Question1", "Answer1");
        userSession->addToStudySet("TestSet", "Question2", "Answer2");
        userSession->addToStudySet("TestSet", "Question3", "Answer3");
        userSession->addToStudySet("TestSet", "Question4", "Answer4");
    }

    void TearDown() override
    {
        UserSession::resetInstance();
    }

    UserSession* userSession;
};

TEST_F(InverseMultipleChoiceTest, InitializationWithFewEntries)
{
    InverseMultipleChoice imc("TestSet", 4, 0);
    std::string getQuestion = imc.getQuestion();
    std::set<std::string> expectedAnswers = { "Answer1", "Answer2", "Answer3", "Answer4" };
    EXPECT_TRUE(expectedAnswers.find(getQuestion) != expectedAnswers.end());

    if (getQuestion == "Answer1") {
        EXPECT_EQ(imc.getAnswer(), "Question1");
    } else if (getQuestion == "Answer2") {
        EXPECT_EQ(imc.getAnswer(), "Question2");
    } else if (getQuestion == "Answer3") {
        EXPECT_EQ(imc.getAnswer(), "Question3");
    } else if (getQuestion == "Answer4") {
        EXPECT_EQ(imc.getAnswer(), "Question4");
    } else {
        FAIL() << "Unexpected question";
    }
}

TEST_F(InverseMultipleChoiceTest, GoToNextQuestionBoundary)
{
    InverseMultipleChoice imc("TestSet", 2, 2);
    for (int i = 0; i < 3; ++i) {
        imc.goToNextQuestion();
    }
    EXPECT_FALSE(imc.goToNextQuestion());
}

TEST_F(InverseMultipleChoiceTest, GenerateOptionsForSmallSet)
{
    InverseMultipleChoice imc("TestSet", 2, 1);
    auto options = imc.generateOptions();
    std::unordered_set<std::string> uniqueOptions { std::get<0>(options), std::get<1>(options), std::get<2>(options), std::get<3>(options) };
    EXPECT_EQ(uniqueOptions.size(), 4);
}

TEST_F(InverseMultipleChoiceTest, GenerateOptionsForLargeSet)
{
    // Add six new questions
    for (int i = 5; i <= 10; ++i) {
        userSession->addToStudySet("TestSet", "Question" + std::to_string(i), "Answer" + std::to_string(i));
    }

    InverseMultipleChoice imc("TestSet", 2, 2);
    auto options = imc.generateOptions();
    std::unordered_set<std::string> uniqueOptions { std::get<0>(options), std::get<1>(options), std::get<2>(options), std::get<3>(options) };
    EXPECT_EQ(uniqueOptions.size(), 4);

    for (int i = 5; i <= 10; ++i) {
        userSession->deleteFromStudySet("TestSet", "Question" + std::to_string(i));
    }

    auto table = userSession->getTable("TestSet");
    userSession->printDatabaseTable("TestSet");

    for (const auto& row : table) {
        std::string question = std::get<1>(row);
        EXPECT_TRUE(question != "Question5" && question != "Question6" && question != "Question7" && question != "Question8" && question != "Question9" && question != "Question10");
    }
}

TEST_F(InverseMultipleChoiceTest, UpdateScoresInTableCorrect)
{
    InverseMultipleChoice imc("TestSet", 4, 0);
    for (int i = 0; i < 4; ++i) {
        imc.updateScoresInTable(false);
        imc.goToNextQuestion();
    }
    auto table = userSession->getTable("TestSet");
    for (const auto& row : table) {
        EXPECT_EQ(std::get<3>(row), 0);
        EXPECT_EQ(std::get<4>(row), 1);
    }
}

TEST_F(InverseMultipleChoiceTest, GetQuestionOutOfBounds)
{
    InverseMultipleChoice imc("TestSet", 2, 0);
    for (int i = 0; i < 2; i++) {
        imc.goToNextQuestion();
    }
    EXPECT_NE(imc.getQuestion(), "");
}

TEST_F(InverseMultipleChoiceTest, GetAnswerOutOfBounds)
{
    InverseMultipleChoice imc("TestSet", 2, 0);
    for (int i = 0; i < 2; i++) {
        imc.goToNextQuestion();
    }
    EXPECT_NE(imc.getAnswer(), "");

    userSession->deleteStudySet("TestSet");
}
