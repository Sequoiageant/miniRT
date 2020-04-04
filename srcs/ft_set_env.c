/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:50:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/04 17:09:57 by julien           ###   ########.fr       */
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
	print_cams((*cams));
}

void	ft_add_light(t_light **lights, t_light *light)
{
	t_light *new;

	new = malloc(sizeof(*new));
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

int		is_int_or_float(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		set_res(char **tab, t_data *data, int *error)
{
	static int set = FAILURE;

	if (set != SUCCESS)
	{
		if (is_int_or_float(tab[1]) && is_int_or_float(tab[2]))
		{
			data->win.w = ft_min(ft_atoi(tab[1]), MAX_W);
			data->win.h = ft_min(ft_atoi(tab[2]), MAX_H);
			if (data->win.w > 0.0 && data->win.h > 0.0)
				set = SUCCESS;
			else
				*error |= INT_ERROR_MASK;
		}
		else
			*error |= INT_ERROR_MASK;
	}
	else
	{
		set = FAILURE;
		*error |= ENV_ERROR_MASK;
	}
	return (set);
}

/*
int		set_res(char **tab, t_data *data, int *error)
{
	static int set = FALSE;

	if (set != TRUE)
	{
		if (is_int_or_float(tab[1]) && is_int_or_float(tab[2]))
			set = TRUE;
		else
			set = FAILURE;
		if (set == TRUE)
		{
			data->win.w = ft_min(ft_atoi(tab[1]), MAX_W);
			data->win.h = ft_min(ft_atoi(tab[2]), MAX_H);
			if (data->win.w < 0.0 && data->win.w < 0.0)
				set = FAILURE;
		}
	}
	else
		set = FALSE;
	return (set);
}

*/int		set_light(char **tab, t_data *data, int *error)
{
	static	t_light *lights;
	t_light			light;
	char			**lt_set;
	(void)error;

	lt_set = ft_split(tab[1], ',');
	if (lt_set != NULL)
	{
		light.pos = new_vec_from_char(lt_set[0], lt_set[1], lt_set[2]);
		ft_free_tab2(&lt_set);
	}
	light.lum = ft_atof(tab[2]);
	lt_set = ft_split(tab[3], ',');
	if (lt_set != NULL)
	{
		light.color = char_to_col(lt_set[0], lt_set[1], lt_set[2]);
		ft_free_tab2(&lt_set);
	}
	ft_add_light(&lights, &light);
	data->lights = lights;
	data->lights_set = TRUE;
	return (SUCCESS);
}

int		set_al(char **tab, t_data *data, int *error)
{
	t_ambl		al;
	char		**al_set;
	static int	set = FAILURE;
	(void)error;

	if (set != SUCCESS)
	{
		al.lum = ft_atof(tab[1]);
		al_set = ft_split(tab[2], ',');
		if (al_set != NULL)
		{
			al.color.r = ft_atoi(al_set[0]) * al.lum;
			al.color.g = ft_atoi(al_set[1]) * al.lum;
			al.color.b = ft_atoi(al_set[2]) * al.lum;
			ft_free_tab2(&al_set);
		}
		data->al = al;
		set = SUCCESS;
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
	static	t_cam	*cams;
	t_cam			cam;
	char			**cam_set;
	(void)error;

	cam_set = ft_split(tab[1], ',');
	if (cam_set != NULL)
	{
		cam.pos = new_vec_from_char(cam_set[0], cam_set[1], cam_set[2]);
		ft_free_tab2(&cam_set);
	}
	cam_set = ft_split(tab[2], ',');
	if (cam_set != NULL)
	{
		cam.dir = new_vec_from_char(cam_set[0], cam_set[1], cam_set[2]);
		ft_free_tab2(&cam_set);
	}
	cam.fov = deg_to_rad(ft_atoi(tab[3]));
	ft_add_cam(&cams, &cam);
	data->cams = cams;
	data->cams_set = TRUE;
	return (SUCCESS);
}
