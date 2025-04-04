#include "Dictionary.h"
#include <iostream>
#include <windows.h>

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RU");
    
    if (argc != 2)
    {
        std::cout << ERR_INVALID_ARGS << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        dictionaryType dictionary;
        bool hasChanges = false;
        std::string dictionaryPath = argv[1];
        LoadDictionary(dictionary, dictionaryPath);
        ProcessUserInput(std::cin, std::cout, dictionary, hasChanges);
        ProcessSaveDialog(std::cin, std::cout, dictionary, hasChanges, dictionaryPath);
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << "������: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}