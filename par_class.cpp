#include "header.h"

device::device(const char *_name)
{
	i = 0;
	this->name = new char[255];
	strncpy(this->name, _name, strlen(_name) + 1);
}

void device::call_name()
{
	std::cout << this->name << std::endl;
}

char *device::what_type()
{
	char *type;

	type = new char[255];
	strncpy(type, typeid(this).name(), strlen(typeid(this).name() + 1));
	return (type);
}

void device::action(t_data *data)
{
}

device *device::new_control()
{
	return (NULL);
}

device::~device()
{
	delete[] this->name;
}
