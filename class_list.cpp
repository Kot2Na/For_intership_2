#include "header.h"
/*
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
	list();
	void	list_add_end(device *add);
	device *find_gpu();
	void	list_print_count();
	device *rand_device();
	void	list_destroy(node *head = NULL);
};
*/

list::list()
{
	i = 0;
	start = NULL;
}

void	list::list_add_end(device *add)
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

device *list::find_gpu()
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

void	list::list_print_count()
{
	node *head;

	head = this->start;
	while (head)
	{
		std::cout << head->cur->name << " was called " << head->cur->i << " times" << std::endl;
		head = head->next;
	}
}

device *list::rand_device()
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

void	list::list_destroy(node *head = NULL)
{
		
	if (!head)
		head = this->start;
	if (!head)
		return ;
	if (head->next)
		list_destroy(head->next);
	delete head;
}
