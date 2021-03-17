/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:40:45 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/13 16:44:48 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int num, int exp)
{
	int res;

	if (exp == 0)
		return (1);
	res = num;
	while (exp > 1)
	{
		res *= num;
		--exp;
	}
	return (res);
}

static void	ft_nbr(int n, int fd)
{
	int		len;
	int		i;
	char	ch;

	i = n;
	len = 1;
	while (i / 10 != 0)
	{
		++len;
		i /= 10;
	}
	i = 0;
	while (i < len)
	{
		ch = '0' + (char)(n / ft_pow(10, len - i - 1));
		n %= ft_pow(10, len - i - 1);
		ft_putchar_fd(ch, fd);
		++i;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	ft_nbr(n, fd);
}
