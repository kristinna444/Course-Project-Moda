#pragma once

#include "Order.h"

class OrderContainer {
private:
	Order* orders;
	size_t currentNumberOfOrders;
	size_t capacity;

	void freeDynamicMemory();
	void copyDynamicMemory(const OrderContainer& other);

	size_t getNumberOfPendingOrders() const; 
	size_t getNumberOfShippedOrders(const MyString& clientName) const;  

	Order** getPendingOrders(size_t& numberOfPendingOders);
	Order** getShippedOrders(const MyString& clientName, size_t& numberOfShippedOrders);
	

public:
	OrderContainer(const char* fileName);
	OrderContainer(const OrderContainer& other);
	OrderContainer& operator=(const OrderContainer& other);

	Order& operator[](size_t index);
	const Order& operator[](size_t index) const;
	size_t getCurrentNumberOfOrders() const;

	bool hasProduct(const MyString& clientName, int productID);

	void markAsApproved(size_t index);
	double markAsConfirmed(const MyString& clientName, size_t index);

	double totalAmountSpent(const MyString& clientName);
	size_t numberOfCompletedOrders(const MyString& clientName);

	Order rejectOrder(size_t index, const MyString& message);  
	void shiftLeft(size_t index);  
	void deleteOrder(const Order& orderToDelete);  

	void listPendingOrders() const;
	void listOrdersByStatus(const char* status, const MyString& clientName) const;
	void listOrdersOf(const MyString& clientName) const;

	void printOrders() const; 
	void updateFileWithOrders(const char* fileName) const; 

	~OrderContainer();
};
