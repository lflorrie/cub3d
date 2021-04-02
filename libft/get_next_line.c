/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:13:58 by lflorrie          #+#    #+#             */
/*   Updated: 2020/12/30 21:15:50 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		findendl(char *buffer, int n)
{
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0' && i < n)
	{
		++i;
	}
	return (i);
}

int		reading(int fd, char *buffer, char **line, int n)
{
	char	*temp;
	int		rowlen;
	int		count;

	while ((count = read(fd, buffer, n)) > 0)
	{
		if (n != count)
			buffer[count] = '\0';
		rowlen = findendl(buffer, n);
		temp = *line;
		if (!(*line = (char*)malloc(sizeof(char)
			* (rowlen + 1 + ft_strlen(temp)))))
			return (-1);
		ft_strlcpy(*line, temp, ft_strlen(temp) + 1);
		ft_strlcpy(*line + ft_strlen(temp), buffer, rowlen + 1);
		if (temp)
			free(temp);
		if (n > rowlen && !(rowlen == count && count < n))
			return (1);
	}
	buffer[0] = '\0';
	return (count);
}

int		get_next_line(int fd, char **line)
{
	static char	buffer[10];
	int			count;
	int			n;

	count = 0;
	n = 9;
	if (!(*line = (char*)malloc(sizeof(char))))
		return (-1);
	(*line)[0] = '\0';
	if (buffer[0] != '\0')
	{
		ft_strlcpy(buffer, buffer + findendl(buffer, n) + 1,
		n - findendl(buffer, n));
		free(*line);
		if (!(*line = (char*)malloc(sizeof(char) * (findendl(buffer, n) + 1))))
			return (-1);
		ft_strlcpy(*line, buffer, findendl(buffer, n) + 1);
		if (buffer[findendl(buffer, n)] == '\n')
			return (1);
	}
	count = reading(fd, buffer, line, n);
	return (count);
}
