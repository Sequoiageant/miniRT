/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_func_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:57:34 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/12 16:02:44 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	new_vec(double a, double b, double c)
{
	t_vec3 vec;

	vec.x = a;
	vec.y = b;
	vec.z = c;
	return (vec);
}

void	reset_vec(t_vec3 *vec)
{
	vec->x = 0.0;
	vec->y = 0.0;
	vec->z = 0.0;
}

t_vec3	new_vec_from_char(char *a, char *b, char *c)
{
	t_vec3 vec;

	vec.x = ft_atof(a);
	vec.y = ft_atof(b);
	vec.z = ft_atof(c);
	return (vec);
}

double	ft_norm_vec3_2(t_vec3 *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

double	ft_norm_vec3(t_vec3 *vec)
{
	return (sqrt(ft_norm_vec3_2(vec)));
}

double 	ft_dot_product3(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	ft_cross_product3(t_vec3 *u, t_vec3 *v)
{
	t_vec3 p;

	p.x = v->z * u->y - v->y * u->z;
	p.y = v->x * u->z - v->z * u->x;
	p.z = v->y * u->x - v->x * u->y;
	return (p);
}

t_vec3	ft_add_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3 p;

	p.x = u.x + v.x;
	p.y = u.y + v.y;
	p.z = u.z + v.z;
	return (p);
}

t_vec3	ft_sub_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3 p;

	p.x = u.x - v.x;
	p.y = u.y - v.y;
	p.z = u.z - v.z;
	return (p);
}

void	ft_rot_vec3(t_vec3 *u, t_vec3 *dir)
{
	u->x *= dir->x;
	u->y *= dir->y;
	u->z *= dir->z;
}

t_vec3	ft_multby_vec3(t_vec3 *u, double mult)
{
	t_vec3 p;

	p.x = u->x * mult;
	p.y = u->y * mult;
	p.z = u->z * mult;
	return (p);
}
t_vec3	ft_divby_vec3(t_vec3 *u, double div)
{
	t_vec3 p;

	p.x = u->x / div;
	p.y = u->y / div;
	p.z = u->z / div;
	return (p);
}

t_vec3	ft_decal_vec3(t_vec3 *u, double sub)
{
	t_vec3 p;

	p.x = u->x + sub;
	p.y = u->y + sub;
	p.z = u->z + sub;
	return (p);
}

void	ft_normalize(t_vec3 *vec)
{
	double norm;

	norm = ft_norm_vec3(vec);
	if (norm != 1 && norm != 0)
	{
		vec->x /= norm;
		vec->y /= norm;
		vec->z /= norm;
	}
}

t_vec3	ft_get_normalized(t_vec3 vec)
{
	ft_normalize(&vec);
	return (vec);
}

double	ft_get_dist(t_vec3 u, t_vec3 v)
{
	return (sqrt(pow(v.x - u.x, 2) + pow(v.y - u.y, 2) + pow(v.z - u.z, 2)));
}

static void	rot_x(t_vec3 *v, double rot)
{
	v->y = v->y * cos(rot) - v->z * sin(rot);
	v->z = v->y * sin(rot) + v->z * cos(rot);
}

static void	rot_y(t_vec3 *v, double rot)
{
	v->x = v->x * cos(rot) - v->z * sin(rot);
	v->z = v->x * sin(rot) + v->z * cos(rot);
}

static void	rot_z(t_vec3 *v, double rot)
{
	v->x = v->x * cos(rot) - v->y * sin(rot);
	v->y = v->x * sin(rot) + v->y * cos(rot);
}

void		rot_3d(t_vec3 *v, double rot)
{
	rot_x(v, rot);
	rot_y(v, rot);
	rot_z(v, rot);
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
