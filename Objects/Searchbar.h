#pragma once

#include "Product.h"
#include "../Storage.h"
#include "../Utils.h"

class Searchbar
{
private:
	Product* products;
	int size;
	int capacity;

	void freeDynamicMemory();
	void copyDynamicMemory(const Searchbar& other);
	void moveDynamicMemory(Searchbar&& other);
	void shiftLeft(size_t index);
	void resize(int newCapacity);

	void swapProducts(Product& lhs, Product& rhs);
public:
	Searchbar();
	Searchbar(const char* fileName);
	Searchbar(const Searchbar& other);
	Searchbar& operator=(const Searchbar& other);

	Searchbar(Searchbar&& other) noexcept;
	Searchbar& operator=(Searchbar&& other) noexcept;

	const Product& operator[](size_t index) const;
	Product& operator[](size_t index);
	int getSize() const;

	void load();

	void listProducts();
	void filterByNumberOfSales();
	void filterByRatings();
	void filterByNames();
	void filterByAscendingPrice();
	void filterByDescendingPrice();
	void viewProduct(int productID) const;

	void print() const;
	const Product& getProduct(int productID, size_t quantity) const; 

	void deleteProduct(size_t index);
	void rateProduct(int productID, double rating);

	void updateList() const;

	~Searchbar();
};
