#include "CheckContainer.h"

void CheckContainer::freeDynamicMemory()
{
	delete[] checks;
}

void CheckContainer::copyDynamicMemory(const CheckContainer& other)
{
	size = other.size;
	capacity = other.capacity;

	checks = new Check[capacity];
	for (size_t i = 0; i < size; i++) {
		checks[i] = other.checks[i];
	}
}

void CheckContainer::shiftLeft(size_t index)
{
	for (size_t i = index; i < size - 1; i++) {
		checks[i] = checks[i + 1];
	}
}

CheckContainer::CheckContainer(const char* fileName): size(0), capacity(0), checks(nullptr)
{
	std::ifstream input(fileName);
	if (!input.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	int currentPosition = input.tellg();

	delete[] checks;
	size = Utils::getCharOccurences(input, '\n');

	input.clear();
	input.seekg(0, currentPosition);

	if (size == 0) {
		capacity = CONSTANTS::BEG_CAPACITY;
		checks = new Check[capacity];
	}
	else {
		capacity = Utils::roundToPowerOfTwo(size);
		checks = new Check[capacity];

		Check check;
		for (size_t i = 0; i < size; i++) {
			check.readCheckFromFile(input);
			checks[i] = check;
		}
	}

	input.close();
}

CheckContainer::CheckContainer(const CheckContainer& other)
{
	copyDynamicMemory(other);
}

CheckContainer& CheckContainer::operator=(const CheckContainer& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

bool CheckContainer::hasCheck(const MyString& code) const
{
	for (size_t i = 0; i < size; i++) {
		if (checks[i].getCode() == code) {
			return true;
		}
	}

	return false;
}

double CheckContainer::getAmountFromCheck(const MyString& code, const MyString& EGN)
{
	for (size_t i = 0; i < size; i++) {
		if (checks[i].getCode() == code && checks[i].getClientEGN() == EGN) {
			return checks[i].getAmount();
		}
	}

	std::cout << "Sorry! We couldn't find the check!" << std::endl;
	return 0;
}

void CheckContainer::deleteCheck(const MyString& code)
{
	for (size_t i = 0; i < size; i++) {
		if (checks[i].getCode() == code) {
			shiftLeft(i);
			size--;

			return;
		}
	}

	std::cout << "No check with this code!" << std::endl;
}

void CheckContainer::updateCheckList()
{
	std::ofstream output("uncashed_checks.txt");
	if (!output.is_open()) {
		throw std::runtime_error("Program couldn't open file!");
	}

	for (size_t i = 0; i < size; i++) {
		checks[i].writeCheckToFile(output);
	}

	output.close();
}

CheckContainer::~CheckContainer()
{
	freeDynamicMemory();
}