/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:49:42 by glima             #+#    #+#             */
/*   Updated: 2024/12/29 12:51:59 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL)
		return ;
	i = -1;
	while (s[++i] != '\0')
		ft_putchar_fd(s[i], fd);
}

long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
		return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
	exit(0);
}

void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_action(HUNGRY, philo);
	sleep_routine(philo->table->time_to_die);
	pthread_mutex_unlock(philo->fork_left);
}
