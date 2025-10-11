#include "philo.h"

/*
 * Module containing wrapper functions
 * with embedded controls on return
*/
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Error with the malloc");
	return (ret);
}

/*
 * Embed controls on return status
*/
static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid.");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error_exit("The process cannnot allocate enough memory to create another mutex.");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

// *** MUTEX SAFE ***
/*
 * init
 * destroy
 * lock
 * unlock
*/
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex));
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex));
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL));
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex));
	else
		error_exit("Wrong opcode for mutex handle");
}

// *** THREADS SAFE ***
/*
 * THREADS errors
*/
static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permission\n");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that"
				"specified by the given thread ID, thread.");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread.");
}

/*
 * One function to handle threads
 * create join detach
*/
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread handle:"
			" use <CREATE> <JOIN> <DETACH>");
}
