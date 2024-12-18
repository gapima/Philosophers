#include "philo.h"


int main(int ac, char **av)
{
	int count;

	if (ac < 5)
	{
		ft_putstr_fd("Deu ruim0", 1);
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
		ft_putstr_fd("Deu ruim1", 1);
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
			return ;
		count++;	
	}
	

	return 0;
}