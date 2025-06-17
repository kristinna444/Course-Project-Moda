#include "Order.h"

void Order::freeDynamicMemory()
{
	delete[] products;
}

void Order::copyDynamicMemory(const Order& other)
{
	size = other.size;

	products = new Product[size];
	for (size_t i = 0; i < size; i++) {
		products[i] = other.products[i]; 
	}

	totalPrice = other.totalPrice;
	points = other.points;
	discount = other.discount;

	status = other.status;
	clientName = other.clientName;
}

size_t Order::getProductQuantity(const MyString& productName) const
{
	size_t productQuantity = 0;
	for (size_t i = 0; i < size; i++) {
		if (products[i].getStringName() == productName) { 
			productQuantity++;
		}
	}
	
	return productQuantity;
}

Order::Order()
{
	products = new Product[20];
}

Order::Order(const Product* products, size_t size, double totalPrice, double discount, const MyString& status, const MyString& clientName):  
	size(size), totalPrice(totalPrice), discount(discount), status(status), clientName(clientName)
{
	points = 5 * totalPrice;

	this->products = new Product[size];
	for (size_t i = 0; i < size; i++) {
		this->products[i] = products[i];
	}
}

Order::Order(const Order& other)
{
	copyDynamicMemory(other);
}

Order& Order::operator=(const Order& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

double Order::getPoints() const
{
	return 5 * totalPrice; 
}

double Order::getPrice() const
{
	return totalPrice;
}

double Order::getDiscount() const
{
	return discount;
}

const Product& Order::operator[](size_t index) const
{
	return products[index];
}

size_t Order::getSize() const
{
	return size; 
}

const MyString& Order::getClientName() const
{
	return clientName;
}

const char* Order::getStatus() const
{
	return status.c_str();
}

void Order::setStatus(const char* status)
{
	if (strcmp(status, "Pending") == 0) {
		this->status = MyString("Pending");
		return;
	}
	else if (strcmp(status, "Shipped") == 0) {
		this->status = MyString("Shipped");
		return;
	}
	else if (strcmp(status, "Delivered") == 0) {
		this->status = MyString("Delivered");
		return;
	}
	else if (strcmp(status, "Rejected") == 0) {
		this->status = MyString("Rejected");
		return;
	}
	else if (strcmp(status, "Refunded") == 0) {
		this->status = MyString("Refunded");
		return;
	}

	throw std::logic_error("There's no such status");
}

void Order::writeOrderToFile(const char* fileName) const
{
	std::ofstream ordersFile(fileName, std::ios::app);
	if (!ordersFile.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	ordersFile << clientName << "|";

	size_t productQuantity = 0;

	for (size_t i = 0; i < size; i += productQuantity) {
		productQuantity = getProductQuantity(products[i].getStringName());
		ordersFile << productQuantity << "x" << products[i].getStringName() << ",";
	}

	ordersFile << " " << totalPrice << " " << discount << " " << status << std::endl;

	ordersFile.close();
}

void Order::writeOrderToFile(std::ofstream& ordersFile) const
{
	ordersFile << clientName << "|";

	size_t productQuantity = 0;

	for (size_t i = 0; i < size; i += productQuantity) {
		productQuantity = getProductQuantity(products[i].getStringName());
		ordersFile << productQuantity << "x" << products[i].getStringName() << ",";
	}

	ordersFile << " " << totalPrice << " " << discount << " " << status << std::endl;
}

void Order::printOrder() const
{
	std::cout << clientName << ": ";

	size_t productQuantity = 0;

	for (size_t i = 0; i < size; i += productQuantity) {
		productQuantity = getProductQuantity(products[i].getStringName());
		std::cout << productQuantity << "x " << products[i].getStringName();

		if ((i + productQuantity) < size) {
			std::cout << ", ";
		}
	}

	std::cout << " " << totalPrice << "BGN " << "Current status: " << status << std::endl;
}

void Order::readOrderFromFile(std::stringstream& input) 
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

	double totalPrice, discount; 
	input >> totalPrice >> discount; 
	this->totalPrice = totalPrice;
	this->discount = discount;

	input.ignore();

	char status[CONSTANTS::MAX_LENGTH];
	input.getline(status, CONSTANTS::MAX_LENGTH);
	setStatus(status);

	delete[] products;
	products = temp;
	size = currentSize;

}

bool Order::hasProduct(int productID) const
{
	for (size_t i = 0; i < size; i++) {
		if (products[i].getID() == productID) {
			return true;
		}
	}

	return false;
}

void Order::getProductsFromStorage()
{
	int numberOfItems = 0;
	Product* itemsInStorage = Storage::readProductsFromFile("items_collection.txt", numberOfItems); 

	size_t productQuantity = 0;
	for (size_t i = 0; i < size; i += productQuantity) {
		productQuantity = getProductQuantity(products[i].getStringName());
		Product* item = Storage::getProductByName(itemsInStorage, numberOfItems, products[i].getStringName()); 
		item->getProductFromStorage(productQuantity);
	}

	Storage::updateList(itemsInStorage, numberOfItems, "items_collection.txt");
	delete[] itemsInStorage;
}

void Order::returnProductsToStorage()
{
	int numberOfItems = 0;
	Product* itemsInStorage = Storage::readProductsFromFile("items_collection.txt", numberOfItems);

	size_t productQuantity = 0;
	for (size_t i = 0; i < size; i += productQuantity) {
		productQuantity = getProductQuantity(products[i].getStringName());
		Product* item = Storage::getProductByName(itemsInStorage, numberOfItems, products[i].getStringName());
		item->returnProductToStorage(productQuantity); 
	}

	Storage::updateList(itemsInStorage, numberOfItems, "items_collection.txt");
	delete[] itemsInStorage;
}

Order::~Order()
{
	freeDynamicMemory();
}

bool operator==(const Order& lhs, const Order& rhs)
{
	if (lhs.clientName != rhs.clientName || lhs.status != rhs.status || lhs.size != rhs.size) {
		return false;
	}

	for (size_t i = 0; i < lhs.size; i++) {
		if (lhs.products[i] != rhs.products[i]) { 
			return false;
		}
	}

	return true;
}
