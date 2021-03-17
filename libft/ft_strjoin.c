/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:39:18 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/13 14:44:46 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(res = (char*)malloc((len1 + len2 + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		++i;
	}
	while (i < len1 + len2)
	{
		res[i] = s2[i - len1];
		++i;
	}
	res[len1 + len2] = '\0';
	return (res);
}
