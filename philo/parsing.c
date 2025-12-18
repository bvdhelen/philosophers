/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:55:16 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/17 10:55:16 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
*	1) check for negatives
*	2) check if the number is legit
*	3) check for INT_MAX
*/

// MILISEGUNDOS
// MICROSEGUNDOS  = mili*1e3
// NANOSEGUNDOS = mili*1e6

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

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static long	ft_atol(char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	if (!str || !str[0])
		ft_error_exit("The input is not a correct digit\n");
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		ft_error_exit("Arguments must be positive integers\n");
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		ft_error_exit("The input is not a correct digit\n");
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		if (num > 2147483647)
			ft_error_exit("The value is too big, INT_MAX is the limit\n");
		i++;
	}
	if (str[i] != '\0')
		ft_error_exit("The input is not a correct digit\n");
	return (num);
}

// THE ARGUMENTS ARE IN MILLISECONDS
// But USLEEP wants MICROSECONS
int	parse_args(t_data *data, char **argv)
{
	data->number_of_philos = ft_atol(argv[1]);
	if (data->number_of_philos == 0)
		ft_error_exit("Number of philosophers must be greater than 0\n");
	data->time_to_die = ft_atol(argv[2]) * 1e3;
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (data->time_to_die < 60e3
		|| data->time_to_eat < 60e3
		|| data->time_to_sleep < 60e3)
		ft_error_exit("Use timestamps major than 60ms\n");
	data->limit_meals = -1;
	if (argv[5])
	{
		data->limit_meals = ft_atol(argv[5]);
		if (data->limit_meals == 0)
			ft_error_exit("Number of limit meals must be greater than 0\n");
	}
	return (0);
}
