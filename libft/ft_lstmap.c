/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:14:07 by julnolle          #+#    #+#             */
/*   Updated: 2019/11/14 17:53:10 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_list;
	t_list *tmp;

	if (lst == NULL)
		return (NULL);
	if (!(tmp = ft_lstnew(f(lst->content))))
		return (NULL);
	new_list = tmp;
	while (lst)
	{
		if (lst->next)
		{
			if (!(tmp->next = ft_lstnew((*f)(lst->next->content))))
			{
				ft_lstclear(&new_list, del);
				return (0);
			}
			tmp = tmp->next;
		}
		lst = lst->next;
	}
	tmp->next = 0;
	return (new_list);
}
