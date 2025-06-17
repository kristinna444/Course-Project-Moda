#pragma once

#include "User.h"
#include "UserFactory.h"
#include "../Utils.h"

class UsersContainer
{
private:
	User** users;
	size_t size;
	size_t capacity;

	void freeDynamicMemory();
	void copyDynamicMemory(const UsersContainer& other);
	void moveDynamicMemory(UsersContainer&& other);
	void resize(size_t newCapacity);

public:
	UsersContainer();

	UsersContainer(const UsersContainer& other);
	UsersContainer& operator=(const UsersContainer& other);

	UsersContainer(UsersContainer&& other) noexcept;
	UsersContainer& operator=(UsersContainer&& other) noexcept;

	size_t getNumberOfUsers() const;
	User* operator[](size_t index);
	const User* operator[](size_t index) const;

	void addUser(const User* newUser);
	void loadUsersFromFile(); 

	~UsersContainer();
};