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

typedef struct s_table
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				all_ready;
	pthread_t		verify_each_eat;
	int				quantity_have_philo;
	pthread_mutex_t	how_philo_eat;
	pthread_mutex_t	*all_fork;
	bool			simulation_running;
	unsigned long	time_start;
	pthread_mutex_t	read_mutex;
	pthread_mutex_t	write_action;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	int				quantity_eat;
	pthread_mutex_t	eat_now;
	long			eat_last_time;
	t_table			*table;
}	t_philo;

typedef enum e_action
{
	THINKING,
	EATING,
	SLEEPING,
	DIED,
	HUNGRY
}	t_action;

void	*routine(void *data);
long	ft_get_time(void);
void	print_action(t_action action, t_philo *philo);
void	sleep_routine(int time_sleep);
void	leave_forks(t_philo *philo);
void	get_forks(t_philo *philo);
void	eat_routine(t_philo *philo);
void	ft_destroy(t_philo *philo);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
long	ft_atoi(const char *nptr);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*verify_philo_eat(void *data);
int		ft_init_args(t_table *table, int ac, char **av);
void	ft_delegate_fork(t_philo *philo);
int		ft_play(t_philo *all_philo, int count, t_table *table);
void	when_is_one_philo(t_philo *philo);
bool	bool_read_safe(t_table *table);
void	bool_write_safe(t_table *table, bool val);
void	bool_write_safe_b(t_table *table);
void	ft_one_philo(t_philo *philo);
void	ft_parsing(int ac);
int		ft_initmutex(t_table *table, t_philo *all_philo, int count);
int		ft_verify_onephilo(t_table *table, t_philo *all_philo);

#endif
