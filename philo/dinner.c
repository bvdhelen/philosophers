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

// 1) LOCKING FIRST AND SECOND FORK && WRITE THE STATUS
// 2) EATING: UPDATING THE LAST MEAL && UPDATING THE MEALS COUNTER && WRITE THE STATUS
// 3) SLEEP FOR THE AMOUNT OF TIME REQUESTED (TIME EATING)
	// && CHECK IF WE REACH THE FULL CONDITION
// 4) UNLOCKING FIRST AND SECOND FORK
void	eat(t_philo *philo)
{
	
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->limit_meals > 0
		&& philo->meals == philo->data->limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	think(t_philo *philo, bool print)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (print)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->data->number_of_philos % 2 == 0)
		return ;
	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.5, philo->data);
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
	int	i;

	i = 0;
	if (data->limit_meals == 0)
		return ;
	else if (data->number_of_philos == 1)
		safe_thread_handle(&data->philos[0].thread_id, lone_philo,
		&data->philos[0], CREATE);
	else
	{
		while (i < data->number_of_philos)
		{
			safe_thread_handle(&data->philos[i].thread_id, dinner_simulation,
				&data->philos[i], CREATE);
			i++;
		}
	}
	safe_thread_handle(&data->monitor, monitor_dinner, data, CREATE);
	data->start_simulation = gettime(MILLISECOND);
	set_bool(&data->table_mutex, &data->all_threads_ready, true);
	i = 0;
	while (i < data->number_of_philos)
	{
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	set_bool(&data->table_mutex, &data->end_simulation, true);
	safe_thread_handle(&data->monitor, NULL, NULL, JOIN);
}
