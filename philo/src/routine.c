#include "philo.h"
#include <stdio.h>

long ft_get_time()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == 0)
		return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
	exit(0);
}

void sleep_routine(int time_sleep)
{
	long time_now;

	time_now = ft_get_time() + time_sleep;
	while (ft_get_time() < time_now)
	{
		usleep(time_sleep / 10);
	}
}

void   eat_routine(t_philo *philo)
{
	get_forks(philo);
	print_action(EATING, philo);
	pthread_mutex_lock(&philo->eat_now);
	philo->quantity_eat++;
	philo->eat_last_time = ft_get_time();
	sleep_routine(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->eat_now);
	leave_forks(philo);
	if (philo->quantity_eat == philo->table->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->table->how_philo_eat);
		philo->table->quantity_have_philo++;
		philo->quantity_eat++;
		pthread_mutex_unlock(&philo->table->how_philo_eat);
	}
}

void    *check_died(void *data)
{
	t_philo *philo;

	philo = data;
	while (philo->table->simulation_running)
	{
		pthread_mutex_lock(&philo->eat_now);
		if ((ft_get_time() - philo->eat_last_time) >= philo->table->time_to_die)
		{
			print_action(DIED, philo);
			philo->table->simulation_running = false;
			pthread_mutex_unlock(&philo->eat_now);
			break;
		}
		pthread_mutex_unlock(&philo->eat_now);
		sleep_routine(5);
	}
	return (NULL);
}

void    *routine(void *data)
{
	t_philo     *philo;
	pthread_t   thread;

	philo = data;
	philo->eat_last_time = ft_get_time();
	pthread_create(&thread, NULL, check_died, philo);
	while (philo->table->simulation_running)
	{
		eat_routine(philo);
		print_action(THINKING, philo);
	}
	pthread_join(thread, NULL);
	return (NULL);
}

