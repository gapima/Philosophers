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

#include "philo.h"

void	ft_destroy(t_philo *philo)
{
	int			count;
	t_table		*table;

	count = 0;
	table = philo->table;
	pthread_mutex_destroy(&table->write_action);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->read_mutex);
	while (count < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo[count].eat_now);
		pthread_mutex_destroy(&table->all_fork[count]);
		count++;
	}
	free(philo);
	free(table->all_fork);
}

bool	bool_read_safe(bool *a, pthread_mutex_t *mutexes)
{
	bool	r;

	r = false;
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

void	int_inc_safe(int *n, pthread_mutex_t *mutexes)
{
	pthread_mutex_lock(mutexes);
	*n += 1;
	pthread_mutex_unlock(mutexes);
}

int int_read_safe(int *n, pthread_mutex_t *mutexes)
{
	int r;

	r = 0;
	pthread_mutex_lock(mutexes);
	r = *n;
	pthread_mutex_unlock(mutexes);
	return (r);
}

void	long_set_safe(long *dest, long n, pthread_mutex_t *mutexes)
{
	pthread_mutex_lock(mutexes);
	*dest = n;
	pthread_mutex_unlock(mutexes);
}
