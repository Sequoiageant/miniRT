/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:27:00 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/17 18:06:42 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		get_rot_angle(t_vec3 dir, char c)
{
	double	teta;
	t_vec3	n;

	n = new_vec(0.0, 0.0, 0.0);
	if (c == 'x')
		n = new_vec(0.0, 0.0, 1.0);
	else if (c == 'y')
		n = new_vec(0.0, 0.0, 1.0);
	else if (c == 'z')
		n = new_vec(0.0, 0.0, 1.0);
	teta = acos(dot_product3(dir, n) / (norm_vec3(&dir) * norm_vec3(&n)));
	// teta = rad_to_deg(teta);
	// printf("%c: %f\n", c, teta);
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

t_vec3		multiply_by_matrix(t_vec3 p, t_matrix m)
{
	t_vec3 res;

	res.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
	res.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
	res.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
	return (res);
}
t_matrix	look_at(t_vec3 origin, t_vec3 dir)
{
	t_matrix	m;
	t_vec3		random;
	t_vec3		right;
	t_vec3		up;

	random = new_vec(0.0, 1.0, 0.0);
	ft_normalize(&random);
	right = cross_product3(&random, &dir);
	ft_normalize(&right);
	up = cross_product3(&dir, &right);
	ft_normalize(&up);
	m.d[0][0] = right.x;
	m.d[0][1] = right.y;
	m.d[0][2] = right.z;
	m.d[1][0] = up.x;
	m.d[1][1] = up.y;
	m.d[1][2] = up.z;
	m.d[2][0] = dir.x;
	m.d[2][1] = dir.y;
	m.d[2][2] = dir.z;
	m.d[3][0] = origin.x;
	m.d[3][1] = origin.y;
	m.d[3][2] = origin.z;
	return (m);
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
