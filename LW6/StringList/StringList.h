#pragma once
#include <string>
#include <iterator>
#include <memory>
#include <cstddef>
#include "Node.h"

template<bool IsConst>
class StringListIteratorT;

class StringList
{
public:
	using ValueType = std::string;
	using Iterator = StringListIteratorT<false>;
	using ConstIterator = StringListIteratorT<true>;
	using reverse_iterator = std::reverse_iterator<Iterator>;
	using const_reverse_iterator = std::reverse_iterator<ConstIterator>;

private:
	friend class StringListIteratorT<false>;
	friend class StringListIteratorT<true>;

	Node* m_head = nullptr;
	Node* m_tail = nullptr;
	size_t m_size = 0;

	void CopyFrom(const StringList& other);
	void Swap(StringList& other) noexcept;
	void ClearNodes() noexcept;

	Node* GetHead() const noexcept;
	Node* GetTail() const noexcept;

public:
	StringList();
	StringList(const StringList& other);
	StringList(StringList&& other) noexcept;
	~StringList() noexcept;

	StringList& operator=(StringList other) noexcept;

	void PushBack(const std::string& value);
	void PushBack(std::string&& value);
	void PushFront(const std::string& value);
	void PushFront(std::string&& value);

	void Clear() noexcept;
	bool IsEmpty() const noexcept;
	size_t GetSize() const noexcept;

	Iterator begin() noexcept;
	Iterator end() noexcept;
	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;
	ConstIterator cbegin() const noexcept;
	ConstIterator cend() const noexcept;

	reverse_iterator rbegin() noexcept;
	reverse_iterator rend() noexcept;
	const_reverse_iterator rbegin() const noexcept;
	const_reverse_iterator rend() const noexcept;
	const_reverse_iterator crbegin() const noexcept;
	const_reverse_iterator crend() const noexcept;

	Iterator Insert(Iterator pos, const std::string& value);
	Iterator Insert(Iterator pos, std::string&& value);
	Iterator Erase(Iterator pos) noexcept;
};

using StringListIterator = StringListIteratorT<false>;
using StringListConstIterator = StringListIteratorT<true>;