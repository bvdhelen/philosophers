/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:43:26 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/18 13:43:26 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		ft_error_exit("Gettimeofday failed");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		ft_error_exit("Wrong input to gettime!");
	return (1);
}

void	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(data))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
		start--;
	}
}

// 1) LOCKING FIRST AND SECOND FORK && WRITE THE STATUS
// 2) EATING: UPDATING THE LAST MEAL 
	// && UPDATING THE MEALS COUNTER && WRITE THE STATUS
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

void	clean(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->number_of_philos)
	{
		philo = data->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
		i++;
	}
	safe_mutex_handle(&data->write_mutex, DESTROY);
	safe_mutex_handle(&data->table_mutex, DESTROY);
	free(data->forks);
	free(data->philos);
}
