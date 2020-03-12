/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:18:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/12 20:21:31 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"


/*	ALGO :
** Place the eye and the frame as desired (1)
** For each pixel on the screen
**     Determine the square on the grid corresponding to this pixel (2)
**     Determine the color seen through that square (3)
**     Paint the pixel with that color (4)
*/

t_obj *copy_list(t_obj *head)
{
	t_obj *current = head;	// used to iterate over original list
	t_obj *newList = NULL; // head of the new list
	t_obj *tail = NULL;	// point to last node in new list

	while (current != NULL)
	{
		// special case for the first new Node
		if (newList == NULL)
		{
			newList = (t_obj *)malloc(sizeof(t_obj));
			newList->type = current->type;
			newList->next = NULL;
			tail = newList;
		}
		else
		{
			tail->next = (t_obj *)malloc(sizeof(t_obj));
			tail = tail->next;
			tail->type = current->type;
			tail->next = NULL;
		}
		current = current->next;
	}

	return (newList);
}

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


int		rt_tr(t_vec3 *dir, t_obj *objlst, t_inter *inter)
{
	(void)objlst;
	(void)dir;
	(void)inter;
	// printf("%s\n", "raytracing of triangle");
	return (FALSE);
}
int		rt_cy(t_vec3 *dir, t_obj *objlst, t_inter *inter)
{
	(void)objlst;
	(void)dir;
	(void)inter;
	// printf("%s\n", "raytracing of cylinder");
	return (FALSE);
}

void	reset_image(t_data *data)
{
	float	x;
	float	y;
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

int		rt_pl(t_vec3 *dir, t_obj *objlst, t_inter *inter)
{
	t_vec3		origin;
	t_vec3		p;
	float		denom;

	p = objlst->u_obj.pl.pos;
	origin = inter->origin;
	inter->normal = objlst->u_obj.pl.dir;
	denom = ft_dot_product3(*dir, inter->normal);
	if (fabs(denom) > EPSILON)
	{	
		inter->t = ft_dot_product3(ft_sub_vec3(p, origin), inter->normal) / denom; 
		inter->pos = ft_add_vec3(origin, ft_multby_vec3(dir, inter->t));
		if (inter->t >= 0.0 && inter->t < INFINITY)
			return (TRUE);
	} 
	return (FALSE);
}

int		rt_sq(t_vec3 *dir, t_obj *objlst, t_inter *inter)
{
	float t_min;
	float t_max;

	if (rt_pl(dir, objlst, inter))
	{
		t_min = 0.0; // calcul trigo pour tmin et tmax ?
		t_max = 0.0;

		if (inter->t > t_min && inter->t < t_max)
			return (TRUE);
	}

	return (FALSE);
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

int		rt_sp(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3		origin;
	t_vec3		oc;
	t_quadra	q;
	float		r;

	r = objlst->u_obj.sp.dia;
	origin = inter->origin;
	oc = ft_sub_vec3(origin, objlst->u_obj.sp.pos);
	q.a = ft_norm_vec3_2(ray);
	q.b = 2.0 * ft_dot_product3(*ray, oc);
	q.c = ft_norm_vec3_2(&oc) - (r * r);
	q.delta = q.b * q.b - 4.0 * q.a * q.c;
	if (q.delta < 0.)
		return (FALSE);
	q.t1 = (-q.b - sqrt(q.delta)) / (2 * q.a);
	q.t2 = (-q.b + sqrt(q.delta)) / (2 * q.a);
	if (q.t2 < 0.)
		return (FALSE);
	inter->t = ft_min(q.t1, q.t2);
	inter->pos = ft_add_vec3(origin, ft_multby_vec3(ray, inter->t));
	inter->normal = ft_sub_vec3(inter->pos, objlst->u_obj.sp.pos);
	ft_normalize(&inter->normal);
	return (TRUE);
}

t_vec3	trace_ray_normalized(t_win win, float x, float y, float fov)
{
	t_vec3 ray;

	ray.x = x - win.w / 2;
	ray.y = y - win.h / 2;
	ray.z = -win.w / (2.0 * tan(fov / 2.0));
	ft_normalize(&ray);
	return (ray);
}

int		set_color(t_col color, double intensity, t_col lum_col)
{
	t_col	tmp_col;

	tmp_col = color;
	tmp_col = add_colors(tmp_col, lum_col);
	// printf("%d %d %d \n", tmp_col.r, tmp_col.g, tmp_col.b);
	tmp_col = mult_col_float(tmp_col, intensity);
	return (color_encode(tmp_col));
}

void	find_closest_inter(t_data *data, t_inter *finter, t_vec3 *dir)
{
	t_inter inter;
	t_obj *objlst;
	static t_ray	intersec[NB_OBJ] = {rt_sp, rt_pl, rt_sq, rt_cy, rt_tr};
	
	inter.origin = select_cam(*data).pos;
	objlst = data->objlst;
	while (objlst)
	{
		reset_inter(&inter);
		if (intersec[objlst->type](dir, objlst, &inter))
		{
			finter->set = true;
			if (inter.t <= finter->min_t)
			{
				finter->min_t = inter.t;
				finter->pos = inter.pos;
				finter->normal = inter.normal;
				finter->obj_num = objlst->num;
				finter->col = objlst->col;
			}
		}
		objlst = objlst->next;
	}
}

float	is_in_shade(t_data *data, t_vec3 ray, t_inter finter)
{
	t_obj			*objlst;
	t_inter			inter;
	static t_ray	intersec[NB_OBJ] = {rt_sp, rt_pl, rt_sq, rt_cy, rt_tr};
	t_vec3			normalized_ray;
	
	finter.set = FALSE;
	normalized_ray = ft_get_normalized(ray);
	finter.normal = ft_multby_vec3(&finter.normal, BIAS);
	inter.origin = ft_add_vec3(finter.pos, finter.normal);
	objlst = data->objlst;
	while (objlst)
	{
		if (intersec[objlst->type](&normalized_ray, objlst, &inter))
		{
			if ((inter.t * inter.t) < ft_norm_vec3_2(&ray))
			{
				finter.set = TRUE;
				break ;
			}
		}
		objlst = objlst->next;
	}
	return (finter.set);
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
		col_tmp = mult_col_float(lights_cpy->color, light_power);
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
	t_vec3	dir;
	float	fov;
	int		color;

	win = data->win;
	fov = rad(select_cam(*data).fov);
	win.y = 0;
	while (win.y < win.h - 1)
	{
		win.x = 0;
		while (win.x < win.w - 1)
		{
			finter.min_t = INFINITY;
			finter.set = false;
			dir = trace_ray_normalized(win, win.x, win.y, fov);
			find_closest_inter(data, &finter, &dir);
			color = modulate_color(data, finter, (win.y/win.h));
			ft_pixel_put(&data->mlx, win.x, win.y, color);

			win.x++;
		}
		win.y++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_win, data->mlx.img, 0, 0);
}
