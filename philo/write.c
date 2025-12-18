/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:57:07 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/18 13:57:07 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->data))
		printf(W "%6ld" RST " %d has taken the 1° fork \t" B "[ %d ]\n" RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->data))
		printf(W "%6ld" RST " %d has taken the 2° fork \t" B "[ %d ]\n" RST, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->data))
		printf(W "%6ld" M " %d is eating \t %ld\n" RST, elapsed, philo->id, philo->meals);
	else if (SLEEPING == status && !simulation_finished(philo->data))
		printf(W "%6ld" C " %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->data))
		printf(W "%6ld" Y " %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf(R "%6ld %d died\n" RST, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->data->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->data->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finished(philo->data))
			printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !simulation_finished(philo->data))
			printf(W"%-6ld"C" %d is eating\n"RST, elapsed, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->data))
			printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !simulation_finished(philo->data))
			printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf(R "%-6ld %d died\n" RST, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->data->write_mutex, UNLOCK);
}
