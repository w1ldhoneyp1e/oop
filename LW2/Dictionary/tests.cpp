#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "Dictionary.hpp"
#include <sstream>
#include <fstream>
#include <map>

extern std::multimap<std::string, std::string> dictionary;
extern bool hasChanges;
extern std::string dictionaryPath;

void CreateTestDictionary(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    file << content;
    file.close();
}

void RemoveTestFile(const std::string& path) {
    std::remove(path.c_str());
}

void ClearTestDictionary() {
    dictionary.clear();
    hasChanges = false;
    dictionaryPath.clear();
}

TEST_CASE("LoadDictionary function tests", "[dictionary]")
{
    const std::string TEST_DICT_PATH = "test_dictionary.txt";
    ClearTestDictionary();

    SECTION("Loading empty dictionary")
    {
        CreateTestDictionary(TEST_DICT_PATH, "");
        REQUIRE_NOTHROW(LoadDictionary(TEST_DICT_PATH));
        RemoveTestFile(TEST_DICT_PATH);
    }

    SECTION("Loading non-existent file")
    {
        REQUIRE_THROWS_WITH(LoadDictionary("nonexistent_file.txt"), ERR_OPEN_FILE_READ);
    }

    SECTION("Loading dictionary with data")
    {
        CreateTestDictionary(TEST_DICT_PATH, "cat:кошка\ndog:собака");
        LoadDictionary(TEST_DICT_PATH);

        std::stringstream input("cat\n...\n");
        std::stringstream output;
        ProcessUserInput(input, output);

        REQUIRE(output.str().find("кошка") != std::string::npos);
        REQUIRE(output.str().find("собака") == std::string::npos);
        RemoveTestFile(TEST_DICT_PATH);
    }
}

TEST_CASE("ProcessUserInput function tests", "[input]")
{
    const std::string TEST_DICT_PATH = "test_dictionary.txt";
    ClearTestDictionary();

    SECTION("Looking up existing word")
    {
        CreateTestDictionary(TEST_DICT_PATH, "cat:кошка");
        LoadDictionary(TEST_DICT_PATH);

        std::stringstream input("cat\n...\n");
        std::stringstream output;

        ProcessUserInput(input, output);

        REQUIRE(output.str().find("кошка") != std::string::npos);
        RemoveTestFile(TEST_DICT_PATH);
    }

    SECTION("Adding new word")
    {
        CreateTestDictionary(TEST_DICT_PATH, "");
        LoadDictionary(TEST_DICT_PATH);

        std::stringstream input("dog\nсобака\n...\n");
        std::stringstream output;

        ProcessUserInput(input, output);

        REQUIRE(output.str().find("Неизвестное слово") != std::string::npos);
        REQUIRE(output.str().find("сохранено в словаре") != std::string::npos);
        RemoveTestFile(TEST_DICT_PATH);
    }

    SECTION("Ignoring unknown word")
    {
        CreateTestDictionary(TEST_DICT_PATH, "");
        LoadDictionary(TEST_DICT_PATH);

        std::stringstream input("dog\n\n...\n");
        std::stringstream output;

        ProcessUserInput(input, output);

        REQUIRE(output.str().find("проигнорировано") != std::string::npos);
        RemoveTestFile(TEST_DICT_PATH);
    }
}

TEST_CASE("ProcessSaveDialog function tests", "[save]")
{
    const std::string TEST_DICT_PATH = "test_dictionary.txt";
    ClearTestDictionary();

    SECTION("Save changes when requested")
    {
        CreateTestDictionary(TEST_DICT_PATH, "");
        LoadDictionary(TEST_DICT_PATH);

        std::stringstream input1("dog\nсобака\n...\n");
        std::stringstream output1;
        ProcessUserInput(input1, output1);

        std::stringstream input2("y\n");
        std::stringstream output2;
        ProcessSaveDialog(input2, output2);

        REQUIRE(output2.str().find("Изменения сохранены") != std::string::npos);

        std::ifstream file(TEST_DICT_PATH);
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        REQUIRE(content.find("dog:собака") != std::string::npos);
        RemoveTestFile(TEST_DICT_PATH);
    }

    SECTION("Skip saving when declined")
    {
        CreateTestDictionary(TEST_DICT_PATH, "");
        LoadDictionary(TEST_DICT_PATH);

        std::stringstream input1("dog\nсобака\n...\n");
        std::stringstream output1;
        ProcessUserInput(input1, output1);

        std::stringstream input2("n\n");
        std::stringstream output2;
        ProcessSaveDialog(input2, output2);

        std::ifstream file(TEST_DICT_PATH);
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        REQUIRE(content.empty());
        RemoveTestFile(TEST_DICT_PATH);
    }
}