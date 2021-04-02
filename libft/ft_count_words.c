/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 23:17:01 by lflorrie          #+#    #+#             */
/*   Updated: 2021/03/29 23:17:17 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *s, char c)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i + 1] == c || s[i + 1] == '\0')
			++len;
		++i;
	}
	return (len);
}
