/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 11:43:05 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/22 13:07:24 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

void		reset_inter(t_inter *inter)
{
	inter->t = INFINITY;
	inter->pos.x = 0.0;
	inter->pos.y = 0.0;
	inter->pos.z = 0.0;
	inter->normal.x = 0.0;
	inter->normal.y = 0.0;
	inter->normal.z = 0.0;
}

t_vec3		trace_ray_normalized(t_win win, t_cam camera)
{
	t_vec3		ray;
	t_matrix	c2w;

	c2w = look_at(camera.pos, camera.dir);
	ray.x = win.x - win.w / 2;
	ray.y = win.y - win.h / 2;
	ray.z = -win.w / (2.0 * tan(camera.fov / 2.0));
	ray = multiply_by_matrix(ray, c2w);
	ray = sub_vec3(ray, camera.pos);
	ft_normalize(&ray);
	return (ray);
}

static void	swap_doubles(double *a, double *b)
{
	double buffer;

	buffer = *a;
	*a = *b;
	*b = buffer;
}

int			solve_quadratic(t_quadra *q)
{
	double nom;

	q->delta = q->b * q->b - 4.0 * q->a * q->c;
	if (q->delta < 0)
		return (FALSE);
	else if (q->delta == 0)
	{
		q->t1 = -0.5 * q->b / q->a;
		q->t2 = -0.5 * q->b / q->a;
	}
	else
	{
		if (q->b > 0)
			nom = -1 * (q->b + sqrt(q->delta)) / 2;
		else
			nom = -1 * (q->b - sqrt(q->delta)) / 2;
		q->t1 = nom / q->a;
		q->t2 = q->c / nom;
	}
	if (q->t1 > q->t2)
		swap_doubles(&q->t1, &q->t2);
	return (TRUE);
}
