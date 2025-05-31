#include <iostream>
#include "StringList.h"
#include <utility>
#include <stdexcept>

StringList::StringList()
{
}

StringList::StringList(const StringList& other)
{
    CopyFrom(other);
}

StringList::StringList(StringList&& other) noexcept
{
    Swap(other);
}

StringList::~StringList() noexcept
{
    ClearNodes();
}

StringList& StringList::operator=(StringList other) noexcept
{
    Swap(other);
    return *this;
}

void StringList::PushBack(const std::string& value)
{
    PushBack(std::string(value));
}

void StringList::PushBack(std::string&& value)
{
    Node* node = new Node(std::move(value));
    node->prev = m_tail;
    if (m_tail)
    {
        m_tail->next = node;
    }
    else
    {
        m_head = node;
    }
    m_tail = node;
    ++m_size;
}

void StringList::PushFront(const std::string& value)
{
    PushFront(std::string(value));
}

void StringList::PushFront(std::string&& value)
{
    Node* node = new Node(std::move(value));
    node->next = m_head;
    if (m_head)
    {
        m_head->prev = node;
    }
    else
    {
        m_tail = node;
    }
    m_head = node;
    ++m_size;
}

void StringList::Clear() noexcept
{
    ClearNodes();
}

bool StringList::IsEmpty() const noexcept
{
    return m_size == 0;
}

size_t StringList::GetSize() const noexcept
{
    return m_size;
}

void StringList::CopyFrom(const StringList& other)
{
    ClearNodes();
    for (Node* node = other.m_head; node; node = node->next)
    {
        PushBack(node->value);
    }
}

void StringList::Swap(StringList& other) noexcept
{
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_size, other.m_size);
}

void StringList::ClearNodes() noexcept
{
    Node* node = m_head;
    while (node)
    {
        Node* next = node->next;
        delete node;
        node = next;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

Node* StringList::GetHead() const noexcept
{ 
    return m_head; 
}

Node* StringList::GetTail() const noexcept
{ 
    return m_tail; 
}

StringList::Iterator StringList::begin() noexcept
{
    return Iterator(m_head, this);
}

StringList::Iterator StringList::end() noexcept
{
    return Iterator(nullptr, this);
}

StringList::ConstIterator StringList::begin() const noexcept
{
    return ConstIterator(m_head, this);
}

StringList::ConstIterator StringList::end() const noexcept
{
    return ConstIterator(nullptr, this);
}

StringList::ConstIterator StringList::cbegin() const noexcept
{
    return ConstIterator(m_head, this);
}

StringList::ConstIterator StringList::cend() const noexcept
{
    return ConstIterator(nullptr, this);
}

StringList::reverse_iterator StringList::rbegin() noexcept
{
    return reverse_iterator(end());
}

StringList::reverse_iterator StringList::rend() noexcept
{
    return reverse_iterator(begin());
}

StringList::const_reverse_iterator StringList::rbegin() const noexcept
{
    return const_reverse_iterator(end());
}

StringList::const_reverse_iterator StringList::rend() const noexcept
{
    return const_reverse_iterator(begin());
}

StringList::const_reverse_iterator StringList::crbegin() const noexcept
{
    return const_reverse_iterator(cend());
}

StringList::const_reverse_iterator StringList::crend() const noexcept
{
    return const_reverse_iterator(cbegin());
}

StringList::Iterator StringList::Insert(Iterator pos, const std::string& value)
{
    return Insert(pos, std::string(value));
}

StringList::Iterator StringList::Insert(Iterator pos, std::string&& value)
{
    Node* posNode = pos.m_node;
    Node* newNode = new Node(std::move(value));
    newNode->next = posNode;
    if (posNode)
    {
        newNode->prev = posNode->prev;
        if (posNode->prev)
        {
            posNode->prev->next = newNode;
        }
        else
        {
            m_head = newNode;
        }
        posNode->prev = newNode;
    }
    else
    {
        newNode->prev = m_tail;
        if (m_tail)
        {
            m_tail->next = newNode;
        }
        else
        {
            m_head = newNode;
        }
        m_tail = newNode;
    }
    ++m_size;
    return Iterator(newNode, this);
}

StringList::Iterator StringList::Erase(Iterator pos) noexcept
{
    Node* node = pos.m_node;
    if (!node)
    {
        return end();
    }
    Node* next = node->next;
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        m_head = node->next;
    }
    if (node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        m_tail = node->prev;
    }
    delete node;
    --m_size;
    return Iterator(next, this);
}
