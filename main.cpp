#include <iostream>

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
		strcpy_s(this->name, strlen(_name) + 1, _name);
	}

	void call_name()
	{
		std::cout << this->name << std::endl;
	}

	virtual char *what_type()
	{
		char *type;

		type = new char[255];
		strcpy_s(type, strlen(typeid(this).name()) + 1, typeid(this).name());
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
public:
	list list_dev;

	mather_plate(const char *_name) : device(_name)
	{
	}

	char *what_type()
	{
		char *type;

		type = new char[255];
		strcpy_s(type, strlen(typeid(*this).name()) + 1, typeid(*this).name());
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
			control->action(&data);
			control = data.dev;
			if (control)
				this->i += 1;
			else
				return ;
		}
	}

	device *new_control()
	{
		return (list_dev.rand_device());
	}

	void call_device()
	{
		list_dev.list_print();
	}

	void call_type()
	{
		list_dev.list_print_type();
	}

	void destr()
	{
		list_dev.list_destroy();
	}

	~mather_plate()
	{
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
		strcpy_s(type, strlen(typeid(*this).name()) + 1, typeid(*this).name());
		return (type);
	}

	void action(t_data *data)
	{
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
		strcpy_s(type, strlen(typeid(*this).name()) + 1, typeid(*this).name());
		return (type);
	}

	void action(t_data *data)
	{
		std::cout << "net is work" << std::endl;
		data->data = rand();
		data->dev = data->mather->new_control();
	}

	~net_plate()
	{
	}
};

class hdd : public device
{
public:
	hdd(const char *_name) : device(_name)
	{
	}

	char *what_type()
	{
		char *type;

		type = new char[255];
		strcpy_s(type, strlen(typeid(*this).name()) + 1, typeid(*this).name());
		return (type);
	}

	void action(t_data *data)
	{
		std::cout << "hdd is work" << std::endl;
		data->data = rand();
		data->dev = data->mather->new_control();
	}

	~hdd()
	{
	}
};

class keyboard : public device
{
public:
	keyboard(const char *_name) : device(_name)
	{
	}

	char *what_type()
	{
		char *type;

		type = new char[255];
		strcpy_s(type, strlen(typeid(*this).name()) + 1, typeid(*this).name());
		return (type);
	}

	void action(t_data *data)
	{
		std::cout << "keyboard is work" << std::endl;
		data->data = rand();
		data->dev = data->mather->new_control();
	}

	~keyboard()
	{
	}
};

int main()
{
	mather_plate main_dev("mather");
	gpu_plate first("gpu");
	net_plate second("net");
	hdd third("hdd");
	keyboard fourth("keyboard");
	
	main_dev.registrate(&first);
	main_dev.registrate(&second);
	main_dev.registrate(&third);
	main_dev.registrate(&fourth);

	main_dev.action();

	main_dev.destr();
	return (0);
}
