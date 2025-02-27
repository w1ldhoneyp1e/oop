#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>

const int MATRIX_SIZE = 3;

const std::string INVALID_MATRIX_FORMAT = "Invalid matrix format";
const std::string INVALID_MATRIX = "Invalid matrix";

using Matrix = std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>;

int ExitWithError(int code = 1)
{
	std::cout << "ERROR\n";
	return code;
}

void PrintUsage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "  invert.exe [input file]" << std::endl;
    std::cout << "  invert.exe -h" << std::endl;
    std::cout << std::endl;
    std::cout << "Parameters:" << std::endl;
    std::cout << "  input file    - file with 3x3 matrix" << std::endl;
    std::cout << "  -h              - show this help" << std::endl;
    std::cout << std::endl;
    std::cout << "If file is not specified, matrix is read from stdin" << std::endl;
}

double CalculateMinor(const Matrix& matrix, size_t row, size_t col)
{
    std::vector<double> elements;
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        if (i == row) continue;
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            if (j == col) continue;
            elements.push_back(matrix[i][j]);
        }
    }
    return elements[0] * elements[3] - elements[1] * elements[2];
}

double CalculateDeterminant(const Matrix& matrix)
{
    double det = 0;
    for (size_t j = 0; j < MATRIX_SIZE; j++)
    {
        det += matrix[0][j] * ((j % 2 == 0) ? 1 : -1) * CalculateMinor(matrix, 0, j);
    }
    return det;
}

void CalculateAdjugateMatrix(const Matrix& input, Matrix& output, double det)
{
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            double minor = CalculateMinor(input, i, j);
            output[j][i] = ((i + j) % 2 == 0 || minor == 0 ? 1 : -1) * minor / det;
        }
    }
}

bool InvertMatrix(const Matrix& input, Matrix& output) // Выделил из InvertMatrix - CalculateAdjugateMatrix
{
    double det = CalculateDeterminant(input);
    
    if (det == 0)
        return false;

    CalculateAdjugateMatrix(input, output, det);
    return true;
}

Matrix ReadMatrix(std::istream& input)
{
    Matrix matrix;
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            if (!(input >> matrix[i][j])) {
                throw input.eof() 
                    ? INVALID_MATRIX_FORMAT
                    : INVALID_MATRIX;
            }
        }
    }
    
    double extra;
    if (input >> extra)
        throw INVALID_MATRIX_FORMAT;
        
    return matrix;
}

void PrintMatrix(const Matrix& matrix)
{
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            std::cout << std::fixed << std::setprecision(3) << matrix[i][j];
            if (j < MATRIX_SIZE - 1)
                std::cout << "\t";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc > 2)
    {
        PrintUsage();
        return ExitWithError();
    }

    if (argc == 2 && std::string(argv[1]) == "-h")
    {
        PrintUsage();
        return EXIT_SUCCESS;
    }

    Matrix inputMatrix;
    try
    {
        if (argc == 2)
        {
            std::ifstream inputFile(argv[1]);
            if (!inputFile.is_open())
            {
                return ExitWithError();
            }
            inputMatrix = ReadMatrix(inputFile);
        }
        else
        {
            inputMatrix = ReadMatrix(std::cin);
        }
    }
    catch (const std::string& error)
    {
        std::cout << error << std::endl;
        return EXIT_SUCCESS;
    }

    Matrix outputMatrix;
    
    if (!InvertMatrix(inputMatrix, outputMatrix))
    {
        std::cout << "Non-invertible" << std::endl;
        return EXIT_SUCCESS;
    }

    PrintMatrix(outputMatrix);
    return EXIT_SUCCESS;
}