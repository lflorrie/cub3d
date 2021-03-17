/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:29:09 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/01 15:16:03 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char*)dest;
	s = (unsigned char*)src;
	i = 0;
	while (i != n && s[i] != (unsigned char)c)
	{
		d[i] = s[i];
		++i;
	}
	if (s[i] != (unsigned char)c)
		return (NULL);
	d[i] = (unsigned char)c;
	return ((void*)(d + i + 1));
}
