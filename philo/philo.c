/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:02:36 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/08/18 11:02:36 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_data *data)
{
	if (!ft_isnumber(argv[1]) || !ft_isnumber(argv[2])
		|| !ft_isnumber(argv[3]) || !ft_isnumber(argv[4])
		|| (argc == 6 && !ft_isnumber(argv[5])))
		return (ft_error("arguments must be positive integers\n"));
	data->number_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atol(argv[5]);
	else
		data->must_eat = -1;
	if (data->number_of_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (argc == 6 && data->must_eat <= 0))
		return (ft_error("arguments must be grater than 0\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (arg_error());
	if (parse_args(argc, argv, &data) != 0)
		return (1);
	printf("Philos: %d\n", data.number_of_philos);
	printf("Die: %d\n", data.time_to_die);
	printf("Eat: %d\n", data.time_to_eat);
	printf("Sleep: %d\n", data.time_to_sleep);
	printf("Must eat: %d\n", data.must_eat);

	return (0);
}
