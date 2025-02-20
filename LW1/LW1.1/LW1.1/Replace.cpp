#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

int ExitWithError(int code = 1)
{
	std::cout << "ERROR\n";
	return code;
}

void PrintUsage()
{
	std::cout << "Usage: replace <input file> <output file> <search string> <replacement string>\n";
}

std::string ReplaceString(
	const std::string& subject,
	const std::string& searchString,
	const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;

	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		if (foundPos == std::string::npos)
		{
			result.append(subject, pos, subject.length());
			break;
		}
		result.append(subject, pos, foundPos - pos);
		result.append(replacementString);

		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyStreamWithReplacement(
	std::istream& input, 
	std::ostream& output,
	const std::string& searchString, 
	const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

int CopyFileWithReplacement(
	const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& search,
	const std::string& replace)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		return ExitWithError();
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		return ExitWithError();
	}

	CopyStreamWithReplacement(inputFile, outputFile, search, replace);
	outputFile.flush();

	return EXIT_SUCCESS;
}

int HandleConsoleInput()
{
	std::string search, replace;

	if (!std::getline(std::cin, search) || !std::getline(std::cin, replace))
	{
		return ExitWithError(EXIT_SUCCESS);
	}

	std::vector<std::string> text;
	std::string line;
	while (std::getline(std::cin, line))
	{
		text.push_back(line);
	}

	if (text.empty())
	{
		return ExitWithError(EXIT_SUCCESS);
	}

	for (auto& line : text)
	{
		std::cout << ReplaceString(line, search, replace) << std::endl;
	}
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		return HandleConsoleInput();
	}
	else if (argc == 2 && std::string(argv[1]) == "-h")
	{
        PrintUsage();
        return EXIT_SUCCESS;
    }
	else if (argc != 5)
	{
		return ExitWithError();
	}

	return CopyFileWithReplacement(argv[1], argv[2], argv[3], argv[4]);
}
