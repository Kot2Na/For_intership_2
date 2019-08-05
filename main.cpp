#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

class device
{
public:
	char		*name;
	int			i;

public:

	typedef struct	s_data
	{
		device		*dev;
		device		*mather;
		int			data;
	}				t_data;

	device(const char *_name)
	{
		i = 0;
		this->name = new char[255];
		strncpy(this->name, _name, strlen(_name) + 1);
	}

	void call_name()
	{
		std::cout << this->name << std::endl;
	}

	virtual char *what_type()
	{
		char *type;

		type = new char[255];
		strncpy(type, typeid(this).name(), strlen(typeid(this).name() + 1));
		return (type);
	}

	virtual void action(t_data *data)
	{
	}

	virtual device *new_control()
	{
		return (NULL);
	}

	~device()
	{
		delete[] this->name;
	}
};

class node
{
	class device	*cur;
	class node		*next;
	friend class	list;
};

class list
{
	node *start;
	int i;
public:

	list()
	{
		i = 0;
		start = NULL;
	}

	void	list_add_end(device *add)
	{
		node *elem;
		node *head;

		head = this->start;
		elem = new node();
		elem->cur = add;
		elem->next = NULL;
		if (!head)
		{
			start = elem;
		}
		else
		{
			while (head->next)
				head = head->next;
			head->next = elem;
		}
		this->i += 1;
	}
/*
	void	list_print()
	{
		node *head;

		head = this->start;
		while (head)
		{
			head->cur->call_name();
			head = head->next;
		}
	}

	void	list_print_type()
	{
		node *head;
		char *type;

		head = this->start;
		while (head)
		{
			type = head->cur->what_type();
			std::cout << type << std::endl;
			delete[] type;
			head = head->next;
		}
	}
*/
	device *find_gpu()
	{
		node *head;

		head = this->start;
		while (head)
		{
			if (strcmp("class gpu_plate", typeid(*(head->cur)).name()) == 0)
				return (head->cur);
			head = head->next;
		}
		return (this->start->cur);
	}

	void	list_print_count()
	{
		node *head;

		head = this->start;
		while (head)
		{
			std::cout << head->cur->name << " was called " << head->cur->i << " times" << std::endl;
			head = head->next;
		}
	}

	device *rand_device()
	{
		node *head;
		int num;
		int k;

		head = this->start;
		if (this->i > 0)
		{
			k = 0;
			num = rand() % this->i;
			while (head && k < num)
			{
				head = head->next;
				k++;
			}
		}
		return (head ? head->cur : NULL);
	}


	void	list_destroy(node *head = NULL)
	{

		if (!head)
			head = this->start;
		if (!head)
			return ;
		if (head->next)
			list_destroy(head->next);
		delete head;
	}
};

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
		list_dev.list_destroy();
	}

	device *new_control()
	{
		return (list_dev.rand_device());
	}
/*
	void call_device()
	{
		list_dev.list_print();
	}

	void call_type()
	{
		list_dev.list_print_type();
	}
*/
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
