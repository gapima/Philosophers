#include "philo.h"

static void *routine(void *data)
{
	t_table table;

}

static unsigned long ft_get_time()
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == 0)
		return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
	else
		perror("Erro ao obter o tempo");
	return (1);
}
static void ft_destroy(t_philo *philo)
{
	int			count;
	t_table 	*table;

	count = 0;
	table = philo->table;
	while (count < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo[count].eat_now);
		pthread_mutex_destroy(&table->all_fork[count]);
		count++;	
	}
	free(philo);
	free(table->all_fork);
}

static void ft_delegateFork(t_philo *philo)
{
	int			count;
	t_table 	*table;

	count = 0;
	table = philo->table;
	while (count < table->number_of_philosophers)
	{
		philo[count].fork_left = &table->all_fork[count];
		philo[count].fork_rigth = &table->all_fork[(count + 1) % table->number_of_philosophers];
		count++;	
	}

}


int main(int ac, char **av)
{
	int count;

	if (ac < 5)
	{
		ft_putstr_fd("Deu ruim0\n", 1);
		return 1;
	}
	t_table table;
	t_philo	*all_philo;

	table.number_of_philosophers = ft_atoi(av[1]);
	table.time_to_die = ft_atoi(av[2]);
	table.time_to_eat = ft_atoi(av[3]);
	table.time_to_sleep = ft_atoi(av[4]);

	if (table.number_of_philosophers <= 0 || table.time_to_die <= 0 \
		|| table.time_to_eat <= 0 || table.time_to_sleep <= 0)
	{
		ft_putstr_fd("\nDeu ruim1\n", 1);
		return 1;
	}
	all_philo = ft_calloc(table.number_of_philosophers,sizeof(t_philo));
	table.all_fork = ft_calloc(table.number_of_philosophers,sizeof(pthread_mutex_t));
	count = 0;
	while (count < table.number_of_philosophers)
	{
		all_philo[count].id = count + 1;
		all_philo[count].table = &table;
		pthread_mutex_init(&all_philo[count].eat_now, 0);
		if (pthread_mutex_init(&table.all_fork[count], 0) < 0)
			return 1;
		count++;
	}
	ft_delegateFork(all_philo);
	count = 0;
	while (count < table.number_of_philosophers)
	{
		if (pthread_create(&all_philo[count].thread_id, NULL, \
			&routine, &all_philo[count]) != 0)
			return (1);
		count++;
	}
	count = 0;
	while (count < table.number_of_philosophers)
	{
		if (pthread_join(all_philo[count].thread_id, NULL) != 0)
			return (1);
		count++;
	}
	ft_destroy(all_philo);
	return 0;
}