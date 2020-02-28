/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:18:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/28 18:23:12 by julnolle         ###   ########.fr       */
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

int		ft_intersec_sp(t_vec3 *dir, t_data *data, t_obj *objlst, t_vec3 *n, t_vec3 *p, double *t)
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
		return (FALSE);
	q.t1 = (-q.b - sqrt(q.delta)) / (2 * q.a);
	q.t2 = (-q.b + sqrt(q.delta)) / (2 * q.a);
	if (q.t2 < 0)
		return (FALSE);
	*t = ((q.t1 > 0) ? q.t1 : q.t2);
	ft_multby_vec3(dir, *t);
	*p = ft_add_vec3(&origin, dir);
	*n = ft_sub_vec3(p, &objlst->u_obj.sp.pos);
	ft_normalize(n);
		return (TRUE);
}

int		rt_tr(t_data *data, t_obj *objlst)
{
	(void)data;
	(void)objlst;
	printf("%s\n", "raytracing of triangle");
	return (0);
}
int		rt_cy(t_data *data, t_obj *objlst)
{
	(void)data;
	(void)objlst;
	printf("%s\n", "raytracing of cylinder");
	return (0);
}
int		rt_sq(t_data *data, t_obj *objlst)
{
	(void)data;
	(void)objlst;
	printf("%s\n", "raytracing of square");
	return (0);
}
int		rt_pl(t_data *data, t_obj *objlst)
{
	(void)data;
	(void)objlst;
	printf("%s\n", "raytracing of plane");
	return (0);
}

int	rt_sp(t_data *data, t_obj *objlst)
{
	t_win	win;
	t_vec3	dir;
	float	fov;
	float	y;
	float	x;
	t_vec3	n;
	t_vec3	p;
	double  int_pix = 0;
	double int_lum = 1500000;
	t_vec3 p2;
	int color;
	static double t = INFINITY;

	win = data->win;
	fov = select_cam(*data).fov * M_PI / 180;
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
			if (ft_intersec_sp(&dir, data, objlst, &n, &p, &t))
			{
				p2 = ft_sub_vec3(&data->lights->pos, &p);
				int_pix = int_lum * ft_max(0.0, ft_dot_product3(ft_get_normalized(p2), n));
				int_pix /=  ft_norm_vec3_2(&p2);
				if (int_pix < 0.0)
					int_pix = 0;
				if (int_pix > 255)
					int_pix = 255;
				color = create_trgb(int_pix,int_pix,int_pix,0);
				ft_pixel_put(&data->mlx, x, y, color);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	reset_image(t_data *data)
{
	float	i;
	float	j;
	t_win	win;
	win = data->win;

	i = 0;
	while (i < win.w - 1)
	{
		j = 0;
		while (j < win.h - 1)
		{
			ft_pixel_put(&data->mlx, i, j, create_trgb((j/win.h)*255, 255, 255, 0));
			j++;
		}
		i++;
	}
}

void	ft_raytracing(t_data *data)
{
	t_obj *objlst;
	static t_ray	raytrace[NB_OBJ] = {rt_sp, rt_pl, rt_sq, rt_cy, rt_tr};

	objlst = data->objlst;
	reset_image(data);
	while (objlst)
	{
		raytrace[objlst->type](data, objlst);
		objlst = objlst->next;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_win, data->mlx.img, 0, 0);
}
