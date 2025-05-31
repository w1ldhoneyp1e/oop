#pragma once
#include <string>

struct Node {
    std::string value;
    Node* prev = nullptr;
    Node* next = nullptr;
    
    Node() = default;
    Node(const std::string& val) : value(val) {}
    Node(std::string&& val) : value(std::move(val)) {}
}; 