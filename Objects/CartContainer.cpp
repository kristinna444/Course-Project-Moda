#include "CartContainer.h"

void CartContainer::freeDynamicMemory()
{
	delete[] carts;
}

void CartContainer::copyDynamicMemory(const CartContainer& other)
{
	size = other.size;
	capacity = other.capacity;

	carts = new Cart[capacity];
	for (size_t i = 0; i < size; i++) {
		carts[i] = other.carts[i];
	}
}

void CartContainer::resize(size_t newCapacity)
{
	capacity = newCapacity;

	Cart* temp = new Cart[capacity];

	for (size_t i = 0; i < size; i++) {
		temp[i] = carts[i];
	}

	delete[] carts;
	carts = temp;
}

void CartContainer::shiftLeft(size_t index)
{
	for (size_t i = index; i < size - 1; i++) {
		carts[i] = carts[i + 1];
	}
}

CartContainer::CartContainer(): size(0), capacity(CONSTANTS::BEG_CAPACITY)
{
	carts = new Cart[capacity];
}

CartContainer::CartContainer(const CartContainer& other)
{
	copyDynamicMemory(other);
}

CartContainer& CartContainer::operator=(const CartContainer& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

Cart* CartContainer::getCart(const MyString& clientName)
{
	for (size_t i = 0; i < size; i++) {
		if (carts[i].getClientName() == clientName) {
			return &carts[i];
		}
	}

	return nullptr;
}

void CartContainer::addCart(const Cart& newCart)
{
	if (size == capacity) {
		resize(capacity * CONSTANTS::RES_FACTOR);
	}
	
	carts[size++] = newCart;

}

void CartContainer::removeCart(const MyString& clientName)
{
	for (size_t i = 0; i < size; i++) {
		if (carts[i].getClientName() == clientName) {
			shiftLeft(i);
			size--;

			return;
		}
	}

	std::cout << "We couldn't find card!" << std::endl;
}

void CartContainer::load()
{
	readFromFile("carts.txt");
}

void CartContainer::readFromFile(const char* fileName)
{
	std::ifstream input(fileName);

	if (!input.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	int currentPosition = input.tellg();

	delete[] carts;
	size = Utils::getCharOccurences(input, '\n'); 

	input.clear();
	input.seekg(0, currentPosition); 

	if (size == 0) {
		capacity = CONSTANTS::BEG_CAPACITY;
		carts = new Cart[capacity];
	}
	else {
		capacity = Utils::roundToPowerOfTwo(size);
		carts = new Cart[capacity];

		Cart newCart;
		for (size_t i = 0; i < size; i++) {
			char buffer[CONSTANTS::MAX_LENGTH];
			input.getline(buffer, CONSTANTS::MAX_LENGTH);

			std::stringstream ss(buffer);

			newCart.readFromFile(ss);
			carts[i] = newCart;
		}
	}

	input.close();
}

void CartContainer::updateFileWithCarts() const
{
	std::ofstream file("carts.txt");
	if (!file.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	for (size_t i = 0; i < size; i++) {
		carts[i].writeToFile(file);
	}

	file.close(); 
}

CartContainer::~CartContainer()
{
	freeDynamicMemory();
}