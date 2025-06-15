#pragma once

#include "../MyString.h"
#include "../Utils.h"

class Mailbox 
{
private:
	MyString* messages;
	size_t size;

	void freeDynamicMemory();
	void copyDynamicMemory(const Mailbox& other);

public:
	Mailbox(const char* fileName);
	Mailbox(const Mailbox& other);
	Mailbox& operator=(const Mailbox& other);

	size_t getSize() const;
	const MyString& operator[](size_t index) const;

	~Mailbox();
};
