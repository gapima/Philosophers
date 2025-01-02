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
	int_inc_safe(&philo->quantity_eat, &philo->eat_now);
	long_set_safe(&philo->eat_last_time, ft_get_time(), &philo->eat_now);
	sleep_routine(philo->table->time_to_eat);
	leave_forks(philo);
	if (philo->quantity_eat == \
	philo->table->number_of_times_each_philosopher_must_eat)
	{
		int_inc_safe(&philo->table->quantity_have_philo, &philo->table->read_mutex);
		int_inc_safe(&philo->quantity_eat, &philo->eat_now);
	}
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = data;
	philo->eat_last_time = ft_get_time();
	int_inc_safe(&philo->table->all_ready, &philo->table->read_mutex);
	while (!bool_thread_ready(philo->table)) {}
	while (bool_read_safe(&philo->table->simulation_running, &philo->table->read_mutex))
	{
		eat_routine(philo);
		print_action(THINKING, philo);
	}
	return (NULL);
}

bool	bool_thread_ready(t_table *table)
{
	int a;
	int b;

	a = int_read_safe(&table->all_ready, &table->read_mutex);
	b = int_read_safe(&table->number_of_philosophers, &table->read_mutex);
	return (a >= b);
}
