#include "../Database/DatabaseManager.h"
#include <gtest/gtest.h>

class DatabaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Remove any existing test database
        std::remove(testDbName.c_str());

        // Initialize the database manager instance
        dbManager = DatabaseManager::getDatabaseManager(testDbName);
        ASSERT_TRUE(dbManager->openDatabase());

        // Create a test table
        std::string createTableQuery = "CREATE TABLE test_table (id INTEGER PRIMARY KEY, name TEXT);";
        ASSERT_TRUE(dbManager->executeQuery(createTableQuery));
    }

    void TearDown() override {
        dbManager->closeDatabase();
        // Remove the test database file
        std::remove(testDbName.c_str());
    }

    const std::string testDbName = "test.db";
    DatabaseManager* dbManager = nullptr;
};

TEST_F(DatabaseTest, OpenDatabase) {
    ASSERT_TRUE(dbManager->openDatabase());
}

TEST_F(DatabaseTest, CloseDatabase) {
    dbManager->closeDatabase();
    ASSERT_FALSE(dbManager->executeQuery("SELECT 1;"));
}

TEST_F(DatabaseTest, ExecuteQuery) {
    std::string insertQuery = "INSERT INTO test_table (name) VALUES ('John Doe');";
    ASSERT_TRUE(dbManager->executeQuery(insertQuery));
}

TEST_F(DatabaseTest, ExecuteQueryWithResults) {
    std::string insertQuery = "INSERT INTO test_table (name) VALUES ('John Doe');";
    ASSERT_TRUE(dbManager->executeQuery(insertQuery));

    std::string selectQuery = "SELECT * FROM test_table;";
    auto results = dbManager->executeQueryWithResults(selectQuery);
    ASSERT_EQ(results.size(), 1);
    ASSERT_EQ(results[0]["name"], "John Doe");
}

TEST_F(DatabaseTest, PrintDatabaseTable) {
    std::string insertQuery = "INSERT INTO test_table (name) VALUES ('John Doe');";
    ASSERT_TRUE(dbManager->executeQuery(insertQuery));

    // Redirect stdout to a string stream
    std::ostringstream oss;
    std::streambuf* coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Call the print method
    dbManager->printDatabaseTable("test_table");

    // Restore stdout
    std::cout.rdbuf(coutBuf);

    // Check the output
    std::string output = oss.str();
    std::string expectedOutput = "id: 1\nname: John Doe\n\n";
    ASSERT_EQ(output, expectedOutput);
}