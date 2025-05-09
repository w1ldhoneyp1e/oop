#include <iostream>
#include <fstream>
#include "HandlerPaint2D.h"

int main(int argc, char* argv[])
{
    HandlerPaint2D handler;

    if (argc > 1) {
        std::ifstream file(argv[1]);
        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл: " << argv[1] << std::endl;
            return 1;
        }
        std::cin.rdbuf(file.rdbuf());
    }

    handler.HandleCommand(std::cin, std::cout);

    return 0;
}