/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:44:30 by lflorrie          #+#    #+#             */
/*   Updated: 2020/11/13 16:30:00 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin_result;
	t_list	*temp;

	begin_result = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (!(temp = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&begin_result, del);
			return (NULL);
		}
		else
		{
			ft_lstadd_back(&begin_result, temp);
		}
		lst = lst->next;
	}
	return (begin_result);
}
