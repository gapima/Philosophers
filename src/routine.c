/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:48:14 by glima             #+#    #+#             */
/*   Updated: 2024/12/27 15:48:14 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
		return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
	exit(0);
}

void sleep_routine(int time_sleep)
{
	long	time_now;

	time_now = ft_get_time() + time_sleep;
	while (ft_get_time() < time_now)
	{
		usleep(time_sleep / 10);
	}
}

void	eat_routine(t_philo *philo)
{
	get_forks(philo);
	print_action(EATING, philo);
	pthread_mutex_lock(&philo->eat_now);
	philo->quantity_eat++;
	philo->eat_last_time = ft_get_time();
	sleep_routine(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->eat_now);
	leave_forks(philo);
	if (philo->quantity_eat == philo->table->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->table->how_philo_eat);
		philo->table->quantity_have_philo++;
		philo->quantity_eat++;
		pthread_mutex_unlock(&philo->table->how_philo_eat);
	}
}

bool bool_read_safe(t_table *table) {
	bool r;

	r = false;
	pthread_mutex_lock(&table->read_mutex);
	r = table->simulation_running;
	pthread_mutex_unlock(&table->read_mutex);
	return r;
}

void bool_write_safe(t_table *table, bool val) {
	pthread_mutex_lock(&table->read_mutex);
	table->simulation_running = val;
	pthread_mutex_unlock(&table->read_mutex);
}

void	*check_died(void *data)
{
	t_philo	*philo;

	philo = data;
	while (bool_read_safe(philo->table))
	{
		pthread_mutex_lock(&philo->eat_now);
		if ((ft_get_time() - philo->eat_last_time) >= philo->table->time_to_die)
		{
			print_action(DIED, philo);
			bool_write_safe(philo->table, false);
			pthread_mutex_unlock(&philo->eat_now);
			break;
		}
		pthread_mutex_unlock(&philo->eat_now);
	}
	return (NULL);
}

void ft_one_philo(t_philo *philo) {
	pthread_mutex_lock(philo->fork_left);
	print_action(HUNGRY, philo);
	sleep_routine(philo->table->time_to_die);
	pthread_mutex_unlock(philo->fork_left);
}

bool bool_read_safe_a(t_table *table) {
	bool r;

	r = false;
	pthread_mutex_lock(&table->read_mutex);
	r = table->all_ready < table->number_of_philosophers; 
	pthread_mutex_unlock(&table->read_mutex);
	return r;
}

void bool_write_safe_b(t_table *table) {
	pthread_mutex_lock(&table->read_mutex);
	table->all_ready++;
	pthread_mutex_unlock(&table->read_mutex);
}

void	*routine(void *data)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = data;
	philo->eat_last_time = ft_get_time();

	bool_write_safe_b(philo->table);
	while (bool_read_safe_a(philo->table)) {} 

	pthread_create(&thread, NULL, check_died, philo);
	if (philo->table->number_of_philosophers == 1) {
		ft_one_philo(philo);
		pthread_join(thread, NULL);
		return (NULL);
	}

	while (bool_read_safe(philo->table))
	{
		eat_routine(philo);
		print_action(THINKING, philo);
		if (philo->table->number_of_philosophers % 2 == 1) {
			sleep_routine(1);
		}
	}

	pthread_join(thread, NULL);
	return (NULL);
}
