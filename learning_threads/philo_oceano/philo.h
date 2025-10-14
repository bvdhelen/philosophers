#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, usleep
#include <stdbool.h>
#include <pthread.h> //mutex : init destroy lock unlock
					// threads : create join detach
#include <sys/time.h> //gettimeofday
#include <limits.h> //INT_MAX
#include <errno.h> 

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage:
**	printf(R"This is red text"RST);
**	printf(B"This is blue text"RST);
** 	Remember to use RST to reset the color after setting it
*/

#define RST	"\033[0m"	// Reset to default color
#define R	"\033[1:31m"	// Bold Red
#define G	"\033[1:32m"	// Bold Green
#define Y	"\033[1:33m"	// Bold Yellow
#define B	"\033[1:34m"	// Bold Blue
#define M	"\033[1:35m"	// Bold Magenta
#define C	"\033[1:36m"	// Bold Cyan
#define W	"\033[1:37m"	// Bold White

/*
 * write function macro
*/
#define DEBUG_MODE 0

/*
 * PHILO STATES
*/
typedef enum	e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;


/*
 * OPCODE for mutex | thread functions
*/
typedef enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

/*
 * CODES for gettime
*/
typedef enum	e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

// STRUCTURES
// 2 arrays to model the problem: philos & forks
// fork = mutex

//CODE MORE READABLE, pero no se pueden usar variables globales
typedef	pthread_mutex_t	t_mtx;

typedef	struct	s_table	t_table;

/*			FORK			*/
typedef struct	s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

/*			PHILO			*/
typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time; // time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id; // a philo is a thread
	t_mtx		philo_mutex; // useful for races with the monitor
	t_table		*table;
}	t_philo;

/*			TABLE			*/
/*
	./philo 5 800 200 200 [5]	
*/
struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals; // [5] | FLAG if -1
	long	start_simulation; // time start
	bool	end_simulation; // a philo died or all philos full
	bool	all_threads_ready; // synchro philos
	t_mtx	table_mutex; // avoid races while reading from table
	t_mtx	write_mutex;
	t_fork	*forks; // array forks
	t_philo	*philos; // array philos
}	t_table;

// *** PROTOTYPES ***

// ** utils **
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);

void	write_status(t_philo_status status, t_philo *philo, bool debug);

// ** parsing **
void	parse_input(t_table *table, char **argv);

// ** data init **
void	data_init(t_table *table);

// ** safe functions **
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

// ** synchro utils **
void	wait_all_threads(t_table *table);

// ** setters and getters, very useful to write DRY code **
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_bool(t_mtx *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);
