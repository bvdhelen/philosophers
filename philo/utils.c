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

void	ft_putstr_fd(char *s, int fd)
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

int	ft_isnumber(char *str)
{
	char	c;
	int		i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		c = str[i];
		if (c >= '0' && c <= '9')
			return (1);
		i++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + str[i] - '0';
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return (result);
}
