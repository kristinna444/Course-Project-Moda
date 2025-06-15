#pragma once

#include "../MyString.h"

class Product
{
private:
	static int nextID;
	int ID;
	MyString name;
	double price;
	size_t quantity;
	size_t numberOfSales;
	MyString description;
	double rating;
	bool availability;

public:
	Product() = default;
	Product(const MyString& name, double price, size_t quantity, const MyString& description);

	const char* getName() const;
	const MyString& getStringName() const;
	const char* getDescription() const;
	double getPrice() const;

	double getRating() const;
	void setRating(double rating);

	int getID() const; 
	size_t getQuantity() const;
	size_t getNumberOfSales() const;

	void writeProductToFile(std::ofstream& output) const;
	void readProductFromFile(std::ifstream& input);
	
	void getProductFromStorage(size_t quantity);
	void returnProductToStorage(size_t quantity);

	void print() const;

	friend bool operator==(const Product& lhs, const Product& rhs);
};

bool operator!=(const Product& lhs, const Product& rhs);

