#pragma once
#include <iostream>
#include <exception>
#include <fstream>
#pragma warning(disable:4996)

namespace CONSTANTS {
	constexpr size_t MAX_LENGTH = 1024;
	constexpr size_t BEG_CAPACITY = 4;
	constexpr size_t RES_FACTOR = 2;
}

class MyString {
private:
	char* string;
	size_t size;
	size_t capacity;

	size_t roundToPowerOfTwo(size_t num);
	void copyDynamicMemory(const MyString& other);
	void freeDynamicMemory();
	void resize(size_t newCapacity);
	void shiftRight(size_t index, size_t length);
	void addString(size_t length, const char* str);

public:
	MyString();
	MyString(const char* string);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	void reserve(size_t newCapacity);
	void shrink_to_fit();
	void clear();

	void push_back(char ch);
	void pop_back();
	bool empty() const;

	size_t getSize() const;
	size_t getCapacity() const;
	const char* c_str() const;
	MyString substr(unsigned startIndex, unsigned len) const;

	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	char& at(size_t index);
	const char& at(size_t index) const;

	MyString& operator+=(const MyString& other);

	MyString& append(size_t count, char ch);
	MyString& append(const char* str);

	MyString& insert(size_t index, const char* str);
	MyString& insert(size_t index, size_t count, char ch);
	MyString& erase(size_t index, size_t count);
	void swap(MyString& other);

	friend std::ostream& operator<<(std::ostream& os, const MyString& object);
	friend std::istream& operator>>(std::istream& is, MyString& object);
};

MyString operator+(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);


