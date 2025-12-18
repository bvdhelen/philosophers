/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:26:48 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/18 12:26:48 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*safe_malloc(size_t bytes);
void		safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void		safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
static void	handle_mutex_error(int status, t_opcode opcode);
static void	handle_thread_error(int status, t_opcode opcode);

void	*safe_malloc(size_t bytes)
{
	void	*result;

	result = malloc(bytes);
	if (!result)
		ft_error_exit("malloc error\n");
	return (result);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK || opcode == DESTROY))
		ft_error_exit("The value specified by mutex is invalid.\n");
	else if (status == EINVAL && opcode == INIT)
		ft_error_exit("The value specified by attr is invalid.\n");
	else if (status == EDEADLK)
		ft_error_exit("A deadlock would occur if the thread blocked waiting for mutex.\n");
	else if (status == EPERM)
		ft_error_exit("The current thread does not hold a lock on mutex.\n");
	else if (status == ENOMEM)
		ft_error_exit("The process cannnot allocate enough memory to create another mutex.\n");
	else if (status == EBUSY)
		ft_error_exit("Mutex is locked\n");
}

void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		ft_error_exit("Wrong opcode for mutex handle\n");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		ft_error_exit("No resources to create another thread\n");
	else if (status == EPERM)
		ft_error_exit("The caller does not have appropriate permission\n");
	else if (status == EINVAL && opcode == CREATE)
		ft_error_exit("The value specified by attr is invalid.\n");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		ft_error_exit("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		ft_error_exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.\n");
	else if (status == EDEADLK)
		ft_error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread.\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		ft_error_exit("Wrong opcode for thread handle:"
			" use <CREATE> <JOIN> <DETACH>\n");
}
