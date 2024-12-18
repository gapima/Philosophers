/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:31:14 by glima             #+#    #+#             */
/*   Updated: 2023/10/24 18:12:11 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	size_t	len;

	len = ft_strlen(s) + 1;
	duplicate = (char *)malloc(len);
	if (duplicate == NULL)
		return (NULL);
	ft_memcpy(duplicate, s, len);
	return (duplicate);
}
