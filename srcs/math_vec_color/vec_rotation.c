/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:27:00 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/16 16:27:09 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		get_rot_angle(t_vec3 dir, char c)
{
	double	teta;
	t_vec3	n;

	n = new_vec(0.0, 0.0, 0.0);
	if (c == 'x')
		n = new_vec(1.0, 0.0, 0.0);
	else if (c == 'y')
		n = new_vec(0.0, 1.0, 0.0);
	else if (c == 'z')
		n = new_vec(0.0, 0.0, 1.0);
	teta = acos(ft_dot_product3(dir, n) / (ft_norm_vec3(&dir) * ft_norm_vec3(&n)));
	teta = rad_to_deg(teta);
	printf("%c: %f\n", c, teta);
	return (teta);
}


static void	rot_x(t_vec3 *v, t_vec3 dir)
{
	double rot;

	rot = get_rot_angle(dir, 'x');
	v->y = v->y * cos(rot) - v->z * sin(rot);
	v->z = v->y * sin(rot) + v->z * cos(rot);
}

static void	rot_y(t_vec3 *v, t_vec3 dir)
{
	double rot;

	rot = get_rot_angle(dir, 'y');
	v->x = v->x * cos(rot) - v->z * sin(rot);
	v->z = v->x * sin(rot) + v->z * cos(rot);
}

static void	rot_z(t_vec3 *v, t_vec3 dir)
{
	double rot;

	rot = get_rot_angle(dir, 'z');
	v->x = v->x * cos(rot) - v->y * sin(rot);
	v->y = v->x * sin(rot) + v->y * cos(rot);
}

void		rot_3d(t_vec3 *v, t_vec3 dir)
{
	rot_x(v, dir);
	rot_y(v, dir);
	rot_z(v, dir);
}

/*void   rot_3d(t_vec3 *v, double rot)
{
	double c;
	double s;
	double x2;
	double y2;
	double z2;

	c = cos(rot);
	s = sin(rot);
	x2 = v->x * v->x;
	y2 = v->y * v->y;
	z2 = v->z * v->z;

	v->x = (x2 + (1 - x2) * c) + (((v->x * v->y) * (1 - c)) - (v->z * s)) + (((v->x * v->z) * (1 - c)) + (v->y * s));
	v->y = (((v->x * v->y) * (1 - c)) + (v->z * s)) + (y2 + (1 - y2) * c) + (((v->y * v->z) * (1 - c)) - (v->x * s));
	v->z = (((v->x * v->z) * (1 - c)) - (v->y * s)) + (((v->y * v->z) * (1 - c)) - (v->x * s)) + (z2 + (1 - z2) * c);
}*/
