/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:48:10 by glima             #+#    #+#             */
/*   Updated: 2024/12/27 15:48:10 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(HUNGRY, philo);
	pthread_mutex_lock(philo->right_fork);
	print_action(HUNGRY, philo);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

bool is_simulation_running(t_table *table)
{
	return (bool_read_safe(&table->simulation_running, &table->check_sim_mutex));
}

void	philo_sleep(t_philo *philo, time_t time)
{
	time_t wakeup_time;

	wakeup_time = ft_get_time() + time;
	while (ft_get_time() < wakeup_time)
	{
		if (!is_simulation_running(philo->table))
			break;
		usleep(100);
	}
}
