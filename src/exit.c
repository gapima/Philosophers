/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:48:03 by glima             #+#    #+#             */
/*   Updated: 2024/12/27 15:48:03 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_destroy(t_table *table)
{
	int				count;
	t_philo		*philo;

	philo = table->philosophers;
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->check_sim_mutex);
	count = -1;
	while (++count < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo[count].meal_mutex);
		pthread_mutex_destroy(&table->forks[count]);
	}
	free(philo);
	free(table->forks);
}

bool	bool_read_safe(bool *a, pthread_mutex_t *mutexes)
{
	bool	r;

	r = true;
	pthread_mutex_lock(mutexes);
	r = *a;
	pthread_mutex_unlock(mutexes);
	return (r);
}

void	bool_write_safe(bool *a, bool val, pthread_mutex_t *mutexes)
{
	pthread_mutex_lock(mutexes);
	*a = val;
	pthread_mutex_unlock(mutexes);
}
