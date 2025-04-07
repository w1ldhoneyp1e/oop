#pragma once
#include <set>
#include <string>
const int MAX_UPPER_BOUND = 100000000;
const std::string ERR_INVALID_ARGS = "Использование: <программа> <верхняя граница>\nВерхняя граница должна быть положительным числом, не превышающим 100000000";
const std::string ERR_OUT_OF_RANGE = "Верхняя граница должна быть положительным числом, не превышающим 100000000";

std::set<int> GeneratePrimeNumbersSet(int upperBound);
