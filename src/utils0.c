/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <gapima7@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:48:17 by glima             #+#    #+#             */
/*   Updated: 2024/12/27 15:48:17 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL)
		return ;
	i = -1;
	while (s[++i] != '\0')
		ft_putchar_fd(s[i], fd);
}

long	ft_atoi(const char *nptr)
{
	long	n;
	int		sign;

	sign = 1;
	n = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr)
	{
		if (!(*nptr >= 48 && *nptr <= 57))
			return (n * sign);
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*array;
	size_t	full_size;

	full_size = size * nmemb;
	if (full_size != 0 && full_size / size != nmemb)
		return (NULL);
	array = malloc(full_size);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, full_size);
	return (array);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(214748364, fd);
		ft_putchar_fd('8', fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		c = (n % 10 + '0');
		ft_putchar_fd(c, fd);
	}
	else if (n >= 0 && n <= 9)
	{
		c = (n + '0');
		ft_putchar_fd(c, fd);
	}
	else
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n * -1, fd);
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
