#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_table
{
	int 			number_of_philosophers;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t *all_fork;
	bool			simulation_running;
	unsigned long	time_start;
	pthread_mutex_t	write_action;
} t_table;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
	int				quantity_eat;
	pthread_mutex_t	eat_now;
	long			eat_last_time;
	t_table			*table;
} t_philo;

typedef enum e_action
{
	THINKING,
	EATING,
    SLEEPING,
    DIED,
	HUNGRY
} t_action;

void    *routine(void *data);
unsigned long ft_get_time();
void    print_action(t_action action, t_philo *philo);
void sleep_routine(int time_sleep);
void    leave_forks(t_philo *philo);
void    get_forks(t_philo *philo);
void   eat_routine(t_philo *philo);



#endif