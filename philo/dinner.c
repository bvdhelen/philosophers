/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:18:00 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/18 13:18:00 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->data->table_mutex, &philo->data->threads_running);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->data))
		precise_usleep(philo->data->time_to_die, philo->data);
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->data->table_mutex, &philo->data->threads_running);
	de_synchronize_philos(philo);
	while (!simulation_finished(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		think(philo, true);
	}
	return (NULL);
}

static void	create_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		safe_thread_handle(&data->philos[i].thread_id, dinner_simulation,
			&data->philos[i], CREATE);
		i++;
	}
}

static void	join_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}

/* 
 * 0) If no meals, return -> [0]
 * 0.1) If only one philo -> ad hoc function
 * 1) Create all threads, all philos
 * 2) Create a monitor thread -> deads
 * 3) Synchronize the begginning of the simulation
 * 		pthread_create -> philo starts running!
 * 		every philo start simultaneously
 * 4) JOIN everyone
*/
void	dinner_start(t_data *data)
{
	if (data->limit_meals == 0)
		return ;
	else if (data->number_of_philos == 1)
		safe_thread_handle(&data->philos[0].thread_id, lone_philo,
			&data->philos[0], CREATE);
	else
		create_philo_threads(data);
	safe_thread_handle(&data->monitor, monitor_dinner, data, CREATE);
	data->start_simulation = gettime(MILLISECOND);
	set_bool(&data->table_mutex, &data->all_threads_ready, true);
	join_philo_threads(data);
	set_bool(&data->table_mutex, &data->end_simulation, true);
	safe_thread_handle(&data->monitor, NULL, NULL, JOIN);
}
