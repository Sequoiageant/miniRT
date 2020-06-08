/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 11:34:47 by julnolle          #+#    #+#             */
/*   Updated: 2020/05/03 19:28:36 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_split(char **tab)
{
	size_t i;

	i = 0;
	while (tab[i] != 0)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

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

void	print_obj(t_obj *objlst)
{
	if (objlst)
	{
		while (objlst)
		{
			printf("	-->Type %d\n", objlst->type);
			objlst = objlst->next;
		}
	}
	else
		printf("%s\n", "LISTE VIDE");
}

void	print_lights(t_light *lights)
{
	while (lights)
	{
		printf("	--> %f %f %f \n", lights->pos.x, lights->pos.y, lights->pos.z);
		lights = lights->next;
	}
}

void	print_cams(t_cam *cams)
{
	while (cams)
	{
		printf("	-->num %d\n", cams->nbr);
		printf("	-->fov: %f\n", cams->fov);
		cams = cams->next;
	}
}

void	print_vec(t_vec3 v)
{
	printf("%f %f %f \n", v.x, v.y, v.z);
}

/*void	print_list2(t_obj *objlst)
{
	t_sp	*sp;

	while (objlst)
	{
		if (objlst->type == SPHERE)
		{
			sp = (objlst->content);
			printf("	-->%f\n", sp->dia);
		}
		objlst = objlst->next;
	}
}
*/
/*void	ft_add_obj(t_obj **objlst, void *content, int type, t_data *data)
{
	t_obj *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->type = type;
		new->content = content;
		new->next = (*objlst);
		(*objlst) = new;
	}
	data->objlst = (*objlst);
	if (type == SPHERE)
		printf("<%f>\n", ((t_sp *)data->objlst->content)->dia);
	ft_putendl("	-->element added");
}*/
