#include "../User/UserSessionInfo.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

std::string captureOutput(std::function<void()> func)
{
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

class UserSessionInfoTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        UserSessionInfo::instancePtr = nullptr;
        userSessionInfo = UserSessionInfo::getUserSessionInfo();
    }

    void TearDown() override
    {
        delete userSessionInfo;
        userSessionInfo = nullptr;
    }

    UserSessionInfo* userSessionInfo {};
};

TEST_F(UserSessionInfoTest, CreateStudySetSuccess)
{
    bool created = userSessionInfo->createStudySet("testSet");
    EXPECT_TRUE(created);
}

TEST_F(UserSessionInfoTest, CreateDuplicateStudySet)
{
    userSessionInfo->createStudySet("testSet");
    bool createdAgain = userSessionInfo->createStudySet("testSet");
    EXPECT_FALSE(createdAgain);
}

TEST_F(UserSessionInfoTest, ExistsStudySet)
{
    userSessionInfo->createStudySet("testSet");
    bool exists = userSessionInfo->existsStudySet("testSet");
    EXPECT_TRUE(exists);
}

TEST_F(UserSessionInfoTest, DeleteStudySetSuccess)
{
    userSessionInfo->createStudySet("testSet");
    bool deleted = userSessionInfo->deleteStudySet("testSet");
    EXPECT_TRUE(deleted);
    bool exists = userSessionInfo->existsStudySet("testSet");
    EXPECT_FALSE(exists);
    EXPECT_TRUE(userSessionInfo->isSetNamesTableEmpty());
}

TEST_F(UserSessionInfoTest, AddToStudySetSuccess)
{
    userSessionInfo->createStudySet("testSet");
    bool added = userSessionInfo->addToStudySet("testSet", "key1", "value1");
    EXPECT_TRUE(added);
}

TEST_F(UserSessionInfoTest, DeleteFromStudySetSuccess)
{
    userSessionInfo->createStudySet("testSet");
    userSessionInfo->addToStudySet("testSet", "key1", "value1");
    bool deleted = userSessionInfo->deleteFromStudySet("testSet", "key1");
    EXPECT_TRUE(deleted);

    userSessionInfo->deleteStudySet("testSet");
    bool exists = userSessionInfo->existsStudySet("testSet");
    EXPECT_FALSE(exists);
    EXPECT_TRUE(userSessionInfo->isSetNamesTableEmpty());
}

TEST_F(UserSessionInfoTest, VerifyStudySetContents)
{
    userSessionInfo->createStudySet("testSet");
    userSessionInfo->addToStudySet("testSet", "key1", "value1");
    userSessionInfo->addToStudySet("testSet", "key2", "value2");
    userSessionInfo->addToStudySet("testSet", "key3", "value3");
    userSessionInfo->deleteFromStudySet("testSet", "key3");

    std::string output = captureOutput([&]() {
        userSessionInfo->printDatabaseTable("testSet");
    });

    EXPECT_NE(output.find("key1"), std::string::npos);
    EXPECT_NE(output.find("value1"), std::string::npos);
    EXPECT_NE(output.find("key2"), std::string::npos);
    EXPECT_NE(output.find("value2"), std::string::npos);
    EXPECT_EQ(output.find("key3"), std::string::npos);
    EXPECT_EQ(output.find("value3"), std::string::npos);

    userSessionInfo->deleteStudySet("testSet");
    bool exists = userSessionInfo->existsStudySet("testSet");
    EXPECT_FALSE(exists);
    EXPECT_TRUE(userSessionInfo->isSetNamesTableEmpty());
}

TEST_F(UserSessionInfoTest, IsSetNamesTableEmptyWhenNotEmpty)
{
    userSessionInfo->createStudySet("testSet");
    EXPECT_FALSE(userSessionInfo->isSetNamesTableEmpty());
}

TEST_F(UserSessionInfoTest, UpdateScoreCorrect)
{
    userSessionInfo->createStudySet("testSet");
    userSessionInfo->addToStudySet("testSet", "key1", "value1");
    bool updated = userSessionInfo->updateScore("testSet", "key1", true);
    EXPECT_TRUE(updated);
    std::string output = captureOutput([&]() {
        userSessionInfo->printDatabaseTable("testSet");
    });
    EXPECT_NE(output.find("TotalCorrect: 1"), std::string::npos);
    EXPECT_NE(output.find("TimesAsked: 2"), std::string::npos);
}

TEST_F(UserSessionInfoTest, UpdateScoreIncorrect)
{
    userSessionInfo->createStudySet("testSet");
    userSessionInfo->addToStudySet("testSet", "key1", "value1");
    bool updated = userSessionInfo->updateScore("testSet", "key1", false);
    EXPECT_TRUE(updated);
    std::string output = captureOutput([&]() {
        userSessionInfo->printDatabaseTable("testSet");
    });
    EXPECT_NE(output.find("TotalCorrect: 1"), std::string::npos);
    EXPECT_NE(output.find("TimesAsked: 3"), std::string::npos);
}

TEST_F(UserSessionInfoTest, GetTableKeyValues)
{
    userSessionInfo->createStudySet("testSet");
    userSessionInfo->addToStudySet("testSet", "key1", "value1");
    userSessionInfo->addToStudySet("testSet", "key2", "value2");
    auto keyValues = userSessionInfo->getTableKeyValues("testSet");
    EXPECT_EQ(keyValues.size(), 2);
    EXPECT_EQ(keyValues[0].first, "key1");
    EXPECT_EQ(keyValues[0].second, "value1");
    EXPECT_EQ(keyValues[1].first, "key2");
    EXPECT_EQ(keyValues[1].second, "value2");
}

TEST_F(UserSessionInfoTest, GetLowestAccuracies)
{
    userSessionInfo->createStudySet("testSet");
    userSessionInfo->addToStudySet("testSet", "key1", "value1");
    userSessionInfo->addToStudySet("testSet", "key2", "value2");
    userSessionInfo->updateScore("testSet", "key1", true);
    auto lowestAccuracies = userSessionInfo->getLowestAccuracies("testSet", 1);
    EXPECT_EQ(lowestAccuracies.size(), 1);
    EXPECT_EQ(std::get<0>(lowestAccuracies[0]), "key2");
    EXPECT_EQ(std::get<1>(lowestAccuracies[0]), "value2");
    EXPECT_FLOAT_EQ(std::get<2>(lowestAccuracies[0]), 0.0);
}

TEST_F(UserSessionInfoTest, GetRandomEntries)
{
    userSessionInfo->createStudySet("testSet");
    userSessionInfo->addToStudySet("testSet", "key1", "value1");
    userSessionInfo->addToStudySet("testSet", "key2", "value2");
    auto randomEntries = userSessionInfo->getRandomEntries("testSet", 1);
    EXPECT_EQ(randomEntries.size(), 1);
    EXPECT_TRUE(randomEntries[0].first == "key1" || randomEntries[0].first == "key2");
}

TEST_F(UserSessionInfoTest, DeleteFromStudySetSuccess2)
{
    userSessionInfo->createStudySet("testSet");
    userSessionInfo->addToStudySet("testSet", "key1", "value1");
    bool deleted = userSessionInfo->deleteFromStudySet("testSet", "key1");
    EXPECT_TRUE(deleted);

    userSessionInfo->deleteStudySet("testSet");
    bool exists = userSessionInfo->existsStudySet("testSet");
    EXPECT_FALSE(exists);
    EXPECT_TRUE(userSessionInfo->isSetNamesTableEmpty());
}

TEST_F(UserSessionInfoTest, IsSetNamesTableEmptyWhenEmpty2)
{
    EXPECT_TRUE(userSessionInfo->isSetNamesTableEmpty());
}
