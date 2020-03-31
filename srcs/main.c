/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:16:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/31 20:36:32 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_lstsize(t_obj *lst)
{
	int size;

	size = 0;
	if (lst != NULL)
	{
		while (lst)
		{
			size++;
			lst = lst->next;
		}
	}
	return (size);
}
/*
void	ft_lstclear(t_obj **lst)
{
	if (lst != NULL && *lst != NULL)
	{
		while (*lst != NULL)
		{
			free(*lst->content);
			(*lst) = (*lst)->next;
		}
		free(*lst);
		*lst = NULL;
	}
}
*/

void	print_list(t_obj *objlst)
{
	if (objlst)
	{
		while (objlst)
		{
			printf("	-->type: %d\n", objlst->type);
			objlst = objlst->next;
		}
	}
	else
		printf("%s\n", "LISTE VIDE");
}

int	main(int ac, char **av)
{
	int		fd;
	t_data	data;

	if (ac == 2 || ac == 3)
	{
		fd = open(av[1], O_RDONLY);
		if (fd != -1)
		{
			parser(&data, fd);
			close(fd);
			if (ac == 2)
				ft_launch_window(&data);
			else if (ac == 3 && ft_strcmp(av[2], "-save") == 0)
				ft_save_image(&data);
			else
				return (FAILURE);
		}
	}
	else
		return (FAILURE);
	// system("leaks minirt");
	return (SUCCESS);
}
