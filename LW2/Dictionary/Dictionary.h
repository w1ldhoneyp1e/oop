#pragma once
#include <string>
#include <map>
#include <vector>

using dictionaryType = std::multimap<std::string, std::string>;
const std::string ERR_OPEN_FILE_READ = "Не удалось открыть файл словаря для чтения";
const std::string ERR_OPEN_FILE_WRITE = "Не удалось открыть файл словаря для записи";
const std::string ERR_WRITE_TO_FILE = "Ошибка при записи в файл";
const std::string ERR_INVALID_ARGS = "Использование: <программа> <путь к файлу словаря>";

void LoadDictionary(dictionaryType& dictionary, std::string const& dictionaryPath);
void ProcessSaveDialog(std::istream& input, std::ostream& output, dictionaryType& dictionary, bool& hasChanges, std::string const& dictionaryPath);
void ProcessUserInput(std::istream& input, std::ostream& output, dictionaryType& dictionary, bool& hasChanges);
