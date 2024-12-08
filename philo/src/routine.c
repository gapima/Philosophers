#include "philo.h"
#include <pthread.h>


unsigned long ft_get_time()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == 0)
		return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
	exit(0);
}

void sleep_routine(int time_sleep)
{
    unsigned long time_now;

    time_now = ft_get_time() + time_sleep;
    while (ft_get_time() < time_now)
    {
        usleep(time_sleep / 2);
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
}

void    *routine(void *data)
{
	t_philo *philo;
	
	philo = data;
	while (philo->table->simulation_running)
	{
		eat_routine(philo);
		print_action(THINKING, philo);
	}
	return (NULL);
}

