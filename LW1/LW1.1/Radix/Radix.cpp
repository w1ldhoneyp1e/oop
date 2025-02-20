#include <algorithm>
#include <cctype>
#include <climits>
#include <iostream>
#include <string>

const int MAX_RADIX = 36;
const int MIN_RADIX = 2;
const int DECIMAL_RADIX = 10;

int CharToDigit(char c, bool& wasError)
{
	if (c >= '0' && c <= '9')
	{
		return c - '0';
	}
	else if (c >= 'A' && c <= 'Z')
	{
		return c - 'A' + DECIMAL_RADIX;
	}
	else
	{
		wasError = true;
		return 0;
	}
}

char DigitToChar(int remainder, bool& wasError)
{
	if (remainder < DECIMAL_RADIX)
	{
		return '0' + remainder;
	}
	else
	{
		return 'A' + (remainder - DECIMAL_RADIX);
	}
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		wasError = true;
		return 0;
	}

	if (str.empty())
	{
		wasError = true;
		return 0;
	}

	int result = 0;
	bool isNegative = (str[0] == '-');
	size_t startPos = isNegative ? 1 : 0;

	for (size_t i = startPos; i < str.length(); ++i)
	{
		char c = std::toupper(str[i]);
		int digit = CharToDigit(c, wasError);

		if (digit >= radix)
		{
			wasError = true;
			return 0;
		}

		if (result > (INT_MAX - digit) / radix)
		{
			wasError = true;
			return 0;
		}

		result = result * radix + digit;
	}

	if (isNegative)
	{
		result = -result;
	}

	return result;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		wasError = true;
		return "";
	}

	if (n == 0)
	{
		return "0";
	}

	bool isNegative = (n < 0);
	int number = n < 0 ? -n : n;
	std::string result;

	while (number != 0)
	{
		char ch = DigitToChar(number % radix, wasError);

		result += ch;
		number /= radix;
	}

	if (isNegative)
	{
		result += "-";
	}

	std::reverse(result.begin(), result.end());

	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Error: Invalid number of arguments\n";
		std::cout << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	bool wasError = false;
	int sourceRadix = StringToInt(argv[1], DECIMAL_RADIX, wasError);
	int destRadix = StringToInt(argv[2], DECIMAL_RADIX, wasError);

	int number = StringToInt(argv[3], sourceRadix, wasError);

	std::string result = IntToString(number, destRadix, wasError);
	if (wasError)
	{
		std::cout << "ERROR\n";
		return 1;
	}

	std::cout << result << "\n";
	return 0;
}
