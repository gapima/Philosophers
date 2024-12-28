/* ************************************************************************** */
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

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	char		*str;

	str = (char *)s;
	i = 0;
	while (i < n)
		str[i++] = c;
	return (s);
}

int	ft_init_args(t_table *table, int ac, char **av)
{
	table->number_of_times_each_philosopher_must_eat = 0;
	table->quantity_have_philo = 0;
	table->number_of_philosophers = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&table->how_philo_eat, 0);
	if (ac > 5)
	{
		table->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		if (table->number_of_times_each_philosopher_must_eat <= 0)
		{
			ft_putstr_fd("\nDeu ruim1\n", 1);
			return (EXIT_FAILURE);
		}
		pthread_create(&table->verify_each_eat, NULL, verify_philo_eat, table);
	}
	if (table->number_of_philosophers <= 0 || table->time_to_die < 0 \
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
	{
		ft_putstr_fd("\nDeu ruim1\n", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_play(t_philo *all_philo, int count, t_table *table)
{
	table->all_fork = ft_calloc(table->number_of_philosophers, \
	sizeof(pthread_mutex_t));
	count = 0;
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
	ft_delegateFork(all_philo);
	count = 0;
	table->time_start = ft_get_time();
	if (table->number_of_philosophers == 1)
	{
		when_is_one_philo(all_philo);
		return (EXIT_SUCCESS);
	}
	while (count < table->number_of_philosophers)
	{
		if (pthread_create(&all_philo[count].thread_id, NULL, \
			&routine, &all_philo[count]) != 0)
			return (EXIT_FAILURE);
		/*sleep_routine(1);*/
		count++;
	}
	count = 0;
	while (count < table->number_of_philosophers)
	{
		if (pthread_join(all_philo[count].thread_id, NULL) != 0)
			return (EXIT_FAILURE);
		count++;
	}
	return (EXIT_SUCCESS);
}
