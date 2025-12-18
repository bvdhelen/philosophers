/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:34:00 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/17 21:34:00 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main_parsing(int argc, char **argv)
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
