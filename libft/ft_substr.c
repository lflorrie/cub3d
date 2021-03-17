/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:37:19 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/13 14:57:46 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (!(res = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (ft_strlen(s) < start)
	{
		res[0] = '\0';
		return (res);
	}
	i = 0;
	while (s[i + start] != '\0' && i < len)
	{
		res[i] = s[i + start];
		++i;
	}
	res[len] = '\0';
	return (res);
}
