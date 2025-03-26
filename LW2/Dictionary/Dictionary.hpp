#pragma once
#include <string>
#include <vector>

const std::string ERR_OPEN_FILE_READ = "�� ������� ������� ���� ������� ��� ������";
const std::string ERR_OPEN_FILE_WRITE = "�� ������� ������� ���� ������� ��� ������";
const std::string ERR_WRITE_TO_FILE = "������ ��� ������ � ����";
const std::string ERR_INVALID_ARGS = "�������������: <���������> <���� � ����� �������>";

void LoadDictionary(const std::string& dictionaryPath);
void ProcessSaveDialog(std::istream& input, std::ostream& output);
void ProcessUserInput(std::istream& input, std::ostream& output);
