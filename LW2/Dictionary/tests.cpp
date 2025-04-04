#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "Dictionary.h"
#include <sstream>
#include <fstream>
#include <map>

void CreateTestDictionary(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    file << content;
    file.close();
}

void RemoveTestFile(const std::string& path) {
    std::remove(path.c_str());
}

TEST_CASE("LoadDictionary function tests", "[dictionary]")
{
    const std::string TEST_DICT_PATH = "test_dictionary.txt";
    dictionaryType dictionary;

    SECTION("Loading empty dictionary")
    {
        CreateTestDictionary(TEST_DICT_PATH, "");
        REQUIRE_NOTHROW(LoadDictionary(dictionary, TEST_DICT_PATH));
        RemoveTestFile(TEST_DICT_PATH);
    }

    SECTION("Loading non-existent file")
    {
        REQUIRE_THROWS_WITH(LoadDictionary(dictionary, "nonexistent_file.txt"), ERR_OPEN_FILE_READ);
    }

    SECTION("Loading dictionary with data")
    {
        CreateTestDictionary(TEST_DICT_PATH, "cat:�����\ndog:������");
        LoadDictionary(dictionary, TEST_DICT_PATH);

        std::stringstream input("cat\n...\n");
        std::stringstream output;
        bool hasChanges = false;
        ProcessUserInput(input, output, dictionary, hasChanges);

        REQUIRE(output.str().find("�����") != std::string::npos);
        REQUIRE(output.str().find("������") == std::string::npos);
        RemoveTestFile(TEST_DICT_PATH);
    }
}

TEST_CASE("ProcessUserInput function tests", "[input]")
{
    const std::string TEST_DICT_PATH = "test_dictionary.txt";
    dictionaryType dictionary;
    bool hasChanges = false;

    SECTION("Looking up existing word")
    {
        CreateTestDictionary(TEST_DICT_PATH, "cat:�����");
        LoadDictionary(dictionary, TEST_DICT_PATH);

        std::stringstream input("cat\n...\n");
        std::stringstream output;

        ProcessUserInput(input, output, dictionary, hasChanges);

        REQUIRE(output.str().find("�����") != std::string::npos);
        RemoveTestFile(TEST_DICT_PATH);
    }

    SECTION("Adding new word")
    {
        CreateTestDictionary(TEST_DICT_PATH, "");
        LoadDictionary(dictionary, TEST_DICT_PATH);

        std::stringstream input("dog\n������\n...\n");
        std::stringstream output;

        ProcessUserInput(input, output, dictionary, hasChanges);

        REQUIRE(output.str().find("����������� �����") != std::string::npos);
        REQUIRE(output.str().find("��������� � �������") != std::string::npos);
        RemoveTestFile(TEST_DICT_PATH);
    }
}

TEST_CASE("ProcessSaveDialog function tests", "[save]")
{
    const std::string TEST_DICT_PATH = "test_dictionary.txt";
    dictionaryType dictionary;
    bool hasChanges = false;

    SECTION("Save changes when requested")
    {
        CreateTestDictionary(TEST_DICT_PATH, "");
        LoadDictionary(dictionary, TEST_DICT_PATH);

        std::stringstream input1("dog\n������\n...\n");
        std::stringstream output1;
        ProcessUserInput(input1, output1, dictionary, hasChanges);

        std::stringstream input2("y\n");
        std::stringstream output2;
        ProcessSaveDialog(input2, output2, dictionary, hasChanges, TEST_DICT_PATH);

        REQUIRE(output2.str().find("��������� ���������") != std::string::npos);

        std::ifstream file(TEST_DICT_PATH);
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        REQUIRE(content.find("dog:������") != std::string::npos);
        RemoveTestFile(TEST_DICT_PATH);
    }
}