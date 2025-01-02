/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:03:00 by glima             #+#    #+#             */
/*   Updated: 2025/01/02 16:59:54 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_parsing(int ac)
{
	if (ac < 5)
	{
		ft_putstr_fd("Usage: number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]", 1);
		exit (0);
	}
	if (ac > 6)
	{
		ft_putstr_fd("Too many arguments", 1);
		exit (0);
	}
}

int	ft_initmutex(t_table *table, t_philo *all_philo, int count)
{
	pthread_mutex_init(&table->write_action, 0);
	while (count < table->number_of_philosophers)
	{
		all_philo[count].id = count + 1;
		all_philo[count].table = table;
		pthread_mutex_init(&all_philo[count].eat_now, 0);
		if (pthread_mutex_init(&table->all_fork[count], 0) < 0)
			return (EXIT_FAILURE);
		count++;
	}
	return (EXIT_SUCCESS);
}

void	*routine_died(void *data)
{
	t_philo		*philo;
	t_table		*table;
	int				i;

	philo = data;
	table = philo->table;
	while (!bool_thread_ready(table))
	{
	}
	while (bool_read_safe(&table->simulation_running, &table->read_mutex))
	{
		i = -1;
		while (++i < table->number_of_philosophers)
		{
			pthread_mutex_lock(&philo[i].eat_now);
			if ((ft_get_time() - philo[i].eat_last_time) >= table->time_to_die)
			{
				print_action(DIED, &philo[i]);
				bool_write_safe(&table->simulation_running, false, &table->write_mutex);
				pthread_mutex_unlock(&philo[i].eat_now);
				break ;
			}
			pthread_mutex_unlock(&philo[i].eat_now);
		}
	}
	return (NULL);
}
