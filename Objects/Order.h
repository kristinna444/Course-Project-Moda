#pragma once
#include <sstream> 
#include "Product.h"
#include "../Storage.h"
#include "../Utils.h"

namespace ORDER_CONST
{
	constexpr char NAME_DELIM = '|';
	constexpr char PRODUCT_DELIM = ',';
	constexpr size_t MAX_ORDER_CAPACITY = 100;
}

class Order
{
private:
	Product* products;
	size_t size;

	double totalPrice;
	double discount;
	double points;

	MyString status;
	MyString clientName;

	void freeDynamicMemory();
	void copyDynamicMemory(const Order& other);
	

public:
	Order();
	Order(const Product* products, size_t size, double totalPrice, double discount, const MyString& status, const MyString& clientName); 

	Order(const Order& other);
	Order& operator=(const Order& other);

	double getPoints() const;
	double getPrice() const;

	size_t getProductQuantity(const MyString& productName) const; 
	const Product& operator[](size_t index) const;
	size_t getSize() const;

	const MyString& getClientName() const;
	const char* getStatus() const;
	void setStatus(const char* status);

	void writeOrderToFile(const char* fileName) const;
	void writeOrderToFile(std::ofstream& ordersFile) const;
	void printOrder() const;
	void readOrderFromFile(std::stringstream& input);

	bool hasProduct(int productID) const;
	void getProductsFromStorage();
	void returnProductsToStorage();

	~Order();

	friend bool operator==(const Order& lhs, const Order& rhs);
};
