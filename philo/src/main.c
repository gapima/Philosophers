#include "philo.h"
#include <stdlib.h>

static	void ft_delegateFork(t_philo *philo)
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
	int		count;
	t_table	table;
	t_philo	*all_philo;

	table.number_of_times_each_philosopher_must_eat = 0;
	table.quantity_have_philo = 0;
	if (ac < 5)
	{
		ft_putstr_fd("Deu ruim0\n", 1);
		return (1);
	}
	table.number_of_philosophers = ft_atoi(av[1]);
	table.time_to_die = ft_atoi(av[2]);
	table.time_to_eat = ft_atoi(av[3]);
	table.time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&table.how_philo_eat, 0);
	if (ac > 5)
	{
		table.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		if (table.number_of_times_each_philosopher_must_eat <= 0)
		{
			ft_putstr_fd("\nDeu ruim1\n", 1);
			return (EXIT_FAILURE);
		}
		pthread_create(&table.verify_each_eat, NULL, verify_philo_eat, &table);
	}
	if (table.number_of_philosophers <= 0 || table.time_to_die <= 0 \
		|| table.time_to_eat <= 0 || table.time_to_sleep <= 0)
	{
		ft_putstr_fd("\nDeu ruim1\n", 1);
		return (EXIT_FAILURE);
	}
	all_philo = ft_calloc(table.number_of_philosophers, sizeof(t_philo));
	table.all_fork = ft_calloc(table.number_of_philosophers, \
	sizeof(pthread_mutex_t));
	count = 0;
	pthread_mutex_init(&table.write_action, 0);
	while (count < table.number_of_philosophers)
	{
		all_philo[count].id = count + 1;
		all_philo[count].table = &table;
		pthread_mutex_init(&all_philo[count].eat_now, 0);
		if (pthread_mutex_init(&table.all_fork[count], 0) < 0)
			return (EXIT_FAILURE);
		count++;
	}
	ft_delegateFork(all_philo);
	count = 0;
	table.time_start = ft_get_time();
	table.simulation_running = true;
	if (table.number_of_philosophers == 1)
	{
		when_is_one_philo(all_philo);
		return (EXIT_SUCCESS);
	}
	while (count < table.number_of_philosophers)
	{
		if (pthread_create(&all_philo[count].thread_id, NULL, \
			&routine, &all_philo[count]) != 0)
			return (EXIT_FAILURE);
		sleep_routine(1);
		count++;
	}
	count = 0;
	while (count < table.number_of_philosophers)
	{
		if (pthread_join(all_philo[count].thread_id, NULL) != 0)
			return (EXIT_FAILURE);
		count++;
	}
	if (ac > 5)
	{
		if (pthread_join(table.verify_each_eat, NULL) != 0)
			return (EXIT_FAILURE);
	}
	pthread_mutex_destroy(&table.how_philo_eat);
	ft_destroy(all_philo);
	return (EXIT_SUCCESS);
}