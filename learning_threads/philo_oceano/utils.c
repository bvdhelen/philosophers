#include "philo.h"

// gettimeofday
/*
 * time_code -> SECONDS MILISECONDS MICROSECONDS
 *
*/
long	gettime(t_time_code time_code)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3))
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime!");
	return (1337);
}

/*
 * precise usleep, the real one suck
 * Why table? Is the simulation finished?
 * 1) usleep the majority of time, not CPU intensive
 * 2) refine last microsec with spinlock
*/
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long 	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		// to get a spinlock threshold
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			//SPINLOCK
			while (gettime(MICROSECOND) - start < usec)
				;
		}

		start--;
	}
}

void	error_exit(const char *error)
{
	printf(R" %s \n"RST, error);
	exit(EXIT_FAILURE);
}