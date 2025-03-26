#include "Dictionary.hpp"
#include <fstream>
#include <map>
#include <algorithm>
#include <cctype>
#include <iostream>

std::multimap<std::string, std::string> dictionary;
bool hasChanges = false;
std::string dictionaryPath;

std::string ToLower(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

void AddTranslation(const std::string& word, const std::string& translation)
{
    dictionary.insert({ ToLower(word), translation });
    dictionary.insert({ ToLower(translation), word });
    hasChanges = true;
}

void PrintTranslations(const std::vector<std::string>& translations, std::ostream& output)
{
    auto it = translations.begin();
    output << *it;
    ++it;
    for (auto it = translations.begin() + 1; it != translations.end(); ++it)
    {
        output << ", " << *it;
    }
    output << std::endl;
}

void ProcessUnknownWord(const std::string& word, std::istream& input, std::ostream& output)
{
    output << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << std::endl;
    std::string translation;
    std::getline(input, translation);

    if (!translation.empty())
    {
        AddTranslation(word, translation);
        output << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\"." << std::endl;
    }
    else
    {
        output << "Слово \"" << word << "\" проигнорировано." << std::endl;
    }
}

bool IsExitCommand(const std::string& input)
{
    return input == "...";
}

// Interface

void LoadDictionary(const std::string& path)
{
    dictionaryPath = path;
    std::ifstream file(dictionaryPath);
    if (!file)
    {
        throw std::runtime_error(ERR_OPEN_FILE_READ);
    }

    std::string line;
    while (std::getline(file, line))
    {
        size_t pos = line.find(':');
        if (pos != std::string::npos)
        {
            std::string word = line.substr(0, pos);
            std::string translation = line.substr(pos + 1);
            dictionary.insert({word, translation});
        }
    }
}

std::vector<std::string> GetTranslations(const std::string& word)
{
    std::vector<std::string> translations;
    std::string lowerWord = ToLower(word);

    auto range = dictionary.equal_range(lowerWord);
    for (auto it = range.first; it != range.second; ++it)
    {
        translations.push_back(it->second);
    }

    return translations;
}

void TryToSaveDictionary(std::ostream& output)
{
    std::ofstream file(dictionaryPath);
    if (!file)
    {
        throw std::runtime_error(ERR_OPEN_FILE_WRITE);
    }

    for (const auto& pair : dictionary)
    {
        file << pair.first << ":" << pair.second << std::endl;
    }
    output << "Изменения сохранены. До свидания." << std::endl;
}

bool HasChanges()
{
    return hasChanges;
}

void ProcessSaveDialog(std::istream& input, std::ostream& output)
{
    if (HasChanges())
    {
        output << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
        std::string answer;
        std::getline(input, answer);

        if (answer == "Y" || answer == "y")
        {
            TryToSaveDictionary(output);
        }
    }
}

void ProcessUserInput(std::istream& input, std::ostream& output)
{
    std::string userInput;
    while (true)
    {
        output << ">";
        std::getline(input, userInput);

        if (IsExitCommand(userInput))
            break;

        auto translations = GetTranslations(userInput);
        if (translations.empty())
        {
            ProcessUnknownWord(userInput, input, output);
        }
        else
        {
            PrintTranslations(translations, output);
        }
    }
}
