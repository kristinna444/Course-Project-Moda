#include "OrderContainer.h"

void OrderContainer::freeDynamicMemory()
{
	delete[] orders;
}

void OrderContainer::copyDynamicMemory(const OrderContainer& other)
{
	currentNumberOfOrders = other.currentNumberOfOrders;
	capacity = other.capacity;

	orders = new Order[currentNumberOfOrders];
	for (size_t i = 0; i < currentNumberOfOrders; i++) { 
		orders[i] = other.orders[i];
	}
}

void OrderContainer::shiftLeft(size_t index)
{
	for (size_t i = index; i < currentNumberOfOrders - 1; i++) {
		orders[i] = orders[i + 1];
	}

	currentNumberOfOrders--;
}

size_t OrderContainer::getNumberOfPendingOrders() const
{
	size_t counter = 0;
	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		if (strcmp(orders[i].getStatus(), "Pending") == 0) {
			counter++;
		}
	}

	return counter;
}

size_t OrderContainer::getNumberOfShippedOrders(const MyString& clientName) const
{
	size_t counter = 0;
	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		if (strcmp(orders[i].getStatus(), "Shipped") == 0 && orders[i].getClientName() == clientName) { 
			counter++;
		}
	}

	return counter;
}

Order** OrderContainer::getPendingOrders(size_t& numberOfPendingOrders)
{
	numberOfPendingOrders = getNumberOfPendingOrders();

	if (numberOfPendingOrders == 0) {
		return nullptr;
	}

	Order** pendingOrders = new Order*[numberOfPendingOrders];
	size_t currentSize = 0;

	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		if (strcmp(orders[i].getStatus(), "Pending") == 0 && currentSize < numberOfPendingOrders) {
			pendingOrders[currentSize++] = &orders[i];
		}
	}

	return pendingOrders;
}

Order** OrderContainer::getShippedOrders(const MyString& clientName, size_t& numberOfShippedOrders) 
{
	numberOfShippedOrders = getNumberOfShippedOrders(clientName); 

	if (numberOfShippedOrders == 0) {
		return nullptr;
	}

	Order** shippedOrders = new Order*[numberOfShippedOrders];
	size_t currentSize = 0;

	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		if (strcmp(orders[i].getStatus(), "Shipped") == 0 && orders[i].getClientName() == clientName) { 
			shippedOrders[currentSize++] = &orders[i];
		}
	}

	return shippedOrders;
}

void OrderContainer::deleteOrder(const Order& orderToDelete)
{
	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		if (orderToDelete == orders[i]) {
			shiftLeft(i);

			return;
		}
	}

	throw std::logic_error("There's no such order!");
}

OrderContainer::OrderContainer(const char* fileName): 
	currentNumberOfOrders(0), capacity(0), orders(nullptr)
{
	std::ifstream input(fileName);

	if (!input.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	int currentPosition = input.tellg();

	size_t numberOfOrders = Utils::getCharOccurences(input, '\n');
	Order* temp = new Order[numberOfOrders];

	input.clear();
	input.seekg(0, currentPosition);

	Order newOrder;
	for (size_t i = 0; i < numberOfOrders; i++) {
		char buffer[CONSTANTS::MAX_LENGTH];
		input.getline(buffer, CONSTANTS::MAX_LENGTH);

		std::stringstream ss(buffer);

		newOrder.readOrderFromFile(ss);
		temp[i] = newOrder;
	}

	input.close();

	delete[] orders;
	orders = temp;
	currentNumberOfOrders = numberOfOrders;
	capacity = Utils::roundToPowerOfTwo(currentNumberOfOrders);
}

OrderContainer::OrderContainer(const OrderContainer& other)
{
	copyDynamicMemory(other);
}

OrderContainer& OrderContainer::operator=(const OrderContainer& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

Order& OrderContainer::operator[](size_t index)
{
	return orders[index];
}

const Order& OrderContainer::operator[](size_t index) const
{
	return orders[index]; 
}

size_t OrderContainer::getCurrentNumberOfOrders() const
{
	return currentNumberOfOrders; 
}

double OrderContainer::totalAmountSpent(const MyString& clientName)
{
	double sum = 0;
	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		if (orders[i].getClientName() == clientName) {
			sum += orders[i].getPrice();
		}
	}

	return sum;
}

size_t OrderContainer::numberOfCompletedOrders(const MyString& clientName)
{
	size_t counter = 0; 
	for (size_t i = 0; i < currentNumberOfOrders; i++) { 
		if (orders[i].getClientName() == clientName && strcmp(orders[i].getStatus(), "Delivered") == 0) {
			counter++;
		}
	}

	return counter; 
}

bool OrderContainer::hasProduct(const MyString& clientName, int productID)
{
	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		if (strcmp(orders[i].getStatus(), "Delivered") == 0 && orders[i].getClientName() == clientName && 
			orders[i].hasProduct(productID)) {

			return true;
		}
	}

	return false;
}

void OrderContainer::listPendingOrders() const
{
	bool pendingOrdersPresent = false;
	size_t currentOrderIndex = 1;

	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		if (strcmp(orders[i].getStatus(), "Pending") == 0) {
			std::cout << currentOrderIndex << ". ";
			orders[i].printOrder();  

			pendingOrdersPresent = true;
			currentOrderIndex++;
		}
	}

	if (!pendingOrdersPresent) {
		std::cout << "No pending orders left!" << std::endl;
	}
}

void OrderContainer::listOrdersByStatus(const char* status, const MyString& clientName) const
{
	bool found = false;
	size_t currentIndex = 1;

	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		if (strcmp(orders[i].getStatus(), status) == 0 && orders[i].getClientName() == clientName) {  
			std::cout << currentIndex << ". ";
			orders[i].printOrder(); 

			found = true;
			currentIndex++;
		}
	}

	if (!found) {
		std::cout << "No orders on your name!" << std::endl;
	}
}

void OrderContainer::listOrdersOf(const MyString& clientName) const
{
	bool found = false;
	size_t currentIndex = 1;

	for (size_t i = 0; i < currentNumberOfOrders; i++) { 
		if (orders[i].getClientName() == clientName) { 
			std::cout << currentIndex << ". "; 
			orders[i].printOrder(); 

			currentIndex++;
			found = true;
		}
	}

	if (!found) {
		std::cout << "No refunded orders on your name!" << std::endl;
	}

}

void OrderContainer::markAsApproved(size_t index)  
{
	size_t numberOfPendingOrders = 0;
	Order** pendingOrders = getPendingOrders(numberOfPendingOrders); 

	if (!pendingOrders) {
		std::cout << "There are no pending orders left!" << std::endl;
		return;
	}

	if (index > numberOfPendingOrders) {
		std::cout << "Order with this ID doesn't exist!" << std::endl;
		delete[] pendingOrders;
		return;
	}

	pendingOrders[index - 1]->getProductsFromStorage();
	pendingOrders[index - 1]->setStatus("Shipped");
	std::cout << "Order #" << index << " approved and shipped" << std::endl;

	delete[] pendingOrders;
	updateFileWithOrders("orders.txt");
}

Order OrderContainer::rejectOrder(size_t index, const MyString& message)
{
	size_t numberOfPendingOrders = 0;
	Order** pendingOrders = getPendingOrders(numberOfPendingOrders);

	if (!pendingOrders) {
		throw std::out_of_range("No pending orders left!");
	}

	if (index > numberOfPendingOrders) {
		delete[] pendingOrders;
		throw std::out_of_range("Pending order with this ID doesn't exist!");
	}

	Order orderToDelete = *pendingOrders[index - 1];
	deleteOrder(orderToDelete); 
	std::cout << "Order #" << index << " rejected" << std::endl; 

	orderToDelete.setStatus("Rejected");
	orderToDelete.writeOrderToFile("rejected_requests.txt");

	std::ofstream descriptions("descriptions.txt", std::ios::app);
	if (!descriptions.is_open()) {
		throw std::runtime_error("Program couldn't open file");
	}

	descriptions << message << std::endl; 
	descriptions.close();
	
	delete[] pendingOrders;
	updateFileWithOrders("orders.txt");

	return orderToDelete; 
}

double OrderContainer::markAsConfirmed(const MyString& clientName, size_t index) 
{
	size_t numberOfShippedOrders = 0; 
	Order** shippedOrders = getShippedOrders(clientName, numberOfShippedOrders); 

	if (!shippedOrders) { 
		std::cout << "There are no shipped orders on your name!" << std::endl;
		return 0;
	}

	if (index > numberOfShippedOrders) { 
		std::cout << "Order with this ID doesn't exist!" << std::endl;
		delete[] shippedOrders; 
		return 0;
	}

	shippedOrders[index - 1]->setStatus("Delivered"); 

	double loyaltyPoints = shippedOrders[index - 1]->getPoints();

	std::cout << "Order #" << index << " confirmed as delivered." << std::endl;

	delete[] shippedOrders;
	updateFileWithOrders("orders.txt");

	return loyaltyPoints;

}

void OrderContainer::printOrders() const
{
	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		std::cout << i + 1 << ". ";
		orders[i].printOrder();
	}
}

void OrderContainer::updateFileWithOrders(const char* fileName) const
{
	std::ofstream ordersFile(fileName);
	if (!ordersFile.is_open()) {
		throw std::runtime_error("Program couldn't open file"); 
	}

	for (size_t i = 0; i < currentNumberOfOrders; i++) {
		orders[i].writeOrderToFile(ordersFile);
	}

	ordersFile.close();
}

OrderContainer::~OrderContainer()
{
	freeDynamicMemory();
}
