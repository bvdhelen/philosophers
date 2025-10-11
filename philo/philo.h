/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:02:51 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/08/18 11:02:51 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_data;

int	parse_args(int argc, char **argv, t_data *data);

long	ft_atol(const char *str);
int		ft_isnumber(char *str);
int		ft_error(char *message);
int		arg_error(void);
void	ft_putstr_fd(char *s, int fd);

int	main(int argc, char **argv);

#endif