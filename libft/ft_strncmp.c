/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:28:21 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/12 17:30:37 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(char *lhs, char *rhs, size_t n)
{
	size_t			i;
	unsigned char	*l;
	unsigned char	*r;

	l = (unsigned char*)lhs;
	r = (unsigned char*)rhs;
	i = 0;
	while ((l[i] != '\0' || r[i] != '\0') && i < n)
	{
		if (l[i] != r[i])
		{
			return (l[i] - r[i]);
		}
		++i;
	}
	return (0);
}
