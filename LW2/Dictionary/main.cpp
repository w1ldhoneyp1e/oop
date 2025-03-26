#include "Dictionary.hpp"
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
        LoadDictionary(argv[1]);
        ProcessUserInput(std::cin, std::cout);
        ProcessSaveDialog(std::cin, std::cout);
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Îøèáêà: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}