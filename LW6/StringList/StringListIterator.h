#pragma once
#include <iterator>
#include <cstddef>
#include <type_traits>
#include "Node.h"

class StringList;

template<bool IsConst>
class StringListIteratorT
{
    friend class StringList;

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::string;
    using difference_type = std::ptrdiff_t;
    using pointer = std::conditional_t<IsConst, const value_type*, value_type*>;
    using reference = std::conditional_t<IsConst, const value_type&, value_type&>;
    using NodePtr = std::conditional_t<IsConst, const Node*, Node*>;
    using ListPtr = std::conditional_t<IsConst, const StringList*, StringList*>;

private:
    NodePtr m_node;
    ListPtr m_list;

    template<bool> friend class StringListIteratorT;

public:
    StringListIteratorT() : m_node(nullptr), m_list(nullptr) {}
    explicit StringListIteratorT(NodePtr node, ListPtr list);

    template<bool B = IsConst, std::enable_if_t<B, int> = 0>
    StringListIteratorT(const StringListIteratorT<false>& other);

    reference operator*() const;
    pointer operator->() const;
    StringListIteratorT& operator++();
    StringListIteratorT operator++(int);
    StringListIteratorT& operator--();
    StringListIteratorT operator--(int);
    bool operator==(const StringListIteratorT& other) const;
    bool operator!=(const StringListIteratorT& other) const;
};

using StringListIterator = StringListIteratorT<false>;
using StringListConstIterator = StringListIteratorT<true>;