/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:46:12 by csinglet          #+#    #+#             */
/*   Updated: 2018/04/17 13:38:22 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	const char	*temp_src;
	char		*temp_dest;
	size_t		index;

	temp_src = (char *)src;
	temp_dest = (char *)dest;
	index = 0;
	while (index < size)
	{
		temp_dest[index] = temp_src[index];
		index++;
	}
	return (dest);
}
