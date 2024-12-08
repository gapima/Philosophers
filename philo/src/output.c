#include "philo.h"


void    get_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->fork_left);
    print_action(HUNGRY, philo);
    pthread_mutex_lock(philo->fork_right);
    print_action(HUNGRY, philo);
}

void    leave_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->fork_right);
    pthread_mutex_unlock(philo->fork_left);
    sleep_routine(philo->table->time_to_sleep);
    print_action(SLEEPING, philo);
}

void    print_action(t_action action, t_philo *philo)
{
    unsigned long time_now;

    pthread_mutex_lock(&philo->table->write_action);
    time_now = ft_get_time() - philo->table->time_start;
    ft_putnbr_fd(time_now, 1);
    ft_putstr_fd(" ", 1);
    ft_putnbr_fd(philo->id, 1);
    if (action == DIED)
        ft_putendl_fd(" died", 1);
    else if (action == EATING)
        ft_putendl_fd(" is eating", 1);
    else if (action == SLEEPING)
        ft_putendl_fd(" is sleeping", 1);
    else if (action == THINKING)
        ft_putendl_fd(" is thinking", 1);
    else if (action == HUNGRY)
        ft_putendl_fd(" has taken a fork", 1);
    pthread_mutex_unlock(&philo->table->write_action);
}