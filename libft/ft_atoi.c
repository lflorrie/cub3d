/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:29:20 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/13 17:53:56 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long		res;
	long long		sign;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		++str;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		++str;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if ((res > 2147483647 && sign == 1))
			return (-1);
		if (res > 2147483648 && sign == -1)
			return (0);
		++str;
	}
	return (res * sign);
}
