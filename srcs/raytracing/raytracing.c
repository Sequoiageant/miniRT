/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 16:52:56 by julien            #+#    #+#             */
/*   Updated: 2020/04/15 12:28:14 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam	select_cam(t_data data)
{
	while (data.cams)
	{
		if (data.cam_num == 0)
			data.cam_num = 1;
		if (data.cams->nbr == data.cam_num)
			return (*data.cams);
		data.cams = data.cams->next;
	}
	return (*data.cams);
}

void	reset_image(t_data *data)
{
	double	x;
	double	y;
	t_win	win;
	win = data->win;

	y = 0;
	while (y < win.h - 1)
	{
		x = 0;
		while (x < win.w - 1)
		{
			ft_pixel_put(&data->mlx, x, y, rgb_to_int(255, 255, 255));
			x++;
		}
		y++;
	}
}

void reset_inter(t_inter *inter)
{
	inter->t = INFINITY;
	inter->pos.x = 0.0;
	inter->pos.y = 0.0;
	inter->pos.z = 0.0;
	inter->normal.x = 0.0;
	inter->normal.y = 0.0;
	inter->normal.z = 0.0;
}

t_vec3	trace_ray_normalized(t_win win, double x, double y, double fov)
{
	t_vec3 ray;

	ray.x = (x + 0.5) - win.w / 2;
	ray.y = (y + 0.5) - win.h / 2;
	ray.z = -win.w / (2.0 * tan(fov / 2.0));
	ft_normalize(&ray);
	return (ray);
}

void	find_closest_inter(t_data *data, t_inter *finter, t_vec3 *ray)
{
	t_inter inter;
	t_obj *objlst;
	static t_ray	intersec[NB_OBJ] = {rt_sp, rt_pl, rt_sq, rt_cy, rt_tr};
	
	inter.origin = select_cam(*data).pos;
	objlst = data->objlst;
	while (objlst)
	{
		reset_inter(&inter);
		if (intersec[objlst->type](ray, objlst, &inter))
		{
			finter->set = true;
			if (inter.t <= finter->min_t)
			{
				finter->min_t = inter.t;
				finter->pos = inter.pos;
				finter->normal = inter.normal;
				finter->col = objlst->col;
			}
		}
		objlst = objlst->next;
	}
}

double	is_in_shade(t_data *data, t_vec3 ray, t_inter finter)
{
	t_obj			*objlst;
	t_inter			inter;
	static t_ray	intersec[NB_OBJ] = {rt_sp, rt_pl, rt_sq, rt_cy, rt_tr};
	t_vec3			normalized_ray;
	
	normalized_ray = ft_get_normalized(ray);
	finter.normal = ft_multby_vec3(&finter.normal, BIAS);
	inter.origin = ft_add_vec3(finter.pos, finter.normal);
	objlst = data->objlst;
	while (objlst)
	{
		if (intersec[objlst->type](&normalized_ray, objlst, &inter))
		{
			if ((inter.t * inter.t) < ft_norm_vec3_2(&ray))
				return (TRUE);
		}
		objlst = objlst->next;
	}
	return (FALSE);
}

int		calc_pixel_color(t_data *data, t_inter finter)
{
	t_vec3	p;
	double	light_power;
	t_light	*lights_cpy;
	t_col	col;
	t_col	col_tmp;

	init_color(&col);
	init_color(&col_tmp);
	lights_cpy = data->lights;
	light_power = 0.0;
	while (lights_cpy)
	{
		p = ft_sub_vec3(lights_cpy->pos, finter.pos);
		if (is_in_shade(data, p, finter))
			light_power = 0.0;
		else
		{
			light_power = lights_cpy->lum * ft_max(EPSILON, ft_dot_product3(ft_get_normalized(p), finter.normal)) / ft_norm_vec3_2(&p);
			light_power = normalize_and_markout(light_power, 255);
			// light_power = pow(light_power, 1/2.2);
		}
		col_tmp = mult_col_double(lights_cpy->color, light_power);
		col = add_colors(mult_col(finter.col, col_tmp), col);
		lights_cpy = lights_cpy->next;
	}
	col = add_colors(mult_col(finter.col, data->al.color), col);
	return (color_encode(col));
}

int		modulate_color(t_data *data, t_inter finter, double back_color)
{
	int	color;
	(void)back_color;

	if (finter.set)
		color = calc_pixel_color(data, finter);
	else
		color = rgb_to_int(0, 0, 0);
	return (color);
}

void	ft_raytracing(t_data *data)
{
	t_inter	finter;
	t_win	win;
	t_vec3	ray;
	double	fov;
	int		color;

	win = data->win;
	fov = select_cam(*data).fov;
	win.y = 0;
	while (win.y < win.h)
	{
		win.x = 0;
		while (win.x < win.w)
		{
			finter.min_t = INFINITY;
			finter.set = false;
			ray = trace_ray_normalized(win, win.x, win.y, fov);
			find_closest_inter(data, &finter, &ray);
			color = modulate_color(data, finter, (win.y/win.h));
			ft_pixel_put(&data->mlx, win.x, win.y, color);
			win.x++;
		}
		win.y++;
	}
}
