#pragma once
#include <stdexcept>
#include <iterator>
#include <utility>

template <typename T>
class MyArray
{
public:
	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	MyArray() noexcept;
	MyArray(const MyArray& other);
	MyArray(MyArray&& other) noexcept;
	~MyArray() noexcept;

	MyArray& operator=(const MyArray& other);
	MyArray& operator=(MyArray&& other) noexcept;

	template <typename U>
	MyArray& operator=(const MyArray<U>& other);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	void PushBack(const T& value);
	void PushBack(T&& value);

	void Resize(size_t newSize);
	void Clear() noexcept;

	size_t GetSize() const noexcept;
	size_t GetCapacity() const noexcept;
	bool IsEmpty() const noexcept;

	iterator begin() noexcept;
	iterator end() noexcept;

	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;
	const_iterator cbegin() const noexcept;
	const_iterator cend() const noexcept;

	reverse_iterator rbegin() noexcept;
	reverse_iterator rend() noexcept;

	const_reverse_iterator rbegin() const noexcept;
	const_reverse_iterator rend() const noexcept;
	const_reverse_iterator crbegin() const noexcept;
	const_reverse_iterator crend() const noexcept;

private:
	void Reserve(size_t newCapacity);
	void Swap(MyArray& other) noexcept;

	T* m_data;
	size_t m_size;
	size_t m_capacity;
};

template <typename T>
MyArray<T>::MyArray() noexcept
	: m_data(nullptr)
	, m_size(0)
	, m_capacity(0)
{
}

template <typename T>
MyArray<T>::MyArray(const MyArray& other)
	: m_data(nullptr)
	, m_size(0)
	, m_capacity(0)
{
	if (other.IsEmpty())
	{
		return;
	}
    
	T* newData = new T[other.m_size];
	try
	{
		for (size_t i = 0; i < other.m_size; ++i)
		{
			newData[i] = other.m_data[i];
		}
	}
	catch (...)
	{
		delete[] newData;
		throw;
	}
	m_data = newData;
	m_size = other.m_size;
	m_capacity = other.m_size;
}

template <typename T>
MyArray<T>::MyArray(MyArray&& other) noexcept
	: m_data(other.m_data)
	, m_size(other.m_size)
	, m_capacity(other.m_capacity)
{
	other.m_data = nullptr;
	other.m_size = 0;
	other.m_capacity = 0;
}

template <typename T>
MyArray<T>::~MyArray() noexcept
{
	Clear();
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(const MyArray& other)
{
	if (this != &other)
	{
		MyArray temp(other);
		Swap(temp);
	}
	return *this;
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(MyArray&& other) noexcept
{
	if (this != &other)
	{
		Clear(); 

		m_data = other.m_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}
	return *this;
}

template <typename T>
template <typename U>
MyArray<T>& MyArray<T>::operator=(const MyArray<U>& other)
{
	MyArray<T> temp;
	temp.Reserve(other.GetSize());
	for (size_t i = 0; i < other.GetSize(); ++i)
	{
		temp.PushBack(static_cast<T>(other[i]));
	}
	Swap(temp);
	return *this;
}

template <typename T>
T& MyArray<T>::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[index];
}

template <typename T>
const T& MyArray<T>::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[index];
}

template <typename T>
void MyArray<T>::PushBack(const T& value)
{
	if (m_size == m_capacity)
	{
		Reserve(m_capacity == 0 ? 1 : m_capacity * 2);
	}
	m_data[m_size] = value;
	++m_size;
}

template <typename T>
void MyArray<T>::PushBack(T&& value)
{
	if (m_size == m_capacity)
	{
		Reserve(m_capacity == 0 ? 1 : m_capacity * 2);
	}
	m_data[m_size] = std::move(value);
	++m_size;
}

template <typename T>
void MyArray<T>::Resize(size_t newSize)
{
	if (newSize > m_capacity)
	{
		Reserve(newSize);
	}

	if (newSize > m_size)
	{
		for (size_t i = m_size; i < newSize; ++i)
		{
			m_data[i] = T();
		}
	}

	m_size = newSize;
}

template <typename T>
void MyArray<T>::Clear() noexcept
{
	delete[] m_data;
	m_data = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template <typename T>
size_t MyArray<T>::GetSize() const noexcept
{
	return m_size;
}

template <typename T>
size_t MyArray<T>::GetCapacity() const noexcept
{
	return m_capacity;
}

template <typename T>
bool MyArray<T>::IsEmpty() const noexcept
{
	return m_size == 0;
}

template <typename T>
void MyArray<T>::Reserve(size_t newCapacity)
{
	if (newCapacity <= m_capacity)
	{
		return;
	}

	T* newData = new T[newCapacity];
	try
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			newData[i] = std::move(m_data[i]);
		}
	}
	catch (...)
	{
		delete[] newData;
		throw;
	}

	delete[] m_data;
	m_data = newData;
	m_capacity = newCapacity;
}

template <typename T>
void MyArray<T>::Swap(MyArray& other) noexcept
{
	std::swap(m_data, other.m_data);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}

template <typename T>
typename MyArray<T>::iterator MyArray<T>::begin() noexcept
{
	return m_data;
}

template <typename T>
typename MyArray<T>::iterator MyArray<T>::end() noexcept
{
	return m_data + m_size;
}

template <typename T>
typename MyArray<T>::const_iterator MyArray<T>::begin() const noexcept
{
	return m_data;
}

template <typename T>
typename MyArray<T>::const_iterator MyArray<T>::end() const noexcept
{
	return m_data + m_size;
}

template <typename T>
typename MyArray<T>::const_iterator MyArray<T>::cbegin() const noexcept
{
	return begin();
}

template <typename T>
typename MyArray<T>::const_iterator MyArray<T>::cend() const noexcept
{
	return end();
}

template <typename T>
typename MyArray<T>::reverse_iterator MyArray<T>::rbegin() noexcept
{
	return reverse_iterator(end());
}

template <typename T>
typename MyArray<T>::reverse_iterator MyArray<T>::rend() noexcept
{
	return reverse_iterator(begin());
}

template <typename T>
typename MyArray<T>::const_reverse_iterator MyArray<T>::rbegin() const noexcept
{
	return const_reverse_iterator(end());
}

template <typename T>
typename MyArray<T>::const_reverse_iterator MyArray<T>::rend() const noexcept
{
	return const_reverse_iterator(begin());
}

template <typename T>
typename MyArray<T>::const_reverse_iterator MyArray<T>::crbegin() const noexcept
{
	return rbegin();
}

template <typename T>
typename MyArray<T>::const_reverse_iterator MyArray<T>::crend() const noexcept
{
	return rend();
} 