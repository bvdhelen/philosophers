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
	ft_putstr_fd(MAGENTA"Error: invalid number of arguments\n"RESET, 2);
	ft_putstr_fd("Usage:\t ./philo number_of_philosophers time_to_die ", 2);
	ft_putstr_fd("time_to_eat time_to_sleep [number_of_meals]\n", 2);
	return (1);
}

/*Función de error principal*/
void	ft_error_exit(char *message)
{
	ft_putstr_fd(RED"Error: \n"RESET, 2);
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}
