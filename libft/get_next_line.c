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

int		findendl(char *buffer, int BUFFER_SIZE)
{
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0' && i < BUFFER_SIZE)
	{
		++i;
	}
	return (i);
}

int		reading(int fd, char *buffer, char **line, int count, int BUFFER_SIZE)
{
	char	*temp;
	int		rowlen;

	while ((count = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (BUFFER_SIZE != count)
			buffer[count] = '\0';
		rowlen = findendl(buffer, BUFFER_SIZE);
		temp = *line;
		if (!(*line = (char*)malloc(sizeof(char)
			* (rowlen + 1 + ft_strlen(temp)))))
			return (-1);
		ft_strlcpy(*line, temp, ft_strlen(temp) + 1);
		ft_strlcpy(*line + ft_strlen(temp), buffer, rowlen + 1);
		if (temp)
			free(temp);
		if (BUFFER_SIZE > rowlen && !(rowlen == count && count < BUFFER_SIZE))
			return (1);
	}
	buffer[0] = '\0';
	return (count);
}

int		get_next_line(int fd, char **line)
{
	static char	buffer[10];
	int			count;
	int			BUFFER_SIZE;

	count = 0;
	BUFFER_SIZE = 9;
	if (!(*line = (char*)malloc(sizeof(char))))
		return (-1);
	(*line)[0] = '\0';
	if (buffer[0] != '\0')
	{
		ft_strlcpy(buffer, buffer + findendl(buffer, BUFFER_SIZE) + 1,
		BUFFER_SIZE - findendl(buffer, BUFFER_SIZE));
		free(*line);
		if (!(*line = (char*)malloc(sizeof(char) * (findendl(buffer, BUFFER_SIZE) + 1))))
			return (-1);
		ft_strlcpy(*line, buffer, findendl(buffer, BUFFER_SIZE) + 1);
		if (buffer[findendl(buffer, BUFFER_SIZE)] == '\n')
			return (1);
	}
	count = reading(fd, buffer, line, count, BUFFER_SIZE);
	return (count);
}
