#include "UsersContainer.h"

void UsersContainer::freeDynamicMemory()
{
	for (size_t i = 0; i < size; i++) {
		delete users[i];
	}

	delete[] users;
}

void UsersContainer::copyDynamicMemory(const UsersContainer& other)
{
	size = other.size;
	capacity = other.capacity;

	users = new User*[capacity];

	for (size_t i = 0; i < size; i++) {
		users[i] = other.users[i]->clone();
	}
}

void UsersContainer::moveDynamicMemory(UsersContainer&& other)
{
	users = other.users;
	other.users = nullptr;

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;
}

void UsersContainer::resize(size_t newCapacity)
{
	capacity = newCapacity;

	User** temp = new User*[capacity];

	for (size_t i = 0; i < size; i++) {
		temp[i] = users[i];
	}

	delete[] users;
	users = temp;
}

UsersContainer::UsersContainer(): size(0), capacity(CONSTANTS::BEG_CAPACITY)
{
	users = new User*[capacity]; 
}

UsersContainer::UsersContainer(const UsersContainer& other)
{
	copyDynamicMemory(other);
}

UsersContainer& UsersContainer::operator=(const UsersContainer& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

UsersContainer::UsersContainer(UsersContainer&& other) noexcept
{
	moveDynamicMemory(std::move(other));
}

UsersContainer& UsersContainer::operator=(UsersContainer&& other) noexcept
{
	if (this != &other) { 
		freeDynamicMemory(); 
		moveDynamicMemory(std::move(other));
	}

	return *this;
}

size_t UsersContainer::getNumberOfUsers() const
{
	return size;
}

User* UsersContainer::operator[](size_t index)
{
	if (index >= size) {
		throw std::out_of_range("Such user doesn't exist");
	}

	return users[index];
}

void UsersContainer::addUser(const User* newUser)
{
	if (size == capacity) {
		resize(capacity * CONSTANTS::RES_FACTOR);
	}

	users[size++] = newUser->clone();
}

void UsersContainer::loadUsersFromFile()
{
	freeDynamicMemory();

	std::ifstream usersFile("users.txt");
	if (!usersFile.is_open()) {
		throw std::runtime_error("Program couldn't open file!");
	}

	size_t numberOfUsers = Utils::getCharOccurences(usersFile, '\n'); 
	User** temp = new User*[numberOfUsers];

	usersFile.clear();
	usersFile.seekg(0, std::ios::beg);

	for (size_t i = 0; i < numberOfUsers; i++) {
		char userName[CONSTANTS::MAX_LENGTH];
		usersFile.getline(userName, CONSTANTS::MAX_LENGTH, '|'); 

		char userEGN[CONSTANTS::MAX_LENGTH]; 
		usersFile.getline(userEGN, CONSTANTS::MAX_LENGTH, '|'); 

		char userPassword[CONSTANTS::MAX_LENGTH]; 
		usersFile.getline(userPassword, CONSTANTS::MAX_LENGTH, '|');  

		MyString name(userName), EGN(userEGN), password(userPassword);  

		char role[CONSTANTS::MAX_LENGTH];
		usersFile.getline(role, CONSTANTS::MAX_LENGTH);

		temp[i] = UserFactory::create(name, EGN, password, role);
	}

	usersFile.close();

	users = temp;
	size = numberOfUsers;
	capacity = Utils::roundToPowerOfTwo(size); 
}

UsersContainer::~UsersContainer()
{
	freeDynamicMemory();
}