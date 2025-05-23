#include "MyString.h"

char MyString::emptyString[1] = { '\0' };

MyString::MyString()
    : m_data(emptyString)
    , m_length(0)
    , m_capacity(0)
{
}

MyString::MyString(const char* pString)
    : m_data(emptyString)
    , m_length(0)
    , m_capacity(0)
{
    if (pString)
    {
        m_length = strlen(pString);
        m_capacity = m_length + 1;
        m_data = new char[m_capacity];
        memcpy(m_data, pString, m_length);
        m_data[m_length] = '\0';
    }
}

MyString::MyString(const char* pString, size_t length)
    : m_data(emptyString)
    , m_length(0)
    , m_capacity(0)
{
    if (pString && length > 0)
    {
        m_length = length;
        m_capacity = m_length + 1;
        m_data = new char[m_capacity];
        memcpy(m_data, pString, m_length);
        m_data[m_length] = '\0';
    }
}

MyString::MyString(const MyString& other)
    : m_data(emptyString)
    , m_length(0)
    , m_capacity(0)
{
    if (other.m_length > 0)
    {
        m_length = other.m_length;
        m_capacity = m_length + 1;
        m_data = new char[m_capacity];
        memcpy(m_data, other.m_data, m_length);
        m_data[m_length] = '\0';
    }
}

MyString::MyString(MyString&& other) noexcept
    : m_data(other.m_data)
    , m_length(other.m_length)
    , m_capacity(other.m_capacity)
{
    other.m_data = emptyString;
    other.m_length = 0;
    other.m_capacity = 0;
}

MyString::MyString(const std::string& stlString)
    : m_data(emptyString)
    , m_length(0)
    , m_capacity(0)
{
    if (!stlString.empty())
    {
        m_length = stlString.length();
        m_capacity = m_length + 1;
        m_data = new char[m_capacity];
        memcpy(m_data, stlString.c_str(), m_length);
        m_data[m_length] = '\0';
    }
}

MyString::~MyString()
{
    if (m_data != emptyString)
    {
        delete[] m_data;
    }
}

size_t MyString::GetLength() const
{
    return m_length;
}

const char* MyString::GetStringData() const
{
    return m_data;
}

MyString MyString::SubString(size_t start, size_t length) const
{
    if (start >= m_length)
    {
        return MyString();
    }

    length = std::min(length, m_length - start);
    return MyString(m_data + start, length);
}

void MyString::Clear()
{
    if (m_data != emptyString)
    {
        delete[] m_data;
        m_data = emptyString;
    }
    m_length = 0;
    m_capacity = 0;
}

size_t MyString::GetCapacity() const
{
    return m_capacity;
}

void MyString::Reallocate(size_t newCapacity)
{
    if (newCapacity <= m_capacity)
    {
        return;
    }

    char* newData = new char[newCapacity];
    if (m_length > 0)
    {
        memcpy(newData, m_data, m_length);
    }
    newData[m_length] = '\0';

    if (m_data != emptyString)
    {
        delete[] m_data;
    }

    m_data = newData;
    m_capacity = newCapacity;
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other)
    {
        if (other.m_length == 0)
        {
            Clear();
        }
        else
        {
            if (m_capacity <= other.m_length)
            {
                if (m_data != emptyString)
                {
                    delete[] m_data;
                }
                m_capacity = other.m_length + 1;
                m_data = new char[m_capacity];
            }
            m_length = other.m_length;
            memcpy(m_data, other.m_data, m_length);
            m_data[m_length] = '\0';
        }
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
    if (this != &other)
    {
        if (m_data != emptyString)
        {
            delete[] m_data;
        }

        m_data = other.m_data;
        m_length = other.m_length;
        m_capacity = other.m_capacity;

        other.m_data = emptyString;
        other.m_length = 0;
        other.m_capacity = 0;
    }
    return *this;
}

MyString MyString::operator+(const MyString& other) const
{
    if (other.m_length == 0)
    {
        return *this;
    }
    if (m_length == 0)
    {
        return other;
    }

    MyString result;
    result.m_length = m_length + other.m_length;
    result.m_capacity = result.m_length + 1;
    result.m_data = new char[result.m_capacity];

    memcpy(result.m_data, m_data, m_length);
    memcpy(result.m_data + m_length, other.m_data, other.m_length);
    result.m_data[result.m_length] = '\0';

    return result;
}

MyString operator+(const std::string& lhs, const MyString& rhs)
{
    return MyString(lhs) + rhs;
}

MyString operator+(const char* lhs, const MyString& rhs)
{
    return MyString(lhs) + rhs;
}

MyString& MyString::operator+=(const MyString& other)
{
    if (other.m_length > 0)
    {
        size_t newLength = m_length + other.m_length;
        if (newLength >= m_capacity)
        {
            size_t newCapacity = std::max(newLength + 1, m_capacity * 2);
            Reallocate(newCapacity);
        }

        memcpy(m_data + m_length, other.m_data, other.m_length);
        m_length = newLength;
        m_data[m_length] = '\0';
    }
    return *this;
}

bool MyString::operator==(const MyString& other) const
{
    if (m_length != other.m_length)
    {
        return false;
    }
    return memcmp(m_data, other.m_data, m_length) == 0;
}

bool MyString::operator!=(const MyString& other) const
{
    return !(*this == other);
}

bool MyString::operator<(const MyString& other) const
{
    size_t minLength = std::min(m_length, other.m_length);
    int result = memcmp(m_data, other.m_data, minLength);
    if (result != 0)
    {
        return result < 0;
    }
    return m_length < other.m_length;
}

bool MyString::operator>(const MyString& other) const
{
    return other < *this;
}

bool MyString::operator<=(const MyString& other) const
{
    return !(other < *this);
}

bool MyString::operator>=(const MyString& other) const
{
    return !(*this < other);
}

char& MyString::operator[](size_t index)
{
    if (index >= m_length) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

const char& MyString::operator[](size_t index) const
{
    if (index >= m_length) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
    return os.write(str.GetStringData(), str.GetLength());
}

std::istream& operator>>(std::istream& is, MyString& str)
{
    str.Clear();
    char ch;
    while (is.get(ch) && !isspace(static_cast<unsigned char>(ch)))
    {
        if (str.m_length == str.m_capacity)
        {
            size_t newCapacity = std::max(str.m_length + 1, str.m_capacity * 2);
            str.Reallocate(newCapacity);
        }
        str.m_data[str.m_length++] = ch;
    }
    
    if (str.m_capacity > 0 && str.m_length > 0)
    {
        str.m_data[str.m_length] = '\0';
    }

    return is;
}

char* MyString::begin() 
{ 
    return m_data; 
}

char* MyString::end() 
{ 
    return m_data + m_length; 
}
const char* MyString::begin() const 
{
    return m_data; 
}

const char* MyString::end() const 
{ 
    return m_data + m_length; 
}

const char* MyString::cbegin() const 
{ 
    return m_data; 
}

const char* MyString::cend() const 
{ 
    return m_data + m_length; 
}

std::reverse_iterator<char*> MyString::rbegin() 
{ 
    return std::reverse_iterator<char*>(end()); 
}

std::reverse_iterator<char*> MyString::rend() 
{ 
    return std::reverse_iterator<char*>(begin()); 
}

std::reverse_iterator<const char*> MyString::rbegin() const 
{ 
    return std::reverse_iterator<const char*>(end()); 
}

std::reverse_iterator<const char*> MyString::rend() const 
{ 
    return std::reverse_iterator<const char*>(begin()); 
}

std::reverse_iterator<const char*> MyString::crbegin() const 
{ 
    return std::reverse_iterator<const char*>(cend()); 
}

std::reverse_iterator<const char*> MyString::crend() const 
{ 
    return std::reverse_iterator<const char*>(cbegin()); 
}
