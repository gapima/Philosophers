/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:03:00 by glima             #+#    #+#             */
/*   Updated: 2024/12/29 13:45:59 by glima            ###   ########.fr       */
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

int	ft_verify_onephilo(t_table *table, t_philo *all_philo)
{
	if (table->number_of_philosophers == 1)
	{
		when_is_one_philo(all_philo);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
