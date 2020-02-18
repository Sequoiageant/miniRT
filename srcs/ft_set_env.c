/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:50:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/13 19:47:10 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*ft_lstnew(void *content, int type)
{
	t_obj *tmp;

	tmp = (t_obj *)malloc(sizeof(*tmp));
	if (tmp)
	{
		tmp->type = type;
		tmp->content = content;
		tmp->next = NULL;
	}
	return (tmp);
}


void	ft_lstadd_front(t_obj **objlst, t_obj *new)
{
	if (new)
	{
		if ((*objlst) != NULL)
			new->next = (*objlst);
		else
			new->next = NULL;
		(*objlst) = new;
	}
	else
		return ;
}

int ft_add_obj_to_list(t_obj **objlst, t_obj *new, void *content)
{
	new->content = content;
	ft_lstadd_front(objlst, new);
	ft_putendl("	-->element added");
	return (0);
}

// int ft_add_sq_to_list(t_obj **objlst, t_obj *new, t_sq *sq)
// {
// 	new->content = sq;
// 	ft_lstadd_front(objlst, new);
// 	ft_putendl("	-->square added");
// 	return (0);
// }

void	ft_free_tab2(char **tab)
{
	free(tab);
	tab = NULL;
}

void	ft_set_win(char **tab, t_win *win)
{
	win->w = ft_atoi(tab[1]);
	win->h = ft_atoi(tab[2]);
	win->set = true;
	if (win->w > 2560)
		win->w = 2560;
	if (win->h > 1440)
		win->h = 1440;
}

void	ft_set_ambiant_light(char **tab)
{
	t_ambl	al;
	char	**al_color;

	al.lum = ft_atof(tab[1]);
	al_color = ft_split(tab[2], ',');
	if (al_color != NULL)
	{
		al.color.r = ft_atoi(al_color[0]);
		al.color.g = ft_atoi(al_color[1]);
		al.color.b = ft_atoi(al_color[2]);
		ft_free_tab2(al_color);
	}
}

void	ft_set_camera(char **tab)
{
	t_cam	cam;
	char	**cam_set;

	cam_set = ft_split(tab[1], ',');
	if (cam_set != NULL)
	{
		cam.pos.x = ft_atof(cam_set[0]);
		cam.pos.y = ft_atof(cam_set[1]);
		cam.pos.z = ft_atof(cam_set[2]);
		ft_free_tab2(cam_set);
	}
	cam_set = ft_split(tab[2], ',');
	if (cam_set != NULL)
	{
		cam.dir.x = ft_atof(cam_set[0]);
		cam.dir.y = ft_atof(cam_set[1]);
		cam.dir.z = ft_atof(cam_set[2]);
		ft_free_tab2(cam_set);
	}
	cam.fov = ft_atoi(tab[3]);
}

int	set_sp(char **tab, t_obj **objlst)
{
	t_sp	*sp;
	char	**sp_set;
	t_obj	*new;

	sp_set = ft_split(tab[1], ',');
	if (sp_set != NULL)
	{
		sp->pos.x = ft_atof(sp_set[0]);
		sp->pos.y = ft_atof(sp_set[1]);
		sp->pos.z = ft_atof(sp_set[2]);
		ft_free_tab2(sp_set);
	}
	sp->dia = ft_atof(tab[2]);
	sp_set = ft_split(tab[3], ',');
	if (sp_set != NULL)
	{
		sp->color.r = ft_atof(sp_set[0]);
		sp->color.g = ft_atof(sp_set[1]);
		sp->color.b = ft_atof(sp_set[2]);
		ft_free_tab2(sp_set);
	}
	new = ft_lstnew(sp, SPHERE);
	ft_add_obj_to_list(objlst, new, sp);
	return (0);
}

int	set_sq(char **tab, t_obj **objlst)
{
	t_sq	*sq;
	char	**sq_set;
	t_obj	*new;

	sq_set = ft_split(tab[1], ',');
	if (sq_set != NULL)
	{
		sq->pos.x = ft_atof(sq_set[0]);
		sq->pos.y = ft_atof(sq_set[1]);
		sq->pos.z = ft_atof(sq_set[2]);
		ft_free_tab2(sq_set);
	}
	sq_set = ft_split(tab[2], ',');
	if (sq_set != NULL)
	{
		sq->dir.x = ft_atof(sq_set[0]);
		sq->dir.y = ft_atof(sq_set[1]);
		sq->dir.z = ft_atof(sq_set[2]);
		ft_free_tab2(sq_set);
	}	
	sq->h = ft_atof(tab[3]);
	sq_set = ft_split(tab[4], ',');
	if (sq_set != NULL)
	{
		sq->color.r = ft_atof(sq_set[0]);
		sq->color.g = ft_atof(sq_set[1]);
		sq->color.b = ft_atof(sq_set[2]);
		ft_free_tab2(sq_set);
	}
	new = ft_lstnew(sq, SQUARE);
	ft_add_obj_to_list(objlst, new, sq);
	return (0);
}
