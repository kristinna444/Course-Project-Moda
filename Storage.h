#pragma once

#include "Objects/Product.h"

class Storage
{
public:
	static Product* readProductsFromFile(const char* fileName, int& numberOfProducts);
	static Product getProductByName(const char* productName);
	static Product* getProductByName(Product* products, size_t size, const MyString& productName);
	static void updateList(const Product* products, int size, const char* fileName);
};
