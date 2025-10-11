#include "philo.h"

/*
	./philo 5 800 200 200 [5]	
*/

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		// CORRECT INPUT
		// 1) errors checking, filling table
		parse_input(&table, argv);
		// 2) creating the actual thing
		data_init(&table);
		// 3)
		dinner_start(&table); //TODO
		// 4) No leaks -> philos full | 1 philo died
		clean(&table); //TODO
	}
	else
	{
		// ERROR
		error_exit("Wrong input:\n"
				G"Correct is ./philo 5 800 200 200 [5]"RST);
	}
}