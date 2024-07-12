#include "../StudyingMethods/MultipleChoice.h"
#include "../User/UserSession.h"
#include <gtest/gtest.h>
#include <unordered_set>

class MultipleChoiceTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        auto userSession = UserSession::getUserSession();
        userSession->createStudySet("Science");
        userSession->addToStudySet("Science", "H2O", "Water");
        userSession->addToStudySet("Science", "CO2", "Carbon Dioxide");
        userSession->addToStudySet("Science", "NaCl", "Salt");
    }

    void TearDown() override
    {
        auto userSession = UserSession::getUserSession();
        userSession->deleteStudySet("Science");
    }
};

class TestableMultipleChoice : public MultipleChoice {
public:
    TestableMultipleChoice(const std::string& setName, int numLowestAccuracies, int numRandomEntries)
        : MultipleChoice(setName, numLowestAccuracies, numRandomEntries)
    {
        // Bypass shuffling for test predictability
    }

    const std::vector<std::pair<std::string, std::string>>& getKeyValues() const
    {
        return keyValues;
    }
};

TEST_F(MultipleChoiceTest, TestGetQuestionAndAnswer)
{
    TestableMultipleChoice multipleChoice("Science", 3, 0); // 3 lowest accuracy entries, no random entries

    std::unordered_set<std::string> expectedQuestions = { "H2O", "CO2", "NaCl" };
    std::unordered_set<std::string> expectedAnswers = { "Water", "Carbon Dioxide", "Salt" };

    for (int i = 0; i < 3; ++i) {
        std::string question = multipleChoice.getQuestion();
        std::string answer = multipleChoice.getAnswer();
        ASSERT_TRUE(expectedQuestions.find(question) != expectedQuestions.end());
        ASSERT_TRUE(expectedAnswers.find(answer) != expectedAnswers.end());
        expectedQuestions.erase(question);
        expectedAnswers.erase(answer);
        multipleChoice.goToNextQuestion();
    }

    ASSERT_TRUE(expectedQuestions.empty());
    ASSERT_TRUE(expectedAnswers.empty());
}

TEST_F(MultipleChoiceTest, TestGenerateOptions)
{
    TestableMultipleChoice multipleChoice("Science", 3, 0); // 3 lowest accuracy entries, no random entries

    // Test options for the first question
    auto options = multipleChoice.generateOptions();
    ASSERT_TRUE(
        std::get<0>(options) == "Water" || std::get<1>(options) == "Water" || std::get<2>(options) == "Water" || std::get<3>(options) == "Water");

    // Test options for the second question
    multipleChoice.goToNextQuestion();
    options = multipleChoice.generateOptions();
    ASSERT_TRUE(
        std::get<0>(options) == "Carbon Dioxide" || std::get<1>(options) == "Carbon Dioxide" || std::get<2>(options) == "Carbon Dioxide" || std::get<3>(options) == "Carbon Dioxide");

    // Test options for the third question
    multipleChoice.goToNextQuestion();
    options = multipleChoice.generateOptions();
    ASSERT_TRUE(
        std::get<0>(options) == "Salt" || std::get<1>(options) == "Salt" || std::get<2>(options) == "Salt" || std::get<3>(options) == "Salt");
}

TEST_F(MultipleChoiceTest, TestUpdateScoresAndOrder)
{
    auto userSession = UserSession::getUserSession();
    TestableMultipleChoice multipleChoice("Science", 3, 0); // 3 lowest accuracy entries, no random entries

    for (int i = 0; i < 3; ++i) {
        std::string question = multipleChoice.getQuestion();
        if (question == "H2O") {
            multipleChoice.updateScoresInTable(false); // Incorrect answer
        } else {
            multipleChoice.updateScoresInTable(true); // Correct answer
        }
        multipleChoice.goToNextQuestion();
    }

    // Print the accuracy table before reinitialization
    std::cout << "Accuracy table before reinitialization:" << std::endl;
    userSession->printDatabaseTable("Science");

    // Reinitialize to pick up updated scores
    TestableMultipleChoice updatedMultipleChoice("Science", 1, 0);

    // Print the accuracy table after reinitialization
    std::cout << "Accuracy table after reinitialization:" << std::endl;
    userSession->printDatabaseTable("Science");

    // The next question should be the one with the lowest accuracy
    ASSERT_EQ(updatedMultipleChoice.getQuestion(), "H2O");
    ASSERT_EQ(updatedMultipleChoice.getAnswer(), "Water");
}
