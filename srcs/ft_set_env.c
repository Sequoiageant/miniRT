/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:50:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/06 15:54:33 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		al.r = ft_atoi(al_color[0]);
		al.g = ft_atoi(al_color[1]);
		al.b = ft_atoi(al_color[2]);
		free(al_color);
		al_color = NULL;
	}
}

void	ft_set_camera(char **tab)
{
	t_cam	cam;
	char	**cam_set;

	cam_set = ft_split(tab[1], ',');
	if (cam_set != NULL)
	{
		cam.x = ft_atof(cam_set[0]);
		cam.y = ft_atof(cam_set[1]);
		cam.z = ft_atof(cam_set[2]);
		free(cam_set);
		cam_set = NULL;
	}
	cam_set = ft_split(tab[2], ',');
	if (cam_set != NULL)
	{
		cam.or_x = ft_atof(cam_set[0]);
		cam.or_y = ft_atof(cam_set[1]);
		cam.or_z = ft_atof(cam_set[2]);
		free(cam_set);
		cam_set = NULL;
	}
	cam.fov = ft_atoi(tab[3]);
}

void	ft_set_sphere(char **tab)
{
	t_sp	sp;
	char	**sp_set;

	sp_set = ft_split(tab[1], ',');
	if (sp_set != NULL)
	{
		sp.x = ft_atof(sp_set[0]);
		sp.y = ft_atof(sp_set[1]);
		sp.z = ft_atof(sp_set[2]);
		free(sp_set);
		sp_set = NULL;
	}
	sp.dia = ft_atof(tab[2]);
	sp_set = ft_split(tab[3], ',');
	if (sp_set != NULL)
	{
		sp.r = ft_atof(sp_set[0]);
		sp.g = ft_atof(sp_set[1]);
		sp.b = ft_atof(sp_set[2]);
		free(sp_set);
		sp_set = NULL;
	}
}
