#include "../Database/DatabaseManager.h"
#include <gtest/gtest.h>

class DatabaseManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure a clean database for each test
        dbManager = DatabaseManager::getDatabaseManager(":memory:");
        ASSERT_TRUE(dbManager->openDatabase());
        ASSERT_EQ(dbManager->executeQuery("CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT);"), SQLITE_OK);
    }

    void TearDown() override {
        dbManager->closeDatabase();
    }

    DatabaseManager* dbManager{};
};

TEST_F(DatabaseManagerTest, SingletonInstance) {
    DatabaseManager* dbManager1 = DatabaseManager::getDatabaseManager(":memory:");
    DatabaseManager* dbManager2 = DatabaseManager::getDatabaseManager(":memory:");
    EXPECT_EQ(dbManager1, dbManager2);
}

TEST_F(DatabaseManagerTest, OpenDatabase) {
    EXPECT_TRUE(dbManager->openDatabase());
}

TEST_F(DatabaseManagerTest, CloseDatabase) {
    dbManager->closeDatabase();
    // Attempting to close again should not cause any error
    dbManager->closeDatabase();
}

TEST_F(DatabaseManagerTest, ExecuteQuery) {
    EXPECT_EQ(dbManager->executeQuery("INSERT INTO test (name) VALUES ('Alice');"), SQLITE_OK);
    EXPECT_EQ(dbManager->executeQuery("INSERT INTO test (name) VALUES ('Bob');"), SQLITE_OK);
}

TEST_F(DatabaseManagerTest, ExecuteQueryWithResults) {
    dbManager->executeQuery("INSERT INTO test (name) VALUES ('Alice');");
    dbManager->executeQuery("INSERT INTO test (name) VALUES ('Bob');");

    std::vector<std::map<std::string, std::string>> results = dbManager->executeQueryWithResults("SELECT * FROM test;");
    ASSERT_EQ(results.size(), 2);
    EXPECT_EQ(results[0]["name"], "Alice");
    EXPECT_EQ(results[1]["name"], "Bob");
}

TEST_F(DatabaseManagerTest, PrintDatabaseTable) {
    dbManager->executeQuery("INSERT INTO test (name) VALUES ('Alice');");
    dbManager->executeQuery("INSERT INTO test (name) VALUES ('Bob');");

    // This test is not easily automated since it involves printing to the console
    // However, you can check if the function executes without errors
    dbManager->printDatabaseTable("test");
}

TEST_F(DatabaseManagerTest, IsTableEmpty) {
    EXPECT_TRUE(dbManager->isTableEmpty("test"));

    dbManager->executeQuery("INSERT INTO test (name) VALUES ('Alice');");
    EXPECT_FALSE(dbManager->isTableEmpty("test"));
}
