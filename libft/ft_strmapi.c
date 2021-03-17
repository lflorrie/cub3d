/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmapi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:39:59 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/01 15:27:53 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*res;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (!(res = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	res[len] = '\0';
	while (len)
	{
		--len;
		res[len] = f(len, s[len]);
	}
	return (res);
}
