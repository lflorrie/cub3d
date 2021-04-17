/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 23:37:09 by lflorrie          #+#    #+#             */
/*   Updated: 2021/03/29 23:37:31 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_list_to_array(t_list *lst)
{
	t_list	*temp;
	int		size;
	int		i;
	char	**arr;

	i = 0;
	size = ft_lstsize(lst);
	if (size == 0)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	while (i < size)
	{
		arr[i] = (char *)lst->content;
		temp = lst;
		lst = lst->next;
		free(temp);
		++i;
	}
	arr[size] = NULL;
	return (arr);
}
