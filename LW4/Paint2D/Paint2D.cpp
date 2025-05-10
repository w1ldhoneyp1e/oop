#include <iostream>
#include <fstream>
#include <sstream>
#include "HandlerPaint2D.h"
#include "ShapeStorage.h"
#include "ShapeProcessor.h"
#include "Canvas.h"

int main(int argc, char* argv[])
{
    ShapeStorage storage;
    ShapeProcessor processor;
    HandlerPaint2D handler(storage, processor);

    std::istream* input = &std::cin;
    std::ifstream file;
    if (argc > 1) {
        file.open(argv[1]);
        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл: " << argv[1] << std::endl;
            return 1;
        }
        input = &file;
    }

    std::string commandLine;
    std::ostringstream output;
    bool exitRequested = false;

    while (!exitRequested && std::getline(*input, commandLine))
    {
        if (commandLine == "exit")
        {
            exitRequested = true;
            break;
        }
        handler.HandleCommand(commandLine, output);
        std::cout << output.str();
        output.str("");
        output.clear();
    }

    Canvas canvas(800, 600, "Paint2D");
    while (canvas.GetWindow().isOpen())
    {
        sf::Event event;
        while (canvas.GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                canvas.GetWindow().close();
        }

        canvas.GetWindow().clear(sf::Color::White);

        for (const auto& shape : storage.GetShapes())
        {
            shape->Draw(canvas);
        }

        canvas.GetWindow().display();
    }

    return 0;
}