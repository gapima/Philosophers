/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:03:41 by glima             #+#    #+#             */
/*   Updated: 2023/10/21 19:56:41 by gapima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		idx;
	char const	*srctmp;
	char		*destmp;

	destmp = dest;
	srctmp = src;
	idx = -1;
	if (destmp == NULL && srctmp == NULL)
		return (NULL);
	while (++idx < n)
		destmp[idx] = srctmp[idx];
	return (dest);
}
