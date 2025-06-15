#include "MyString.h"

size_t MyString::roundToPowerOfTwo(size_t num)
{
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num++;
    return num;
}

void MyString::copyDynamicMemory(const MyString& other)
{
    size = other.size;
    capacity = other.capacity;
    string = new char[capacity];
    strcpy(string, other.string);
}

void MyString::freeDynamicMemory()
{
    delete[] string;
}

void MyString::resize(size_t newCapacity)
{
    capacity = newCapacity;

    char* temp = new char[capacity];
    strcpy(temp, string);

    delete[] string;
    string = temp;
}

void MyString::shiftRight(size_t index, size_t length)
{
    size_t totalSize = size + length;
    if (totalSize + 1 > capacity) {
        reserve(totalSize + 1);
    }

    for (size_t i = size + 1; i > index; i--) {
        string[i + length - 1] = string[i - 1];
    }
}

void MyString::addString(size_t length, const char* str)
{
    size_t totalSize = size + length;
    if (totalSize + 1 > capacity) {
        reserve(totalSize + 1);
    }

    for (size_t i = 0; i < length; i++) {
        string[size + i] = str[i];
    }

    size = totalSize;
    string[size] = '\0';
}

MyString::MyString() : size(0), capacity(CONSTANTS::BEG_CAPACITY)
{
    string = new char[capacity];
    string[0] = '\0';
}

MyString::MyString(const char* string)
{
    if (!string) {
        string = "";
    }

    size = strlen(string);
    capacity = roundToPowerOfTwo(size + 1);
    this->string = new char[capacity];
    strcpy(this->string, string);
}

MyString::MyString(const MyString& other)
{
    copyDynamicMemory(other);
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other) {
        freeDynamicMemory();
        copyDynamicMemory(other);
    }

    return *this;
}

MyString::~MyString()
{
    freeDynamicMemory();
}

void MyString::reserve(size_t newCapacity)
{
    if (newCapacity <= capacity) return;
    resize(newCapacity);
}

void MyString::shrink_to_fit()
{
    if (capacity == size + 1) return;
    resize(size + 1);
}

void MyString::clear()
{
    size = 0;
    string[0] = '\0';
}

void MyString::push_back(char ch)
{
    if (size + 1 == capacity) {
        reserve(capacity * CONSTANTS::RES_FACTOR);
    }

    string[size++] = ch;
    string[size] = '\0';
}

void MyString::pop_back()
{
    if (empty()) {
        throw std::out_of_range("pop_back on an empty string");
    }

    --size;
    string[size] = '\0';
}

bool MyString::empty() const
{
    return size == 0;
}

size_t MyString::getSize() const
{
    return size;
}

size_t MyString::getCapacity() const
{
    return capacity;
}

const char* MyString::c_str() const
{
    return string;
}

MyString MyString::substr(unsigned startIndex, unsigned len) const
{
    if (startIndex > size) {
        throw std::out_of_range("Substr: startIndex is out of range");
    }

    if (startIndex + len > size) {
        len = size - startIndex;
    }

    char* text = new char[len + 1];

    for (unsigned i = 0; i < len; i++) {
        text[i] = string[i + startIndex];
    }

    text[len] = '\0';

    MyString newString(text);
    delete[] text;

    return newString;
}

char& MyString::operator[](size_t index)
{
    return string[index];
}

const char& MyString::operator[](size_t index) const
{
    return string[index];
}

char& MyString::at(size_t index)
{
    if (index >= size) {
        throw std::out_of_range("index is out of range");
    }

    return string[index];
}

const char& MyString::at(size_t index) const
{
    if (index >= size) {
        throw std::out_of_range("index is out of range");
    }

    return string[index];
}

MyString& MyString::operator+=(const MyString& other)
{
    addString(other.size, other.string);

    return *this;
}

MyString& MyString::append(size_t count, char ch)
{
    size_t totalSize = size + count;
    if (totalSize + 1 > capacity) {
        reserve(totalSize + 1);
    }

    for (size_t i = 0; i < count; i++) {
        string[size + i] = ch;
    }

    size = totalSize;
    string[size] = '\0';

    return *this;
}

MyString& MyString::append(const char* str)
{
    size_t strLength = strlen(str);

    addString(strLength, str);

    return *this;
}

MyString& MyString::insert(size_t index, const char* str)
{
    if (!str) {
        throw std::logic_error("Insert: invalid input string");
    }

    if (index > size) {
        throw std::out_of_range("Insert: index is out of range");
    }

    size_t strLength = strlen(str);
    shiftRight(index, strLength);

    for (size_t i = 0; i < strLength; i++) {
        string[i + index] = str[i];
    }
    size += strLength;

    return *this;
}

MyString& MyString::insert(size_t index, size_t count, char ch)
{
    if (index > size) {
        throw std::out_of_range("Insert: index is out of range");
    }

    shiftRight(index, count);

    for (size_t i = index; i < index + count; i++) {
        string[i] = ch;
    }
    size += count;

    return *this;
}

MyString& MyString::erase(size_t index, size_t count)
{
    if (index > size) {
        throw std::out_of_range("Erase: index is out of range");
    }

    if (index + count > size) {
        count = size - index;
    }

    for (size_t i = index; i <= size - count; i++) {
        string[i] = string[i + count];
    }
    size -= count;

    return *this;
}

void MyString::swap(MyString& other)
{
    MyString temp(other);
    other = *this;
    *this = temp;
}

std::ostream& operator<<(std::ostream& os, const MyString& object)
{
    return os << object.string;
}

std::istream& operator>>(std::istream& is, MyString& object)
{
    char buffer[CONSTANTS::MAX_LENGTH];
    is.getline(buffer, CONSTANTS::MAX_LENGTH);

    object.freeDynamicMemory();

    object.size = strlen(buffer);
    object.capacity = object.roundToPowerOfTwo(object.size + 1);
    object.string = new char[object.capacity];
    strcpy(object.string, buffer);

    return is;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
    MyString newString(lhs);
    newString += rhs;
    return newString;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
    return !(lhs == rhs);
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
    return lhs > rhs || lhs == rhs;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
    return lhs < rhs || lhs == rhs;
}
