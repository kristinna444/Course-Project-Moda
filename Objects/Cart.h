#pragma once

#include "Product.h"
#include "Order.h" 

class Cart
{
private:
	Product* products;
	size_t size;
	size_t capacity;

	double totalAmount; 
	double discount;

	MyString clientName;

	void freeDynamicMemory();
	void copyDynamicMemory(const Cart& other);

	void resize(size_t newCapacity);
	void shiftLeft(size_t index, size_t quantity);

	size_t getProductQuantity(const MyString& productName) const; 

public:
	Cart();
	Cart(const MyString& clientName);
	Cart(const Cart& other);
	Cart& operator=(const Cart& other);

	const Product* getProducts() const;
	size_t getSize() const;
	double getTotalAmount() const;
	const MyString& getClientName() const;

	void setTotalAmount(double amount);
	void setDiscount(double discount);

	void addProduct(const Product& product);
	void removeProduct(const MyString& productName, size_t quantity);
	void view() const;
	
	double getDiscount() const;
	bool applyDiscount(double discount);
	double removeDiscount();

	void writeToFile(std::ofstream& output) const;
	void readFromFile(std::stringstream& input); 

	void empty();

	~Cart();
};


