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
	while (count < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo[count].eat_now);
		pthread_mutex_destroy(&table->all_fork[count]);
		count++;
	}
	free(philo);
	free(table->all_fork);
}

bool	bool_read_safe(t_table *table)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&table->read_mutex);
	r = table->simulation_running;
	pthread_mutex_unlock(&table->read_mutex);
	return (r);
}

void	bool_write_safe(t_table *table, bool val)
{
	pthread_mutex_lock(&table->read_mutex);
	table->simulation_running = val;
	pthread_mutex_unlock(&table->read_mutex);
}

void	bool_write_safe_b(t_table *table)
{
	pthread_mutex_lock(&table->read_mutex);
	table->all_ready++;
	pthread_mutex_unlock(&table->read_mutex);
}
