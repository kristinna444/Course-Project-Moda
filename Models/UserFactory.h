#pragma once

#include "Admin.h"
#include "Business.h"
#include "Client.h"

class UserFactory
{
public:
	static User* create(const MyString& name, const MyString& EGN, const MyString& password, const char* role);
};
