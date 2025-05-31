#pragma once
#include <string>
#include <iterator>
#include <cstddef>
#include <type_traits>
#include "Node.h"

class StringList;

template<bool IsConst>
class StringListIteratorT
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::string;
    using difference_type = std::ptrdiff_t;
    using pointer = std::conditional_t<IsConst, const value_type*, value_type*>;
    using reference = std::conditional_t<IsConst, const value_type&, value_type&>;

    using NodeType = Node;
    using NodePtr = std::conditional_t<IsConst, const NodeType*, NodeType*>;
    using ListPtr = std::conditional_t<IsConst, const StringList*, StringList*>;

private:
    NodePtr m_node = nullptr;
    ListPtr m_list = nullptr;

public:
    StringListIteratorT() = default;
    explicit StringListIteratorT(NodePtr node, ListPtr list = nullptr) : m_node(node), m_list(list) {}

    template<bool B = IsConst, std::enable_if_t<B, int> = 0>
    StringListIteratorT(const StringListIteratorT<false>& other) : m_node(other.m_node), m_list(other.m_list) {}

    reference operator*() const 
    { 
        if (!m_node) 
        {
            static value_type empty_value;
            return empty_value;
        }
        return m_node->value; 
    }
    
    pointer operator->() const 
    { 
        if (!m_node) 
        {
            static value_type empty_value;
            return &empty_value;
        }
        return &m_node->value; 
    }
    
    StringListIteratorT& operator++() 
    { 
        if (m_node) 
        {
            m_node = m_node->next;
        }
        return *this; 
    }
    
    StringListIteratorT operator++(int) 
    { 
        StringListIteratorT tmp = *this; 
        ++(*this); 
        return tmp; 
    }
    
    StringListIteratorT& operator--() 
    { 
        if (m_node) 
        {
            m_node = m_node->prev;
        }
        else if (m_list) 
        {
            m_node = static_cast<NodePtr>(m_list->GetTail());
        }
        return *this; 
    }
    
    StringListIteratorT operator--(int) 
    { 
        StringListIteratorT tmp = *this; 
        --(*this); 
        return tmp; 
    }
    
    bool operator==(const StringListIteratorT& other) const 
    { 
        return m_node == other.m_node; 
    }
    
    bool operator!=(const StringListIteratorT& other) const 
    { 
        return m_node != other.m_node; 
    }

    template<bool> friend class StringListIteratorT;
    friend class StringList;
};

using StringListIterator = StringListIteratorT<false>;
using StringListConstIterator = StringListIteratorT<true>;