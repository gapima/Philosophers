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

#include "../include/philo.h"

static void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(HUNGRY, philo);
	philo_sleep(philo, philo->table->time_to_die);
	print_action(DIED, philo);
	pthread_mutex_unlock(philo->left_fork);
}

static void	eat_sleep_routine(t_philo *philo)
{
	take_forks(philo);
	print_action(EATING, philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	philo_sleep(philo, philo->table->time_to_eat);
	if (is_simulation_running(philo->table))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->meal_mutex);
	}
	print_action(SLEEPING, philo);
	release_forks(philo);
	philo_sleep(philo, philo->table->time_to_sleep);
}

void wait_all_threads(time_t start_time)
{
	while (ft_get_time() < start_time)
	{}
}

static void think_routine(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_mutex);
	time_to_think = (philo->table->time_to_die
		- (ft_get_time() - philo->last_meal)
		- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	print_action(THINKING, philo);
	philo_sleep(philo, time_to_think);
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = data;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = philo->table->simulation_start;
	pthread_mutex_unlock(&philo->meal_mutex);
	wait_all_threads(philo->table->simulation_start);
	if (philo->table->number_of_philosophers == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
	if ((philo->id + 1) % 2 == 1)
		think_routine(philo);
	while (is_simulation_running(philo->table))
	{
		eat_sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}
