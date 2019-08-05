#include "header.h"

class mather_plate : device 
{
	char *file_name;
	std::ofstream fd;
public:
	list list_dev;

	mather_plate(const char *_name, const char *_file_name) : device(_name)
	{
		this->file_name = new char[255];
		strncpy(this->file_name, _file_name, strlen(_file_name) + 1);
		fd.open(this->file_name);
	}

	char *what_type()
	{
		char *type;

		type = new char[255];
		strncpy(type, typeid(*this).name(), strlen(typeid(*this).name()) + 1);
		return (type);
	}

	void registrate(device *item)
	{
		list_dev.list_add_end(item);
	}

	void action()
	{
		device *control;
		t_data data;

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

	device *new_control()
	{
		return (list_dev.rand_device());
	}

	~mather_plate()
	{
		delete[] file_name;
		fd.close();
	}
};

class gpu_plate : public device
{
public:
	
	gpu_plate(const char *_name) : device(_name)
	{
	}

	char *what_type()
	{
		char *type;

		type = new char[255];
		strncpy(type, typeid(*this).name(), strlen(typeid(*this).name()) + 1);
		return (type);
	}

	void action(t_data *data)
	{
		this->i += 1; 
		if (data)
			std::cout << data->data << std::endl;
		data->data = rand();
		data->dev = data->mather->new_control();
	}
	
	~gpu_plate()
	{
	}
};

class net_plate : public device
{
public:
	net_plate(const char *_name) : device(_name)
	{
	}

	char *what_type()
	{
		char *type;

		type = new char[255];
		strncpy(type, typeid(*this).name(), strlen(typeid(*this).name()) + 1);
		return (type);
	}

	void action(t_data *data)
	{
		this->i += 1; 
		sleep(0);
		data->data = rand();
		data->dev = data->mather->new_control();
	}

	~net_plate()
	{
	}
};

class hdd : public device
{
	char *file_name;
	std::ofstream fd;
public:
	hdd(const char *_name, const char *_file_name) : device(_name)
	{
		this->file_name = new char[255];
		strncpy(this->file_name, _file_name, strlen(_file_name) + 1);
		fd.open(this->file_name);
	}

	char *what_type()
	{
		char *type;

		type = new char[255];
		strncpy(type, typeid(*this).name(), strlen(typeid(*this).name()) + 1);
		return (type);
	}

	void action(t_data *data)
	{
		this->i += 1; 
		if (fd.is_open())
		{
			fd << data->data << std::endl;
		}
		data->data = rand();
		data->dev = data->mather->new_control();
	}

	~hdd()
	{
		delete[] file_name;
		fd.close();
	}
};

class keyboard : public device
{
	int fd;
public:
	keyboard(const char *_name) : device(_name)
	{
		fd = open("/dev/console", O_NOCTTY);
	}

	char *what_type()
	{
		char *type;

		type = new char[255];
		strncpy(type, typeid(*this).name(), strlen(typeid(*this).name()) + 1);
		return (type);
	}

	void action(t_data *data)
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

	~keyboard()
	{
		close(fd);
	}
};

int main()
{
	mather_plate main_dev("mather", "mather_data");
	gpu_plate first("gpu");
	net_plate second("net");
	hdd third("hdd", "hdd_data");
	keyboard fourth("keyboard");

	srand(101);
	
	main_dev.registrate(&first);
	main_dev.registrate(&second);
	main_dev.registrate(&third);
	main_dev.registrate(&fourth);

	main_dev.action();
	return (0);
}
