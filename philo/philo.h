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
# define RST	"\033[0m"
# define R		"\033[1;31m"
# define G		"\033[1;32m"
# define Y		"\033[1;33m"
# define B		"\033[1;34m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"

# define DEBUG_MODE 0

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

// time_code -> SECONDS MILISECONDS MICROSECONDS
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
	t_data			*data;
	int				id;
	bool			full;
	long			meals;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
}	t_philo;

/*			DATA			*/
typedef struct s_data
{
	long				number_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				limit_meals;
	long				start_simulation;
	bool				end_simulation;
	bool				all_threads_ready;
	long				threads_running;
	pthread_t			monitor;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
	t_fork				*forks;
	t_philo				*philos;
}	t_data;

int		main(int argc, char **argv);

int		arg_error(void);
void	ft_error_exit(char *message);

int		parse_args(t_data *data, char **argv);

void	data_init(t_data *data);

void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
bool	simulation_finished(t_data *data);

void	wait_all_threads(t_data *data);
void	increase_long(pthread_mutex_t *mutex, long *value);
bool	all_threads_running(pthread_mutex_t *mutex,
			long *threads, long number_of_philos);
void	de_synchronize_philos(t_philo *philo);

long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_data *data);
void	clean(t_data *data);

void	write_status(t_philo_status status, t_philo *philo, bool debug);

void	*lone_philo(void *arg);

void	eat(t_philo *philo);
void	think(t_philo *philo, bool print);
void	*dinner_simulation(void *data);
void	dinner_start(t_data *data);

void	*monitor_dinner(void *data);

#endif