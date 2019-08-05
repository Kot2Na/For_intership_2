#include "header.h"

hdd::hdd(const char *_name, const char *_file_name) : device(_name)
{
	this->file_name = new char[255];
	strncpy(this->file_name, _file_name, strlen(_file_name) + 1);
	fd.open(this->file_name);
}

char	*hdd::what_type()
{
	char	*type;

	type = new char[255];
	strncpy(type, typeid(*this).name(), strlen(typeid(*this).name()) + 1);
	return (type);
}

void	hdd::action(t_data *data)
{
	this->i += 1; 
	if (fd.is_open())
	{
		fd << data->data << std::endl;
	}
	data->data = rand();
	data->dev = data->mather->new_control();
}

hdd::~hdd()
{
	delete[] file_name;
	fd.close();
}
