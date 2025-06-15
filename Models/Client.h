#pragma once

#include "User.h"
#include "../Objects/Searchbar.h"
#include "../Objects/Cart.h"
#include "../Objects/OrderContainer.h"
#include "../Objects/Wallet.h"


class Client : public User
{
	Wallet* wallet;
	Cart* cart;

	Searchbar searchbar;
	bool isSearchbarLoaded = false;
	
public:
	Client(const MyString& name, const MyString& EGN, const MyString& password);

	void setWallet(Wallet* wallet);
	void setCart(Cart* cart);

	const char* getRole() const override;
	User* clone() const override;
	void writeToFile(std::ofstream& output) const override;

	void checkBalance() const;

	void addPoints(double points);
	void addToWallet(double sum);
	void setPointsToZero();

	void loadSearchbar();
	
	void addToCart(int productID, size_t quantity); 
	void removeFromCart(const MyString& productName, size_t quantity);
	void viewCart() const; 

	void applyDiscountToCart();
	void removeDiscountFromCart();

	bool checkout();
};
