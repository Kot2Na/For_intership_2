#include "header.h"

mather_plate::mather_plate(const char *_name, const char *_file_name) : device(_name)
{
	this->file_name = new char[255];
	strncpy(this->file_name, _file_name, strlen(_file_name) + 1);
	fd.open(this->file_name);
}

char	*mather_plate::what_type()
{
	char	*type;

	type = new char[255];
	strncpy(type, typeid(*this).name(), strlen(typeid(*this).name()) + 1);
	return (type);
}

void	mather_plate::registrate(device *item)
{
	list_dev.list_add_end(item);
}

void	mather_plate::action()
{
	device	*control;
	t_data	data;

	data.data = rand();
	data.mather = this;
	control = list_dev.find_gpu();
	while (this->i < 100)
	{
		fd << "get control " << control->name << " data is : " << data.data << std::endl;
		control->action(&data);
		control = data.dev;
		if (control)
			this->i += 1;
		else
			return ;
	}
	list_dev.list_print_count();
	list_dev.list_destroy(NULL);
}

device	*mather_plate::new_control()
{
	return (list_dev.rand_device());
}

mather_plate::~mather_plate()
{
	delete[] file_name;
	fd.close();
}
