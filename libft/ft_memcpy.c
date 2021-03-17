/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:26:17 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/12 16:55:02 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dist, void *source, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (dist == NULL && source == NULL)
		return (NULL);
	d = (char*)dist;
	s = (char*)source;
	i = 0;
	while (i != n)
	{
		d[i] = s[i];
		++i;
	}
	return (dist);
}
