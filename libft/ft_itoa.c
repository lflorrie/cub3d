/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:39:52 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/13 18:00:41 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len(int n)
{
	int	i;

	i = 1;
	n = n / 10;
	while (n != 0)
	{
		++i;
		n = n / 10;
	}
	return (i);
}

char			*ft_itoa(int nn)
{
	char		*result;
	size_t		i;
	int			sign;
	long int	n;

	sign = 0;
	n = nn;
	i = len(n);
	if (n < 0)
	{
		++i;
		sign = 1;
		n = -n;
	}
	if (!(result = (char*)malloc((i) * sizeof(char) + 1)))
		return (NULL);
	result[i] = '\0';
	while (i > 0)
	{
		result[--i] = (char)(n % 10 + '0');
		n /= 10;
	}
	if (sign)
		result[0] = '-';
	return (result);
}
