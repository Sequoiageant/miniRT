/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 19:50:18 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/22 14:22:51 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_add_cam(t_cam **cams, t_cam *cam, int cam_num)
{
	t_cam	*new;
	t_cam	*tmp;

	new = (t_cam*)malloc(sizeof(t_cam));
	if (new)
	{
		new->nbr = cam_num;
		new->pos = cam->pos;
		new->dir = cam->dir;
		new->fov = cam->fov;
		new->next = NULL;
		if (*cams == NULL)
			(*cams) = new;
		else
		{
			tmp = *cams;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

void	ft_add_light(t_light **lights, t_light *light)
{
	t_light *new;

	new = (t_light*)malloc(sizeof(t_light));
	if (new)
	{
		new->pos = light->pos;
		new->lum = light->lum * 500000.0;
		new->color = light->color;
		new->next = (*lights);
		(*lights) = new;
	}
}

int		set_light(char **tab, t_data *data, t_stm *machine)
{
	static	t_light *lights;
	t_light			light;
	int				ret;

	if ((ret = set_vector(tab[1], &light.pos, &machine->error)) == FAILURE)
		return (ret);
	if (is_int_or_float(tab[2], '+'))
	{
		ret = set_if_in_rnge(tab[2], &light.lum, 0.0, 1.0);
		if (ret == FAILURE)
			machine->error |= RANGE_ERROR_MASK;
	}
	else
	{
		machine->error |= SIGN_ERROR_MASK;
		ret = FAILURE;
	}
	if (ret != FAILURE)
	{
		ret = set_color(tab[3], &light.color, &machine->error);
		ft_add_light(&lights, &light);
		data->lights = lights;
		data->lights_set = TRUE;
	}
	return (ret);
}

int		set_cam(char **tab, t_data *data, t_stm *machine)
{
	t_cam		cam;
	int			ret;
	static	int	cam_num;

	cam_num++;
	ret = set_vector(tab[1], &cam.pos, &machine->error);
	if (ret != FAILURE)
		ret = set_normal_vec(tab[2], &cam.dir, &machine->error);
	if (is_int(tab[3], '+'))
	{
		cam.fov = deg_to_rad(ft_atoi(tab[3]));
		if (cam.fov < 0 || (double)cam.fov > PI)
		{
			ret = FAILURE;
			machine->error |= FOV_ERROR_MASK;
		}
	}
	else
	{
		machine->error |= INT_ERROR_MASK;
		ret = FAILURE;
	}
	ft_add_cam(&data->cams, &cam, cam_num);
	data->cams_set = cam_num;
	return (ret);
}
