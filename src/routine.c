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
			break ;
		}
		pthread_mutex_unlock(&philo->eat_now);
	}
	return (NULL);
}

bool	bool_read_safe_a(t_table *table)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&table->read_mutex);
	r = table->all_ready < \
	table->number_of_philosophers;
	pthread_mutex_unlock(&table->read_mutex);
	return (r);
}

void	*routine(void *data)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = data;
	philo->eat_last_time = ft_get_time();
	bool_write_safe_b(philo->table);
	while (bool_read_safe_a(philo->table))
	{
	}
	pthread_create(&thread, NULL, check_died, philo);
	if (philo->table->number_of_philosophers == 1)
	{
		ft_one_philo(philo);
		pthread_join(thread, NULL);
		return (NULL);
	}
	while (bool_read_safe(philo->table))
	{
		eat_routine(philo);
		print_action(THINKING, philo);
		if (philo->table->number_of_philosophers % 2 == 1)
			sleep_routine(1);
	}
	pthread_join(thread, NULL);
	return (NULL);
}
