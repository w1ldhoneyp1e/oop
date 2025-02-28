#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

const int MAX_SIZE = 100;
const char FILL_CHAR = '.';
const char START_CHAR = 'O';
const char WALL_CHAR = '#';
const char EMPTY_CHAR = ' ';
const std::string ERROR = "ERROR";

using Image = std::vector<std::string>;

struct Point
{
    size_t row;
    size_t col;
    Point(size_t r, size_t c) : row(r), col(c) {}
};

void PrintUsage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "  fill.exe <input file> <output file>" << std::endl;
    std::cout << "  fill.exe -h" << std::endl;
    std::cout << std::endl;
    std::cout << "If no arguments provided, reads from stdin" << std::endl;
}

bool IsValidPoint(const Image& image, const Point& point)
{
    return point.row >= 0 && point.row < image.size() &&
           point.col >= 0 && point.col < image[0].size() &&
           image[point.row][point.col] != WALL_CHAR &&
           image[point.row][point.col] != FILL_CHAR;
}

void WaveFill(std::vector<std::string>& image, const Point& start)
{
    if (!IsValidPoint(image, start))
    {
        return;
    }

    std::queue<Point> points;
    points.push(start);

    while (!points.empty())
    {
        Point current = points.front();
        points.pop();

        if (!IsValidPoint(image, current))
        {
            continue;
        }

        if (image[current.row][current.col] != START_CHAR)
        {
            image[current.row][current.col] = FILL_CHAR;
        }

        points.push(Point(current.row - 1, current.col));
        points.push(Point(current.row + 1, current.col));
        points.push(Point(current.row, current.col - 1));
        points.push(Point(current.row, current.col + 1));
    }
}

Image ReadImage(std::istream& input)
{
    Image image;
    std::string line;

    while (std::getline(input, line) && image.size() < MAX_SIZE)
    {
        if (line.length() > MAX_SIZE)
            line.resize(MAX_SIZE);
            
        for (char c : line)
        {
            if (c != WALL_CHAR && c != START_CHAR && c != EMPTY_CHAR)
            {
                throw std::invalid_argument(ERROR);
            }
        }
        
        line.resize(MAX_SIZE, EMPTY_CHAR);
        image.push_back(line);
    }

    while (image.size() < MAX_SIZE)
    {
        image.push_back(std::string(MAX_SIZE, EMPTY_CHAR));
    }

    return image;
}

void ProcessImage(Image& image)
{
    for (size_t i = 0; i < image.size(); ++i)
    {
        for (size_t j = 0; j < image[i].length(); ++j)
        {
            if (image[i][j] == START_CHAR)
            {
                WaveFill(image, Point(i, j));
            }
        }
    }
}

void PrintImage(const Image& image, std::ostream& output)
{
    for (const auto& line : image)
    {
        output << line << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc > 3)
    {
        PrintUsage();
        throw std::invalid_argument(ERROR);
    }

    if (argc == 2 && std::string(argv[1]) == "-h")
    {
        PrintUsage();
        return EXIT_SUCCESS;
    }

    try 
    {
        Image image;
        
        if (argc == 3)
        {
            std::ifstream input(argv[1]);
            if (!input.is_open())
            {
                throw std::invalid_argument(ERROR);
            }
            image = ReadImage(input);
            
            ProcessImage(image);

            std::ofstream output(argv[2]);
            if (!output.is_open())
            {
                throw std::invalid_argument(ERROR);
            }
            PrintImage(image, output);
        }
        else
        {
            image = ReadImage(std::cin);
            ProcessImage(image);
            PrintImage(image, std::cout);
        }
    }
    catch (const std::exception& error)
    {
        std::cout << "ERROR" << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}