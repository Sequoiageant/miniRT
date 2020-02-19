/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:50:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/19 19:48:01 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_cams(t_cam *cams)
{
	while (cams)
	{
		printf("	-->%d\n", cams->fov);
		cams = cams->next;
	}
}

void	ft_add_obj(t_obj **objlst, void *content, int type)
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
	ft_putendl("	-->element added");
}

void	ft_add_cam(t_cam **cams, t_cam *cam)
{
	t_cam *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new = cam;
		new->next = (*cams);
		(*cams) = new;
	}
	ft_putendl("	-->cam added");
	// print_cams((*cams));
}

void	ft_add_light(t_light **lights, t_light *light)
{
	t_light *new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new = light;
		new->next = (*lights);
		(*lights) = new;
	}
	ft_putendl("	-->light added");
}

void	ft_free_tab2(char **tab)
{
	free(tab);
	tab = NULL;
}

int		set_res(char **tab)
{
	t_win win;
	win.w = ft_atoi(tab[1]);
	win.h = ft_atoi(tab[2]);
	win.set = true;
	if (win.w > 2560)
		win.w = 2560;
	if (win.h > 1440)
		win.h = 1440;
	// ft_launch_window(&win);
	return (0);
}

int		set_light(char **tab)
{
	static	t_light *lights;
	t_light			light;
	char			**light_set;

	light_set = ft_split(tab[1], ',');
	if (light_set != NULL)
	{
		light.pos.x = ft_atoi(light_set[0]);
		light.pos.y = ft_atoi(light_set[1]);
		light.pos.z = ft_atoi(light_set[2]);
		ft_free_tab2(light_set);
	}	
	light.lum = ft_atof(tab[2]);
	light_set = ft_split(tab[3], ',');
	if (light_set != NULL)
	{
		light.color.r = ft_atoi(light_set[0]);
		light.color.g = ft_atoi(light_set[1]);
		light.color.b = ft_atoi(light_set[2]);
		ft_free_tab2(light_set);
		ft_add_light(&lights, &light);
	}
	return (0);
}

int		set_al(char **tab)
{
	t_ambl	al;
	char	**al_set;

	al.lum = ft_atof(tab[1]);
	al_set = ft_split(tab[2], ',');
	if (al_set != NULL)
	{
		al.color.r = ft_atoi(al_set[0]);
		al.color.g = ft_atoi(al_set[1]);
		al.color.b = ft_atoi(al_set[2]);
		ft_free_tab2(al_set);
	}
	return (0);
}

int		set_cam(char **tab)
{
	static	t_cam	*cams;
	t_cam			cam;
	char			**cam_set;

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
	ft_add_cam(&cams, &cam);
	return (0);
}

int	set_sp(char **tab, t_obj **objlst)
{
	t_sp	sp;
	char	**sp_set;

	sp_set = ft_split(tab[1], ',');
	if (sp_set != NULL)
	{
		sp.pos.x = ft_atof(sp_set[0]);
		sp.pos.y = ft_atof(sp_set[1]);
		sp.pos.z = ft_atof(sp_set[2]);
		ft_free_tab2(sp_set);
	}
	sp.dia = ft_atof(tab[2]);
	sp_set = ft_split(tab[3], ',');
	if (sp_set != NULL)
	{
		sp.color.r = ft_atof(sp_set[0]);
		sp.color.g = ft_atof(sp_set[1]);
		sp.color.b = ft_atof(sp_set[2]);
		ft_free_tab2(sp_set);
	}
	ft_add_obj(objlst, &sp, SPHERE);
	return (0);
}

int	set_sq(char **tab, t_obj **objlst)
{
	t_sq	sq;
	char	**sq_set;

	sq_set = ft_split(tab[1], ',');
	if (sq_set != NULL)
	{
		sq.pos.x = ft_atof(sq_set[0]);
		sq.pos.y = ft_atof(sq_set[1]);
		sq.pos.z = ft_atof(sq_set[2]);
		ft_free_tab2(sq_set);
	}
	sq_set = ft_split(tab[2], ',');
	if (sq_set != NULL)
	{
		sq.dir.x = ft_atof(sq_set[0]);
		sq.dir.y = ft_atof(sq_set[1]);
		sq.dir.z = ft_atof(sq_set[2]);
		ft_free_tab2(sq_set);
	}	
	sq.h = ft_atof(tab[3]);
	sq_set = ft_split(tab[4], ',');
	if (sq_set != NULL)
	{
		sq.color.r = ft_atof(sq_set[0]);
		sq.color.g = ft_atof(sq_set[1]);
		sq.color.b = ft_atof(sq_set[2]);
		ft_free_tab2(sq_set);
	}
	ft_add_obj(objlst, &sq, SQUARE);
	return (0);
}

int	set_pl(char **tab, t_obj **objlst)
{
	t_pl	pl;
	char	**pl_set;

	pl_set = ft_split(tab[1], ',');
	if (pl_set != NULL)
	{
		pl.pos.x = ft_atof(pl_set[0]);
		pl.pos.y = ft_atof(pl_set[1]);
		pl.pos.z = ft_atof(pl_set[2]);
		ft_free_tab2(pl_set);
	}
	pl_set = ft_split(tab[2], ',');
	if (pl_set != NULL)
	{
		pl.dir.x = ft_atof(pl_set[0]);
		pl.dir.y = ft_atof(pl_set[1]);
		pl.dir.z = ft_atof(pl_set[2]);
		ft_free_tab2(pl_set);
	}	
	pl_set = ft_split(tab[3], ',');
	if (pl_set != NULL)
	{
		pl.color.r = ft_atof(pl_set[0]);
		pl.color.g = ft_atof(pl_set[1]);
		pl.color.b = ft_atof(pl_set[2]);
		ft_free_tab2(pl_set);
	}
	ft_add_obj(objlst, &pl, PLANE);
	return (0);
}

int	set_cy(char **tab, t_obj **objlst)
{
	t_cy	cy;
	char	**cy_set;

	cy_set = ft_split(tab[1], ',');
	if (cy_set != NULL)
	{
		cy.pos.x = ft_atof(cy_set[0]);
		cy.pos.y = ft_atof(cy_set[1]);
		cy.pos.z = ft_atof(cy_set[2]);
		ft_free_tab2(cy_set);
	}
	cy_set = ft_split(tab[2], ',');
	if (cy_set != NULL)
	{
		cy.dir.x = ft_atof(cy_set[0]);
		cy.dir.y = ft_atof(cy_set[1]);
		cy.dir.z = ft_atof(cy_set[2]);
		ft_free_tab2(cy_set);
	}	
	cy_set = ft_split(tab[3], ',');
	if (cy_set != NULL)
	{
		cy.color.r = ft_atof(cy_set[0]);
		cy.color.g = ft_atof(cy_set[1]);
		cy.color.b = ft_atof(cy_set[2]);
		ft_free_tab2(cy_set);
	}
	cy.dia = ft_atof(tab[4]);
	cy.h = ft_atof(tab[5]);
	ft_add_obj(objlst, &cy, CYLINDER);
	return (0);
}

int	set_tr(char **tab, t_obj **objlst)
{
	t_tr	tr;
	char	**tr_set;

	tr_set = ft_split(tab[1], ',');
	if (tr_set != NULL)
	{
		tr.pos1.x = ft_atof(tr_set[0]);
		tr.pos1.y = ft_atof(tr_set[1]);
		tr.pos1.z = ft_atof(tr_set[2]);
		ft_free_tab2(tr_set);
	}
	tr_set = ft_split(tab[2], ',');
	if (tr_set != NULL)
	{
		tr.pos2.x = ft_atof(tr_set[0]);
		tr.pos2.y = ft_atof(tr_set[1]);
		tr.pos2.z = ft_atof(tr_set[2]);
		ft_free_tab2(tr_set);
	}	
	tr_set = ft_split(tab[3], ',');
	if (tr_set != NULL)
	{
		tr.pos3.x = ft_atof(tr_set[0]);
		tr.pos3.y = ft_atof(tr_set[1]);
		tr.pos3.z = ft_atof(tr_set[2]);
		ft_free_tab2(tr_set);
	}
	tr_set = ft_split(tab[4], ',');
	if (tr_set != NULL)
	{
		tr.color.r = ft_atof(tr_set[0]);
		tr.color.g = ft_atof(tr_set[1]);
		tr.color.b = ft_atof(tr_set[2]);
		ft_free_tab2(tr_set);
	}
	ft_add_obj(objlst, &tr, TRIANGLE);
	return (0);
}
