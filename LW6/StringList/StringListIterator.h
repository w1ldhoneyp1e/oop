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
    explicit StringListIteratorT(NodePtr node, ListPtr list = nullptr);

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

    template<bool> friend class StringListIteratorT;
    friend class StringList;
};

using StringListIterator = StringListIteratorT<false>;
using StringListConstIterator = StringListIteratorT<true>;