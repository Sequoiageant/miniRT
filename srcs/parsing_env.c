/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 19:50:18 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/08 15:32:30 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		printf("	-->%f\n", cams->fov);
		cams = cams->next;
	}
}

void	ft_add_cam(t_cam **cams, t_cam *cam)
{
	static	int	cam_num;
	t_cam		*new;

	cam_num++;
	new = (t_cam*)malloc(sizeof(t_cam));
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
	print_cams((*cams));
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
	print_lights((*lights));
	ft_putendl("	-->light added");
}

int		set_res(char **tab, t_data *data, int *error)
{
	static int set = FAILURE;

	if (set != SUCCESS)
	{
		if (is_int_or_float(tab[1], '+') && is_int_or_float(tab[2], '+'))
		{
			data->win.w = ft_min(ft_atoi(tab[1]), MAX_W);
			data->win.h = ft_min(ft_atoi(tab[2]), MAX_H);
			set = SUCCESS;
		}
		else
			*error |= SIGN_ERROR_MASK;
	}
	else
	{
		set = FAILURE;
		*error |= ENV_ERROR_MASK;
	}
	return (set);
}

int		set_light(char **tab, t_data *data, int *error)
{
	static	t_light *lights;
	t_light			light;
	int				ret;

	if ((ret = set_vector(tab[1], &light.pos, error)) == FAILURE)
		return (ret);
	if (is_int_or_float(tab[2], '+'))
	{
		ret = set_if_in_rnge(tab[2], &light.lum, 0.0, 1.0);
		if (ret == FAILURE)
			*error |= RANGE_ERROR_MASK;
	}
	else
	{
		*error |= SIGN_ERROR_MASK;
		ret = FAILURE;
	}
	if (ret != FAILURE)
	{
		ret = set_color(tab[3], &light.color, error);
		ft_add_light(&lights, &light);
		data->lights = lights;
		data->lights_set = TRUE;
	}
	return (ret);
}

int		set_al(char **tab, t_data *data, int *error)
{
	static int	set = FAILURE;

	if (set != SUCCESS)
	{
		if (is_int_or_float(tab[1], '+'))
		{
			set = set_if_in_rnge(tab[1], &data->al.lum, 0.0, 1.0);
			if (set == FAILURE)
				*error |= RANGE_ERROR_MASK;
		}
		else
			*error |= SIGN_ERROR_MASK;
		if (set != FAILURE)
		{
			set = set_color(tab[2], &data->al.color, error);
			data->al.color = mult_col_double(data->al.color, data->al.lum);
		}
	}
	else
	{
		set = FAILURE;
		*error |= ENV_ERROR_MASK;
	}
	return (set);
}

int		set_cam(char **tab, t_data *data, int *error)
{
	t_cam	cam;
	int		ret;

	ret = set_vector(tab[1], &cam.pos, error);
	if (ret != FAILURE)
		ret = set_normal_vec(tab[2], &cam.dir, error);
	if (is_int(tab[3], '+'))
	{
		cam.fov = deg_to_rad(ft_atoi(tab[3]));
		if (cam.fov < 0 || (double)cam.fov > PI)
		{
			ret = FAILURE;
			*error |= FOV_ERROR_MASK;
		}
	}
	else
	{
		*error |= INT_ERROR_MASK;
		ret = FAILURE;
	}
	ft_add_cam(&data->cams, &cam);
	data->cams_set = TRUE;
	return (ret);
}
