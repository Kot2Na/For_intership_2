#include "header.h"

net_plate::net_plate(const char *_name) : device(_name) {};
net_plate::~net_plate() {};

char	*net_plate::what_type()
{
	char	*type;

	type = new char[255];
	strncpy(type, typeid(*this).name(), strlen(typeid(*this).name()) + 1);
	return (type);
}

void	net_plate::action(t_data *data)
{
	this->i += 1; 
	sleep(0);
	data->data = rand();
	data->dev = data->mather->new_control();
}
