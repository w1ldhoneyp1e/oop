#include <iostream>
#include <fstream>
#include "HandlerPaint2D.h"
#include "Canvas.h"
#include "ShapeStorage.h"
#include "ShapeProcessor.h"

int main(int argc, char* argv[])
{
    Canvas canvas(800, 600, "Paint2D");
    ShapeStorage storage;
    ShapeProcessor processor;
    HandlerPaint2D handler(storage, processor, canvas);

    if (argc > 1) {
        std::ifstream file(argv[1]);
        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл: " << argv[1] << std::endl;
            return 1;
        }
        std::cin.rdbuf(file.rdbuf());
    }

    handler.HandleCommand(std::cin, std::cout);

    while (canvas.GetWindow().isOpen())
    {
        sf::Event event;
        while (canvas.GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                canvas.GetWindow().close();
        }

        canvas.GetWindow().clear(sf::Color::White);

        processor.Draw(storage.GetShapes(), canvas);

        canvas.GetWindow().display();
    }

    return 0;
}