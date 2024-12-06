/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:44:00 by glima             #+#    #+#             */
/*   Updated: 2023/11/09 18:18:57 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
