/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:39:43 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/13 19:23:42 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_all(char **ar)
{
	int	i;

	i = 0;
	while (ar[i] != NULL)
	{
		free(ar[i]);
		++i;
	}
	free(ar);
	return (NULL);
}

static void	ages(const char *s, char c, int *start, int *i)
{
	*i = 0;
	while (s[(*start)] == c)
		++(*start);
	while (s[(*start) + (*i)] != c && s[(*start) + (*i)] != '\0')
		++(*i);
}

char	**ft_split(const char *s, char c)
{
	int		len;
	int		start;
	int		i;
	int		j;
	char	**res;

	if (s == NULL)
		return (NULL);
	len = ft_count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	start = 0;
	j = -1;
	while (++j < len)
	{
		ages(s, c, &start, &i);
		res[j] = ft_substr(s, start, i);
		if (!res[j])
			return (ft_free_all(res));
		start += i + 1;
	}
	res[len] = NULL;
	return (res);
}
