/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:13:17 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/18 12:13:17 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position);
static void	philo_init(t_data *data);
void		data_init(t_data *data);

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	number_of_philos;

	number_of_philos = philo->data->number_of_philos;
	philo->first_fork = &forks[(philo_position + 1) % number_of_philos];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0 || philo->id == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % number_of_philos];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->number_of_philos)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->data = data;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, data->forks, i);
		i++;
	}
}

void	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->end_simulation = false;
	data->all_threads_ready = false;
	data->threads_running = 0;
	data->philos = safe_malloc(sizeof (t_philo) * data->number_of_philos);
	data->forks = safe_malloc(sizeof (t_fork) * data->number_of_philos);
	safe_mutex_handle(&data->table_mutex, INIT);
	safe_mutex_handle(&data->write_mutex, INIT);
	while (i < data->number_of_philos)
	{
		safe_mutex_handle(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
		i++;
	}
	philo_init(data);
}
