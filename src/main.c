/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:48:07 by glima             #+#    #+#             */
/*   Updated: 2024/12/27 15:48:07 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	ft_delegateFork(t_philo *philo)
{
	int		count;
	t_table	*table;

	count = 0;
	table = philo->table;
	while (count < table->number_of_philosophers)
	{
		if (count % 2 == 0) {
			philo[count].fork_left = &table->all_fork[count];
			philo[count].fork_right = &table->all_fork[(count + 1) % \
				table->number_of_philosophers];
		} else {
			philo[count].fork_right = &table->all_fork[count];
			philo[count].fork_left = &table->all_fork[(count + 1) % \
				table->number_of_philosophers];
		}
		count++;
	}
}

void	*verify_philo_eat(void *data)
{
	t_table	*table;

	table = data;
	while (bool_read_safe(table))
	{
		pthread_mutex_lock(&table->how_philo_eat);
		if (table->quantity_have_philo >= table->number_of_philosophers) {
			bool_write_safe(table, false);
		}
		pthread_mutex_unlock(&table->how_philo_eat);
	}
	return (NULL);
}

void	when_is_one_philo(t_philo *philo)
{
	pthread_create(&philo[0].thread_id, NULL, &routine, &philo[0]);
	pthread_join(philo->thread_id, NULL);
}

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	*all_philo;

	table.simulation_running = true;
	if (ac < 5)
	{
		ft_putstr_fd("Usage: number_of_philosophers time_to_die "
				"time_to_eat time_to_sleep "
				"[number_of_times_each_philosopher_must_eat]", 1);
		return (EXIT_FAILURE);
	}
	if (ac > 6)
	{
		ft_putstr_fd("Too many arguments", 1);
		return (EXIT_FAILURE);
	}
	pthread_mutex_init(&table.read_mutex, 0);
	if (ft_init_args(&table, ac, av) != 0)
		return (EXIT_FAILURE);
	all_philo = ft_calloc(table.number_of_philosophers, sizeof(t_philo));
	if (ft_play(all_philo, 0,&table))
		return (EXIT_FAILURE);
	if (ac > 5)
	{
		if (pthread_join(table.verify_each_eat, NULL) != 0)
			return (EXIT_FAILURE);
	}
	pthread_mutex_destroy(&table.how_philo_eat);
	ft_destroy(all_philo);
	return (EXIT_SUCCESS);
}
