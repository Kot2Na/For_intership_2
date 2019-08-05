#include "header.h"

keyboard::keyboard(const char *_name) : device(_name)
{
	fd = open("/dev/console", O_NOCTTY);
}

char	*keyboard::what_type()
{
	char *type;

	type = new char[255];
	strncpy(type, typeid(*this).name(), strlen(typeid(*this).name()) + 1);
	return (type);
}

void	keyboard::action(t_data *data)
{
	this->i += 1; 
	if (fd)
	{
		if (this->i % 2 == 1)
			ioctl(0, 0x4B32, 0x0);
		else
			ioctl(0, 0x4B32, 0x04);
	}
	data->data = rand();
	data->dev = data->mather->new_control();
}

keyboard::~keyboard()
{
	close(fd);
}
