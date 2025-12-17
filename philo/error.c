/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:39:35 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/08/20 11:39:35 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

/*Función error de argumentos*/
int	arg_error(void)
{
	ft_putstr_fd("\033[31mError: invalid number of arguments\n\033[0m", 2);
	ft_putstr_fd("Usage:\t ./philo number_of_philosophers time_to_die ", 2);
	ft_putstr_fd("time_to_eat time_to_sleep [number_of_meals]\n", 2);
	return (1);
}

/*Función error principal*/
int	ft_error(char *message)
{
	ft_putstr_fd("\033[31mError: \n\033[0m", 2);
	ft_putstr_fd(message, 2);
	return (1);
}

/*Función de error oceano*/
void	error_exit(char *error)
{
	ft_putstr_fd("\033[31mError: \n\033[0m", 2);
	ft_putstr_fd(error, 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (arg_error());
	if (parse_args(&data, argv))
		return (1);
	printf("Philos: %d\n", data.number_of_philos);
	printf("Die: %d\n", data.time_to_die);
	printf("Eat: %d\n", data.time_to_eat);
	printf("Sleep: %d\n", data.time_to_sleep);
	printf("Must eat: %d\n", data.must_eat);
	return (0);
}
