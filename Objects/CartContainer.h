#pragma once

#include "Cart.h"

class CartContainer
{
private:
	Cart* carts;
	size_t size;
	size_t capacity;

	void freeDynamicMemory();
	void copyDynamicMemory(const CartContainer& other);
	void shiftLeft(size_t index);
	void resize(size_t newCapacity);
public:
	CartContainer();
	CartContainer(const CartContainer& other);
	CartContainer& operator=(const CartContainer& other);

	Cart* getCart(const MyString& clientName);

	void addCart(const Cart& newCart);  
	void removeCart(const MyString& clientName);

	void load();
	void readFromFile(const char* fileName);
	void updateFileWithCarts() const;

	~CartContainer();
};
