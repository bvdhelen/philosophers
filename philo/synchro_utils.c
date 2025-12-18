/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:39:04 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/18 13:39:04 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->table_mutex, &data->all_threads_ready))
		;
}

// Increase threads running to synchro with the monitor
void	increase_long(pthread_mutex_t *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

//  Monitor busy waits until all threads are running
bool	all_threads_running(pthread_mutex_t *mutex,
	long *threads, long number_of_philos)
{
	bool	result;

	result = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == number_of_philos)
		result = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (result);
}

// Make the system FAIR -> 30 ms (mitad del mínimo permitido)
void	de_synchronize_philos(t_philo *philo)
{
	if (philo->data->number_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(30e3, philo->data);
	}
	else
	{
		if (philo->id % 2)
			think(philo, false);
	}
}
