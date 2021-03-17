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

static void	ft_free_all(char **ar)
{
	int i;

	i = 0;
	while (ar[i] != NULL)
	{
		free(ar[i]);
		++i;
	}
	free(ar);
}

static int	ft_count_words(const char *s, char c)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			++len;
		++i;
	}
	return (len);
}

static void	ages(const char *s, char c, int *start, int *i)
{
	*i = 0;
	while (s[(*start)] == c)
		++(*start);
	while (s[(*start) + (*i)] != c && s[(*start) + (*i)] != '\0')
		++(*i);
}

char		**ft_split(const char *s, char c)
{
	int		len;
	int		start;
	int		i;
	int		j;
	char	**res;

	if (s == NULL)
		return (NULL);
	len = ft_count_words(s, c);
	if (!(res = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	start = 0;
	j = -1;
	while (++j < len)
	{
		ages(s, c, &start, &i);
		if (!(res[j] = ft_substr(s, start, i)))
		{
			ft_free_all(res);
			return (NULL);
		}
		start += i + 1;
	}
	res[len] = NULL;
	return (res);
}
