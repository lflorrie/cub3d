/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:32:51 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/13 14:46:02 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	i;
	char	*p_res;

	if (!(res = (void*)malloc(size * nmemb)))
		return (NULL);
	i = 0;
	p_res = (char*)res;
	while (i < nmemb * size)
	{
		p_res[i] = 0;
		++i;
	}
	return (res);
}
