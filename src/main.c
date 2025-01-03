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

#include "../include/philo.h"

void	ft_delegate_fork(t_philo *philo)
{
	int		count;
	t_table	*table;

	count = -1;
	table = philo->table;
	while (++count < table->number_of_philosophers)
	{
		if (count % 2 == 1)
		{
			philo[count].left_fork = &table->forks[count];
			philo[count].right_fork = &table->forks[(count + 1) % \
				table->number_of_philosophers];
		}
		else
		{
			philo[count].left_fork = &table->forks[(count + 1) % \
				table->number_of_philosophers];
			philo[count].right_fork = &table->forks[count];
		}
	}
}

int	main(int ac, char **av)
{
	t_table	table;

	ft_parsing(ac);
	if (ft_init_args(&table, ac, av) != 0) return (EXIT_FAILURE);
	if (ft_play(&table)) return (EXIT_FAILURE);
	ft_destroy(&table);
	return (EXIT_SUCCESS);
}
