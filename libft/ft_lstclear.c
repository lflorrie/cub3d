/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:44:15 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/13 16:08:48 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
		return ;
	while ((*lst))
	{
		temp = *lst;
		*lst = (*lst)->next;
		del(temp->content);
		free(temp);
		temp = NULL;
	}
}
