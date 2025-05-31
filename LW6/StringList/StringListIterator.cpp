#include "StringListIterator.h"
#include "StringList.h"

template<bool IsConst>
StringListIteratorT<IsConst>::StringListIteratorT(typename StringListIteratorT<IsConst>::NodePtr node, typename StringListIteratorT<IsConst>::ListPtr list) 
    : m_node(node), m_list(list) 
{
}

template<bool IsConst>
template<bool B, std::enable_if_t<B, int>>
StringListIteratorT<IsConst>::StringListIteratorT(const StringListIteratorT<false>& other) 
    : m_node(other.m_node), m_list(other.m_list) 
{
}

template<bool IsConst>
typename StringListIteratorT<IsConst>::reference StringListIteratorT<IsConst>::operator*() const
{
    if (!m_node)
    {
        static value_type empty_value;
        return empty_value;
    }
    return m_node->value;
}

template<bool IsConst>
typename StringListIteratorT<IsConst>::pointer StringListIteratorT<IsConst>::operator->() const
{
    if (!m_node)
    {
        static value_type empty_value;
        return &empty_value;
    }
    return &m_node->value;
}

template<bool IsConst>
StringListIteratorT<IsConst>& StringListIteratorT<IsConst>::operator++()
{
    if (m_node)
    {
        m_node = m_node->next;
    }
    return *this;
}

template<bool IsConst>
StringListIteratorT<IsConst> StringListIteratorT<IsConst>::operator++(int)
{
    StringListIteratorT tmp = *this;
    ++(*this);
    return tmp;
}

template<bool IsConst>
StringListIteratorT<IsConst>& StringListIteratorT<IsConst>::operator--()
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

template<bool IsConst>
StringListIteratorT<IsConst> StringListIteratorT<IsConst>::operator--(int)
{
    StringListIteratorT tmp = *this;
    --(*this);
    return tmp;
}

template<bool IsConst>
bool StringListIteratorT<IsConst>::operator==(const StringListIteratorT& other) const
{
    return m_node == other.m_node;
}

template<bool IsConst>
bool StringListIteratorT<IsConst>::operator!=(const StringListIteratorT& other) const
{
    return m_node != other.m_node;
}

template class StringListIteratorT<false>;
template class StringListIteratorT<true>;

template StringListIteratorT<true>::StringListIteratorT(const StringListIteratorT<false>&);