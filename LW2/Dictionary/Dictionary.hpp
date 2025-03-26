#pragma once
#include <string>
#include <vector>

const std::string ERR_OPEN_FILE_READ = "Не удалось открыть файл словаря для чтения";
const std::string ERR_OPEN_FILE_WRITE = "Не удалось открыть файл словаря для записи";
const std::string ERR_WRITE_TO_FILE = "Ошибка при записи в файл";
const std::string ERR_INVALID_ARGS = "Использование: <программа> <путь к файлу словаря>";

void LoadDictionary(const std::string& dictionaryPath);
void ProcessSaveDialog(std::istream& input, std::ostream& output);
void ProcessUserInput(std::istream& input, std::ostream& output);
