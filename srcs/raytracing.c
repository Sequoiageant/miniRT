/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:18:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/02 19:34:23 by julnolle         ###   ########.fr       */
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

int		rt_sp(t_vec3 *dir, t_data *data, t_obj *objlst, t_inter *inter)
{
	t_vec3		origin;
	t_vec3		oc;
	t_quadra	q;
	float		r;

	r = objlst->u_obj.sp.dia;
	origin = select_cam(*data).pos;
	oc = ft_sub_vec3(&origin, &objlst->u_obj.sp.pos);
	q.a = 1;
	q.b = 2.0 * ft_dot_product3(*dir, oc);
	q.c = ft_norm_vec3_2(&oc) - ((r/2) * (r/2));
	q.delta = q.b * q.b - 4 * q.a * q.c;
	if (q.delta < 0)
		return (0);
	q.t1 = (-q.b - sqrt(q.delta)) / (2 * q.a);
	q.t2 = (-q.b + sqrt(q.delta)) / (2 * q.a);
	if (q.t2 < 0)
		return (0);
	if(q.t1 > 0)
		inter->t = q.t1;
	else
		inter->t =q.t2;
	ft_multby_vec3(dir, inter->t);
	inter->pos = ft_add_vec3(&origin, dir);
	inter->norm = ft_sub_vec3(&inter->pos, &objlst->u_obj.sp.pos);
	ft_normalize(&inter->norm);
	return (1);
}

int		rt_tr(t_vec3 *dir, t_data *data, t_obj *objlst, t_inter *inter)
{
	(void)data;
	(void)objlst;
	(void)dir;
	(void)inter;
	// printf("%s\n", "raytracing of triangle");
	return (0);
}
int		rt_cy(t_vec3 *dir, t_data *data, t_obj *objlst, t_inter *inter)
{
	(void)data;
	(void)objlst;
	(void)dir;
	(void)inter;
	// printf("%s\n", "raytracing of cylinder");
	return (0);
}
int		rt_sq(t_vec3 *dir, t_data *data, t_obj *objlst, t_inter *inter)
{
	(void)data;
	(void)objlst;
	(void)dir;
	(void)inter;
	// printf("%s\n", "raytracing of square");
	return (0);
}
int		rt_pl(t_vec3 *dir, t_data *data, t_obj *objlst, t_inter *inter)
{
	(void)data;
	(void)objlst;
	(void)dir;
	(void)inter;
	// printf("%s\n", "raytracing of plane");
	return (0);
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
			ft_pixel_put(&data->mlx, x, y, create_trgb((y/win.h)*255, 255, 255, 0));
			x++;
		}
		y++;
	}
}

void reset_inter(t_inter *inter)
{
	inter->t = 0;
	inter->pos.x = 0.0;
	inter->pos.y = 0.0;
	inter->pos.z = 0.0;
	inter->norm.x = 0.0;
	inter->norm.y = 0.0;
	inter->norm.z = 0.0;
}

void	ft_raytracing(t_data *data)
{
	t_inter	inter;
	t_inter	finter;
	float x;
	float y;
	float fov;
	t_obj *objlst;
	double min_t;
	static t_ray	intersec[NB_OBJ] = {rt_sp, rt_pl, rt_sq, rt_cy, rt_tr};
	t_vec3 p;
	t_win win;
	t_vec3 dir;
	double  int_pix = 0;
	double int_lum = 1500000;
	int color;

	// reset_image(data);
	win = data->win;
	fov = rad(select_cam(*data).fov);
	y = 0;
	while (y < win.h - 1)
	{
		x = 0;
		while (x < win.w - 1)
		{
			dir.x = x - win.w / 2;
			dir.y = y - win.h / 2;
			dir.z = -win.w / (2.0 * tan(fov / 2.0));
			ft_normalize(&dir);
			
			objlst = data->objlst;
			min_t = LARGE_NUMB;
			inter.set = false;
			while (objlst)
			{
				reset_inter(&inter);
				if (intersec[objlst->type](&dir, data, objlst, &inter))
				{
					inter.set = true;
					if (inter.t < min_t)
					{
						min_t = inter.t;
						finter.pos = inter.pos;
						finter.norm = inter.norm;
					}
				}
				objlst = objlst->next;
			}
			if (inter.set)
			{
				int_pix = 0;
				p = ft_sub_vec3(&data->lights->pos, &finter.pos);
				int_pix = int_lum * ft_max(0.0, ft_dot_product3(ft_get_normalized(p), finter.norm));
				int_pix /=  ft_norm_vec3_2(&p);
				if (int_pix < 0.0)
					int_pix = 0;
				if (int_pix > 255)
					int_pix = 255;
				color = create_trgb(int_pix,int_pix,int_pix,0);
				ft_pixel_put(&data->mlx, x, y, color);
				reset_inter(&finter);
			}
			else
				ft_pixel_put(&data->mlx, x, y, create_trgb((y/win.h)*255, 255, 69, 0));

			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_win, data->mlx.img, 0, 0);
}
