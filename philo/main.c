/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:34:53 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/17 21:34:53 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1) errors checking, filling table data
// 2) creating the actual thing
// 3) dinner
// 4) no leaks -> philos full | 1 philo died
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (arg_error());
	else
	{
		parse_args(&data, argv);
		data_init(&data);
		dinner_start(&data);
		clean(&data);
	}
	return (0);
}
