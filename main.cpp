#include "header.h"

int main()
{
	mather_plate	main_dev("mather", "mather_data");
	gpu_plate		first("gpu");
	net_plate		second("net");
	hdd				third("hdd", "hdd_data");
	keyboard		fourth("keyboard");

	srand(101);

	main_dev.registrate(&first);
	main_dev.registrate(&second);
	main_dev.registrate(&third);
	main_dev.registrate(&fourth);

	main_dev.action(NULL);
	return (0);
}
