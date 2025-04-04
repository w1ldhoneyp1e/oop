#pragma once
#include <string>
#include <map>
#include <vector>

using dictionaryType = std::multimap<std::string, std::string>;
const std::string ERR_OPEN_FILE_READ = "�� ������� ������� ���� ������� ��� ������";
const std::string ERR_OPEN_FILE_WRITE = "�� ������� ������� ���� ������� ��� ������";
const std::string ERR_WRITE_TO_FILE = "������ ��� ������ � ����";
const std::string ERR_INVALID_ARGS = "�������������: <���������> <���� � ����� �������>";

void LoadDictionary(dictionaryType& dictionary, std::string const& dictionaryPath);
void ProcessSaveDialog(std::istream& input, std::ostream& output, dictionaryType& dictionary, bool& hasChanges, std::string const& dictionaryPath);
void ProcessUserInput(std::istream& input, std::ostream& output, dictionaryType& dictionary, bool& hasChanges);
