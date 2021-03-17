/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:33:07 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/12 17:32:35 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		length;
	char	*res;

	length = 0;
	while (str[length])
	{
		++length;
	}
	if (!(res = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	res[length] = '\0';
	while (length > 0)
	{
		--length;
		res[length] = str[length];
	}
	return (res);
}
