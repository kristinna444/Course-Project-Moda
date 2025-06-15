#pragma once

#include "Check.h"
#include "../Utils.h"

class CheckContainer
{
private:
	Check* checks;
	size_t size;
	size_t capacity;

	void freeDynamicMemory();
	void copyDynamicMemory(const CheckContainer& other);
	void shiftLeft(size_t index);
	
public:
	CheckContainer(const char* fileName);
	CheckContainer(const CheckContainer& other);
	CheckContainer& operator=(const CheckContainer& other);

	bool hasCheck(const MyString& code) const;
	double getAmountFromCheck(const MyString& code, const MyString& EGN);
	void deleteCheck(const MyString& code);
	void updateCheckList();

	~CheckContainer();
};
