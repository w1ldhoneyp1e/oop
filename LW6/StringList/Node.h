#pragma once
#include <string>

struct Node
{
	std::string value;
	Node* prev = nullptr;
	Node* next = nullptr;

	explicit Node(std::string&& val) : value(std::move(val)) {}
}; 