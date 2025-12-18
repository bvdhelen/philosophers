/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:02:51 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/08/18 11:02:51 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

/* COLOURS */
# define RESET		"\033[0m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"

# define DEBUG_MODE 1

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

/* -------- STRUCTURES --------- */

typedef struct s_data	t_data;

/*			FORKS			*/
typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}	t_fork;

/*			PHILO			*/
typedef struct s_philo
{
	int				id;
	bool			full;
	long			meals_counter;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_data			*data;
	//ptread_mutex_t	philo_mutex;
}	t_philo;

/*			DATA			*/
typedef struct s_data
{
	long		number_of_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		limit_meals;
	long		start_simulation;
	bool		end_simulation;
	//bool		all_threads_ready;
	//long		threads_running_nbr;
	//pthread_t	monitor;
	//t_mtx		table_mutex;
	//t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}	t_data;

int		main(int argc, char **argv);

int		parse_args(t_data *data, char **argv);

int		arg_error(void);
void	ft_error_exit(char *message);

#endif