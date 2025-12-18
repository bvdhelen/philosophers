/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:29:08 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/18 15:29:08 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

 // IMPORTANTE: dice que t_to_die has to be converted back to milliseconds
static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	time_to_die = philo->data->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *table)
{
	int		i;
	t_data	*data;

	data = (t_data *)table;
	while (!all_threads_running(&data->table_mutex, &data->threads_running,
			data->number_of_philos))
		;
	while (!simulation_finished(data))
	{
		i = 0;
		while (i < data->number_of_philos && !simulation_finished(data))
		{
			if (philo_died(data->philos + i))
			{
				set_bool(&data->table_mutex, &data->end_simulation, true);
				write_status(DIED, data->philos + i, DEBUG_MODE);
			}
			i++;
		}
	}
	return (NULL);
}
