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
	if (philo->quantity_eat == \
	philo->table->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->table->how_philo_eat);
		philo->table->quantity_have_philo++;
		philo->quantity_eat++;
		pthread_mutex_unlock(&philo->table->how_philo_eat);
	}
}

void	*routine(void *data)
{
	t_philo		*philo;
	// pthread_t	thread;

	philo = data;
	philo->eat_last_time = ft_get_time();
	bool_inc_safe(&philo->table->all_ready, &philo->table->write_mutex);
	while (!bool_thread_ready(philo->table))
	{
	}
	// pthread_create(&thread, NULL, check_died, philo);
	while (bool_read_safe(&philo->table->simulation_running, &philo->table->read_mutex))
	{
		eat_routine(philo);
		print_action(THINKING, philo);
		if (philo->table->number_of_philosophers % 2 == 1)
			sleep_routine(1);
	}
	// pthread_join(thread, NULL);
	return (NULL);
}

bool	bool_thread_ready(t_table *table)
{
	bool	a;

	a = false;
	pthread_mutex_lock(&table->read_mutex);
	a = table->all_ready >= table->number_of_philosophers;
	pthread_mutex_unlock(&table->read_mutex);
	return (a);
}
