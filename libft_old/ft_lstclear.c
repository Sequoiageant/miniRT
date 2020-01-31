/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:11:25 by julnolle          #+#    #+#             */
/*   Updated: 2019/11/15 13:14:06 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst != NULL && *lst != NULL && (*del) != NULL)
	{
		while (*lst != NULL)
		{
			del(*lst->content);
			(*lst) = (*lst)->next;
		}
		free(*lst);
		*lst = NULL;
	}
}
