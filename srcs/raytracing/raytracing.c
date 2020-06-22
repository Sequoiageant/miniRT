/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 11:46:44 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/22 13:08:22 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	find_closest_inter(t_data *data, t_inter *finter, t_vec3 *ray)
{
	t_inter			inter;
	t_obj			*objlst;
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

int		is_in_shade(t_data *data, t_vec3 ray, t_inter finter)
{
	t_obj			*objlst;
	t_inter			inter;
	static t_ray	intersec[NB_OBJ] = {rt_sp, rt_pl, rt_sq, rt_cy, rt_tr};
	t_vec3			normalized_ray;

	normalized_ray = get_normalized(ray);
	finter.normal = multby_vec3(&finter.normal, BIAS);
	inter.origin = add_vec3(finter.pos, finter.normal);
	objlst = data->objlst;
	while (objlst)
	{
		if (intersec[objlst->type](&normalized_ray, objlst, &inter))
		{
			if ((inter.t * inter.t) < norm_vec3_2(&ray))
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
	lights_cpy = data->lights;
	while (lights_cpy)
	{
		p = sub_vec3(lights_cpy->pos, finter.pos);
		if (is_in_shade(data, p, finter))
			light_power = 0.0;
		else
		{
			light_power = lights_cpy->lum * ft_max(EPSILON, dot_product3(
				get_normalized(p), finter.normal)) / norm_vec3_2(&p);
			light_power = normalize_and_markout(light_power, 255);
		}
		col_tmp = mult_col_double(lights_cpy->color, light_power);
		col = add_colors(mult_col(finter.col, col_tmp), col);
		lights_cpy = lights_cpy->next;
	}
	col = add_colors(mult_col(finter.col, data->al.color), col);
	return (color_encode(col));
}

int		modulate_color(t_data *data, t_inter finter)
{
	int	color;

	if (finter.set)
		color = calc_pixel_color(data, finter);
	else
		color = rgb_to_int(0, 0, 0);
	return (color);
}

void	raytracing(t_data *data)
{
	t_inter	finter;
	t_win	win;
	t_vec3	ray;
	int		color;
	t_cam	camera;

	camera = select_cam(*data);
	win = data->win;
	win.y = 0;
	while (win.y < win.h)
	{
		win.x = 0;
		while (win.x < win.w)
		{
			finter.min_t = INFINITY;
			finter.set = false;
			ray = trace_ray_normalized(win, camera);
			find_closest_inter(data, &finter, &ray);
			color = modulate_color(data, finter);
			ft_pixel_put(&data->mlx, win.x, win.y, color);
			win.x++;
		}
		win.y++;
	}
}
