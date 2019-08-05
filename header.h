#ifndef HEADER_H
# define HEADER_H

#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

class device
{
public:
	char			*name;
	int				i;

	typedef struct	s_data
	{
		device		*dev;
		device		*mather;
		int			data;
	}				t_data;

					device(const char *_name);
	void 			call_name();
	virtual char 	*what_type();
	virtual void 	action(t_data *data);
	virtual device 	*new_control();
					~device();
};

class node
{
	class device	*cur;
	class node		*next;
	friend class	list;
};

class list
{
	node			*start;
	int				i;
public:
	friend class	node;
					list();
	void			list_add_end(device *add);
	device			*find_gpu();
	void			list_print_count();
	device			*rand_device();
	void			list_destroy(node *head);
};

class mather_plate : device 
{
	char			*file_name;
	std::ofstream	fd;
public:
	list			list_dev;
					mather_plate(const char *_name, const char *_file_name);
	char			*what_type();
	void			registrate(device *item);
	void			action();
	device			*new_control();
					~mather_plate();
};

class gpu_plate : public device
{
public:
					gpu_plate(const char *_name);
	char			*what_type();
	void			action(t_data *data);
					~gpu_plate();
};

class net_plate : public device
{
public:
					net_plate(const char *_name);
	char			*what_type();
	void			action(t_data *data);
					~net_plate();
};

class hdd : public device
{
	char			*file_name;
	std::ofstream	fd;
public:
					hdd(const char *_name, const char *_file_name);
	char			*what_type();
	void			action(t_data *data);
					~hdd();
};

class keyboard : public device
{
	int				fd;
public:
					keyboard(const char *_name);
	char			*what_type();
	void			action(t_data *data);
					~keyboard();
};

#endif
