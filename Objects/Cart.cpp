#include "Cart.h"

void Cart::freeDynamicMemory()
{
	delete[] products;
}

void Cart::copyDynamicMemory(const Cart& other)
{
	size = other.size;
	capacity = other.capacity;

	totalAmount = other.totalAmount;
	discount = other.discount;

	clientName = other.clientName;

	products = new Product[capacity];
	for (size_t i = 0; i < size; i++) {
		products[i] = other.products[i]; 
	}
}

void Cart::resize(size_t newCapacity)
{
	capacity = newCapacity;

	Product* temp = new Product[capacity];
	for (size_t i = 0; i < size; i++) {
		temp[i] = products[i];
	}

	delete[] products;
	products = temp;
}

void Cart::shiftLeft(size_t index, size_t quantity) 
{
	for (size_t i = index; i < size - quantity; i++) { 
		products[i] = products[i + quantity];   
	}
}

size_t Cart::getProductQuantity(const MyString& productName) const
{
	size_t productQuantity = 0;

	for (size_t i = 0; i < size; i++) {
		if (productName == products[i].getStringName()) {
			productQuantity++;
		}
	}

	return productQuantity;
}

void Cart::setTotalAmount(double amount)
{
	this->totalAmount = amount;
}

void Cart::setDiscount(double discount)
{
	this->discount = discount;
}

Cart::Cart(): size(0), capacity(CONSTANTS::BEG_CAPACITY), 
totalAmount(0), discount(0) 
{
	products = new Product[capacity];
}

Cart::Cart(const MyString& clientName):size(0), capacity(CONSTANTS::BEG_CAPACITY),
totalAmount(0), discount(0), clientName(clientName) 
{
	products = new Product[capacity];
}

Cart::Cart(const Cart& other)
{
	copyDynamicMemory(other);
}

Cart& Cart::operator=(const Cart& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

const Product* Cart::getProducts() const
{
	return products; 
}

size_t Cart::getSize() const
{
	return size; 
}

double Cart::getTotalAmount() const
{
	return totalAmount;
}

const MyString& Cart::getClientName() const
{
	return clientName;
}

void Cart::addProduct(const Product& product)
{
	if (size == capacity) {
		resize(capacity * CONSTANTS::RES_FACTOR);
	}

	products[size++] = product; 
	totalAmount += product.getPrice();
}

void Cart::removeProduct(const MyString& productName, size_t quantity)
{
	size_t productQuantity = getProductQuantity(productName);

	if (productQuantity == 0) {
		std::cout << "There are no products with this name in your cart!" << std::endl;
		return;
	}

	if (quantity > productQuantity) {
		std::cout << "There are only " << productQuantity << "x " << productName << " left in your cart!" << std::endl;
		quantity = productQuantity;
	}

	for (size_t i = 0; i < size; i++) {
		if (products[i].getStringName() == productName) {
			totalAmount -= (quantity * products[i].getPrice()); 

			shiftLeft(i, quantity);
			size -= quantity;

			break;
		}
	}

	std::cout << quantity << "x " << productName << " removed from your cart" << std::endl; 
}

void Cart::view() const
{
	std::cout << "Items in cart: " << std::endl;

	size_t productQuantity = 0;
	for (size_t i = 0; i < size; i += productQuantity) {
		productQuantity = getProductQuantity(products[i].getStringName());
		std::cout << productQuantity << "x " << products[i].getStringName() << " " << products[i].getPrice() << " BGN" << std::endl;
	}

	std::cout << "Discount: -" << discount << " BGN" << std::endl;
	std::cout << "Total amount: " << totalAmount << " BGN" << std::endl;
}

double Cart::getDiscount() const
{
	return discount; 
}

bool Cart::applyDiscount(double discount) 
{
	if (discount >= 0.5 * totalAmount) 
	{
		std::cout << "Only discounts under 50% allowed!" << std::endl;
		return false;
	}

	setTotalAmount(totalAmount - discount);
	setDiscount(discount);
	return true;
}

double Cart::removeDiscount()
{
	if (discount == 0) {
		std::cout << "No discount applied!" << std::endl;
		return 0;
	}

	double sumToReturn = discount;
	setTotalAmount(totalAmount + discount);
	setDiscount(0);

	return sumToReturn; 
}

void Cart::empty()
{
	freeDynamicMemory();
	size = 0;
	capacity = 0;
	products = nullptr;
}

void Cart::writeToFile(std::ofstream& output) const
{
	output << clientName << "|"; 

	size_t productQuantity = 0; 

	for (size_t i = 0; i < size; i += productQuantity) { 
		productQuantity = getProductQuantity(products[i].getStringName()); 
		output << productQuantity << "x" << products[i].getStringName() << ","; 
	}

	output << " " << totalAmount << " " << discount << std::endl; 
}

void Cart::readFromFile(std::stringstream& input) 
{
	int currentPosition = input.tellg();

	size_t numberOfProducts = Utils::getCharOccurences(input, ORDER_CONST::PRODUCT_DELIM); 
	size_t currentSize = 0;
	Product* temp = new Product[ORDER_CONST::MAX_ORDER_CAPACITY];

	input.clear();
	input.seekg(0, currentPosition);

	char clientName[CONSTANTS::MAX_LENGTH];
	input.getline(clientName, CONSTANTS::MAX_LENGTH, ORDER_CONST::NAME_DELIM);
	this->clientName = MyString(clientName);

	size_t counter = 0;
	for (size_t i = 0; i < numberOfProducts; i++) {
		input >> counter;
		input.ignore();

		char productName[CONSTANTS::MAX_LENGTH]; 
		input.getline(productName, CONSTANTS::MAX_LENGTH, ORDER_CONST::PRODUCT_DELIM); 
		Product product = Storage::getProductByName(productName); 

		for (size_t i = 0; i < counter; i++) { 
			if (currentSize == ORDER_CONST::MAX_ORDER_CAPACITY) { 
				throw std::out_of_range("You exceeded the limit of one order");
			}

			temp[currentSize++] = product;
		}
	}

	input.ignore();

	double totalAmount, discount; 
	input >> totalAmount >> discount; 
	this->totalAmount = totalAmount; 
	this->discount = discount;

	input.ignore();

	delete[] products;
	products = temp;
	size = currentSize;
	capacity = ORDER_CONST::MAX_ORDER_CAPACITY;

}

Cart::~Cart()
{
	freeDynamicMemory();
}