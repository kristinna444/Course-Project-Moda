#pragma once

#include "Models/User.h"
#include "Models/UsersContainer.h"
#include "Objects/RatingContainer.h"
#include "Objects/CartContainer.h"
#include "Objects/CheckContainer.h"
#include "Objects/Bank.h"
#include "Models/UserFactory.h"

class System
{
private:
	UsersContainer users;
	Bank bank;
	CartContainer carts;
	User* currentUser;

public:
	System();
	void load();

	const User* getCurrentUser() const;
	User* getCurrentUser();
	User* getClientByName(const MyString& name);

	void setCurrentUser(User* user);
	void setUserData(User* user);

	void addUser(const MyString& name, const MyString& EGN, const MyString& password, const char* role); 
	User* getUserFromFile(const MyString& name, const MyString& password); 

	void deleteCart(const MyString& clientName);

	void logout();
}; 
