#pragma once
#include <string>
#include <iterator>
#include <memory>
#include <cstddef>

template<bool IsConst>
class StringListIteratorT;

using StringListIterator = StringListIteratorT<false>;
using StringListConstIterator = StringListIteratorT<true>;

class StringList
{
private:
	struct Node {
		std::string value;
		Node* prev = nullptr;
		Node* next = nullptr;
		
		Node() = default;
		Node(const std::string& val) : value(val) {}
		Node(std::string&& val) : value(std::move(val)) {}
	};

public:
	template<bool IsConst>
	friend class StringListIteratorT;

	using ValueType = std::string;

private:
	Node* m_head = nullptr;
	Node* m_tail = nullptr;
	size_t m_size = 0;

	void CopyFrom(const StringList& other);
	void Swap(StringList& other) noexcept;
	void ClearNodes() noexcept;

	Node* GetHead() const noexcept;

public:
	Node* GetTail() const noexcept;

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

	using Iterator = StringListIterator;
	using ConstIterator = StringListConstIterator;
	Iterator begin() noexcept;
	Iterator end() noexcept;
	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;
	ConstIterator cbegin() const noexcept;
	ConstIterator cend() const noexcept;

	using reverse_iterator = std::reverse_iterator<Iterator>;
	using const_reverse_iterator = std::reverse_iterator<ConstIterator>;
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