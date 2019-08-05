#include "header.h"

gpu_plate::gpu_plate(const char *_name) : device(_name) {};
gpu_plate::~gpu_plate() {};

char	*gpu_plate::what_type()
{
	char *type;

	type = new char[255];
	strncpy(type, typeid(*this).name(), strlen(typeid(*this).name()) + 1);
	return (type);
}

void	gpu_plate::action(t_data *data)
{
	this->i += 1; 
	if (data)
		std::cout << data->data << std::endl;
	data->data = rand();
	data->dev = data->mather->new_control();
}
