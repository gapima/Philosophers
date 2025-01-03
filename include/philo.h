/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:47:31 by glima             #+#    #+#             */
/*   Updated: 2024/12/27 15:47:31 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo t_philo;

typedef struct s_table
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_amt;
	bool			simulation_running;
	time_t		simulation_start;
	pthread_t	check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	check_sim_mutex;
	t_philo *philosophers;
}	t_table;

typedef struct s_philo
{
	pthread_t	thread_id;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	int			meal_count;
	time_t	last_meal;
	t_table			*table;
}	t_philo;

typedef enum e_action
{
	THINKING,
	EATING,
	DIED,
	HUNGRY,
	SLEEPING
}	t_action;

void	*verify_philo_eat(void *data);
void	*routine(void *data);
void	*routine_died(void *data);
void	eat_routine(t_philo *philo);
int		ft_play(t_table *table);
void	philo_sleep(t_philo *philo, time_t time);

void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);

void	print_action(t_action action, t_philo *philo);

void	ft_destroy(t_table *table);
long	ft_atoi(const char *nptr);

int		ft_init_args(t_table *table, int ac, char **av);
int		ft_initmutex(t_table *table);
void	ft_delegate_fork(t_philo *philo);
void	ft_parsing(int ac);
time_t	ft_get_time(void);

bool	bool_read_safe(bool *a, pthread_mutex_t *mutexes);
void	bool_write_safe(bool *a, bool val, pthread_mutex_t *mutexes);
bool is_simulation_running(t_table *table);
void wait_all_threads(time_t start_time);
#endif
