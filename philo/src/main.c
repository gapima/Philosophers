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
		philo[count].fork_left = &table->all_fork[count];
		philo[count].fork_right = &table->all_fork[(count + 1) % \
		table->number_of_philosophers];
		count++;
	}
}

void	*verify_philo_eat(void *data)
{
	t_table	*table;

	table = data;
	while (table->simulation_running)
	{
		pthread_mutex_lock(&table->how_philo_eat);
		if (table->quantity_have_philo \
		>= table->number_of_philosophers)
			table->simulation_running = false;
		pthread_mutex_unlock(&table->how_philo_eat);
	}
	return (NULL);
}

void	when_is_one_philo(t_philo *philo)
{
	
	pthread_create(&philo[0].thread_id, NULL, &routine, &philo[0]);
	pthread_detach(philo->thread_id);
	while (philo->table->simulation_running)
	{
		sleep_routine(0);
	}
	ft_destroy(philo);
}

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	*all_philo;

	if (ac < 5)
	{
		ft_putstr_fd("Deu ruim0\n", 1);
		return (1);
	}
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