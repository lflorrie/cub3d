/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:19:00 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/12 14:52:27 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t i;
	size_t j;

	if (*little == '\0')
	{
		return ((char*)big);
	}
	i = 0;
	while (big[i] != '\0' && i < n)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < n)
		{
			++j;
			if (little[j] == '\0')
				return ((char*)(big) + i);
		}
		++i;
	}
	return (NULL);
}
