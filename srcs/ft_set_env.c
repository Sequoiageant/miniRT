/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:50:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/21 17:16:40 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_lights(t_light *lights)
{
	while (lights)
	{
		printf("	-->%f\n", lights->lum);
		lights = lights->next;
	}
}

void	print_cams(t_cam *cams)
{
	while (cams)
	{
		printf("	-->num %d\n", cams->nbr);
		printf("	-->%d\n", cams->fov);
		cams = cams->next;
	}
}

void	ft_add_cam(t_cam **cams, t_cam *cam)
{
	static	int	cam_num;
	t_cam 		*new;

	cam_num++;
	new = malloc(sizeof(*new));
	if (new)
	{
		new->nbr = cam_num;
		new->pos = cam->pos;
		new->dir = cam->dir;
		new->fov = cam->fov;
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
		new->pos = light->pos;
		new->lum = light->lum;
		new->color = light->color;
		new->next = (*lights);
		(*lights) = new;
	}
	print_lights((*lights));
	ft_putendl("	-->light added");
}

int		set_res(char **tab, t_data *data)
{
	data->win.w = ft_atoi(tab[1]);
	data->win.h = ft_atoi(tab[2]);
	data->win.set = true;
	if (data->win.w > 2560)
		data->win.w = 2560;
	if (data->win.h > 1440)
		data->win.h = 1440;
	return (0);
}

int		set_light(char **tab, t_data *data)
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
	}
	ft_add_light(&lights, &light);
	data->lights = lights;
	return (0);
}

int		set_al(char **tab, t_data *data)
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

int		set_cam(char **tab, t_data *data)
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
	data->cams = cams;
	return (0);
}
