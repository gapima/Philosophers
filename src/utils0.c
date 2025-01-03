/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:48:17 by glima             #+#    #+#             */
/*   Updated: 2024/12/27 15:48:17 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atoi(const char *nptr)
{
	long	n;
	int		sign;

	sign = 1;
	n = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr)
	{
		if (!(*nptr >= 48 && *nptr <= 57))
			return (n * sign);
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}

time_t ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
		return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
	exit(0);
}

void	ft_parsing(int ac)
{
	if (ac < 5)
	{
		printf("Usage: number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
		exit (0);
	}
	if (ac > 6)
	{
		printf("Too many arguments\n");
		exit (0);
	}
}

void	print_action(t_action action, t_philo *philo)
{
	time_t time_now;

	pthread_mutex_lock(&philo->table->write_mutex);
	if (!is_simulation_running(philo->table))
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	time_now = ft_get_time() - philo->table->simulation_start;
	printf("%ld %d ", time_now, philo->id);
	if (action == DIED)
		printf("died\n");
	else if (action == EATING)
		printf("is eating\n");
	else if (action == SLEEPING)
		printf("is sleeping\n");
	else if (action == THINKING)
		printf("is thinking\n");
	else if (action == HUNGRY)
		printf("%s\n", "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_mutex);
}

