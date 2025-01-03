/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:48:22 by glima             #+#    #+#             */
/*   Updated: 2024/12/27 15:48:22 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_initmutex(t_table *table)
{
	int idx;
	t_philo *philo;

	philo = table->philosophers;
	idx = -1;
	while (++idx < table->number_of_philosophers)
	{
		philo[idx].id = idx + 1;
		philo[idx].table = table;
		pthread_mutex_init(&philo[idx].meal_mutex, 0);
		if (pthread_mutex_init(&table->forks[idx], 0) < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_init_args(t_table *table, int ac, char **av)
{
	table->simulation_running = true;
	table->must_eat_amt = -1;
	table->number_of_philosophers = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac > 5)
	{
		table->must_eat_amt = ft_atoi(av[5]);
		if (table->must_eat_amt <= 0)
		{
			printf("negative parameter and zero will be invalid\n");
			return (EXIT_FAILURE);
		}
	}
	if (table->number_of_philosophers <= 0 ||
			table->time_to_die < 0 || 
			table->time_to_eat < 0 ||
			table->time_to_sleep < 0)
	{
		printf("negative parameter and zero will be invalid\n");
		return (EXIT_FAILURE);
	}
	pthread_mutex_init(&table->write_mutex, 0);
	pthread_mutex_init(&table->check_sim_mutex, 0);
	table->forks = malloc(table->number_of_philosophers * sizeof(pthread_mutex_t));
	table->philosophers = malloc(table->number_of_philosophers * sizeof(t_philo));
	return (ft_initmutex(table));
}


static bool check_philo_died(t_philo *philo)
{
	time_t	time;

	time = ft_get_time();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		print_action(DIED, philo);
		bool_write_safe(&philo->table->simulation_running, false, &philo->table->check_sim_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (true);
	}
	return (false);
}

static bool should_stop(t_table *table)
{
	int	idx;
	bool stop;

	stop = true;
	idx = -1;
	while (++idx < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->philosophers[idx].meal_mutex);
		if (check_philo_died(&table->philosophers[idx]))
			return (true);
		if (table->must_eat_amt != -1)
		{
			if (table->philosophers[idx].meal_count < table->must_eat_amt)
				stop = false;
		}
		pthread_mutex_unlock(&table->philosophers[idx].meal_mutex);
	}
	if (table->must_eat_amt != -1 && stop)
	{
		bool_write_safe(&table->simulation_running, false, &table->check_sim_mutex);
		return (true);
	}
	return (false);
}

void *manager(void *data)
{
	t_table *table;

	table = data;
	bool_write_safe(&table->simulation_running, true, &table->check_sim_mutex);
	wait_all_threads(table->simulation_start);
	while (1)
	{
		if (should_stop(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	ft_play(t_table *table)
{
	t_philo *philos;
	int			count;

	philos = table->philosophers; 
	ft_delegate_fork(philos);
	table->simulation_start = ft_get_time() + (table->number_of_philosophers * 2 * 10);
	count = -1;
	while (++count < table->number_of_philosophers)
	{
		if (pthread_create(&philos[count].thread_id, NULL, &routine, &philos[count]) != 0)
			return (EXIT_FAILURE);
	}
	if (table->number_of_philosophers > 1)
		pthread_create(&table->check, NULL, &manager, table);
	count = -1;
	while (++count < table->number_of_philosophers)
		if (pthread_join(philos[count].thread_id, NULL) != 0)
			return (EXIT_FAILURE);

	if (table->number_of_philosophers > 1)
		if (pthread_join(table->check, NULL) != 0)
			return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
