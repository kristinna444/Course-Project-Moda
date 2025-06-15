#include "Mailbox.h"

void Mailbox::freeDynamicMemory()
{
	delete[] messages;
}

void Mailbox::copyDynamicMemory(const Mailbox& other)
{
	size = other.size;
	messages = new MyString[size];
	for (size_t i = 0; i < size; i++) {
		messages[i] = other.messages[i];
	}
}

Mailbox::Mailbox(const char* fileName): messages(nullptr), size(0)
{
	std::ifstream messageFile(fileName); 
	if (!messageFile.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	int currentPosition = messageFile.tellg();

	size_t size = Utils::getCharOccurences(messageFile, '\n');
	MyString* temp = new MyString[size]; 

	messageFile.clear(); 
	messageFile.seekg(0, currentPosition); 

	for (size_t i = 0; i < size; i++) { 
		char buffer[CONSTANTS::MAX_LENGTH]; 
		messageFile.getline(buffer, CONSTANTS::MAX_LENGTH); 
		temp[i] = MyString(buffer); 
	}

	messageFile.close(); 

	delete[] messages; 
	messages = temp;
	this->size = size;
}

Mailbox::Mailbox(const Mailbox& other)
{
	copyDynamicMemory(other);
}

Mailbox& Mailbox::operator=(const Mailbox& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

size_t Mailbox::getSize() const
{
	return size; 
}

const MyString& Mailbox::operator[](size_t index) const
{
	return messages[index];
}

Mailbox::~Mailbox()
{
	freeDynamicMemory();
}