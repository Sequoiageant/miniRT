/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 11:43:05 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 16:28:44 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

void	reset_inter(t_inter *inter)
{
	inter->t = INFINITY;
	inter->pos.x = 0.0;
	inter->pos.y = 0.0;
	inter->pos.z = 0.0;
	inter->normal.x = 0.0;
	inter->normal.y = 0.0;
	inter->normal.z = 0.0;
}

t_vec3	trace_ray_normalized(t_win win, t_cam camera)
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
