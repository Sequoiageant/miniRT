/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:18:43 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/25 11:24:07 by julnolle         ###   ########.fr       */
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

int		ft_intersec_sp(t_vec3 *dir, t_data *data, t_obj *objlst)
{
	t_vec3 origin;
	t_vec3 oc;
	t_quadra q;
	float r;

	r = objlst->u_obj.sp.dia;
	origin = select_cam(*data).pos;
	oc = ft_sub_vec3(&origin, &objlst->u_obj.sp.pos);
	q.a = 1;
	q.b = 2.0 * ft_dot_product3(dir, &oc);
	q.c = ft_norm_vec3_2(&oc) - ((r/2) * (r/2));
	q.delta = q.b * q.b - 4 * q.a * q.c;
	if (q.delta < 0)
		return (0);
	// q.t1 = (-q.b - sqrt(q.delta)) / (2 * q.a);
	q.t2 = (-q.b + sqrt(q.delta)) / (2 * q.a);
	if (q.t2 > 0 || q.delta == 0)
		return (1);
	return (0);
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
int		rt_sp(t_data *data, t_obj *objlst)
{
	t_win	win;
	t_vec3	dir;
	float	fov;
	float	i;
	float	j;

	win = data->win;
	fov = select_cam(*data).fov * M_PI / 180;
	// printf("%d\n", select_cam(*data).fov);
	i = 0;
	while (i < win.w - 1)
	{
		j = 0;
		while (j < win.h - 1)
		{
			dir.x = i - win.w / 2;
			dir.y = j - win.h / 2;
			dir.z = -win.w / (2.0 * tan(fov / 2.0));
			ft_normalize(&dir);
			if (ft_intersec_sp(&dir, data, objlst) == 1)
			{
				ft_pixel_put(&data->mlx, i, j, create_trgb((j/win.h)*objlst->u_obj.sp.color.r, objlst->u_obj.sp.color.g, objlst->u_obj.sp.color.b, 0));
			}
			j++;
		}
		i++;
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
