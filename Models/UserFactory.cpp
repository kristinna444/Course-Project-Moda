#include "UserFactory.h"

User* UserFactory::create(const MyString& name, const MyString& EGN, const MyString& password, const char* role)
{
	if (strcmp(role, "Administrator") == 0) {
		return new Administrator(name, EGN, password);
	}
	else if (strcmp(role, "Business") == 0) {
		return new Business(name, EGN, password);
	}
	else if (strcmp(role, "Client") == 0) {
		return new Client(name, EGN, password);
	}

	throw std::logic_error("Such role doesn't exist");
}