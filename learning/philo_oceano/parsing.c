#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return (c >= 9 && c <= 13) || (c == 32);
}

/*
*	1) check for negatives
*	2) check if the number is legit
*	3) check for INT_MAX
*/

static const char	*valid_input(const char *str)
{
	int		len;
	const char	*number;

	len = 0;
	//1) skip spaces
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Feed me only positive values!");
	if (!is_digit(*str))
		error_exit("The input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("The value is too big, INT_MAX is the limit");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MEX is the limit");
	return (num);
}

/*
*	./philo 5 800 200 200 [5]	
*	
*	1) actual numbers
*	2) not > INT_MAX
*	3) timestamps > 60ms
*
*	USLEEP function want usec (* 1000)
*	60000 = 6e4
*/

void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3; //CONVIRTIENDO A MICROSEGUNDOS
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Use timestamps major than 60ms");
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}
