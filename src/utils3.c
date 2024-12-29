/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:03:00 by glima             #+#    #+#             */
/*   Updated: 2024/12/29 13:05:19 by glima            ###   ########.fr       */
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
