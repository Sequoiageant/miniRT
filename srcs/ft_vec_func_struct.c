/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_func_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:57:34 by julnolle          #+#    #+#             */
/*   Updated: 2020/03/02 16:16:59 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	new_vec(float a, float b, float c)
{
	t_vec3 vec;

	vec.x = a;
	vec.y = b;
	vec.z = c;
	return (vec);
}

float	ft_norm_vec3_2(t_vec3 *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

float	ft_norm_vec3(t_vec3 *vec)
{
	return (sqrt(ft_norm_vec3_2(vec)));
}

float 	ft_dot_product3(t_vec3 u, t_vec3 v)
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

t_vec3	ft_add_vec3(t_vec3 *u, t_vec3 *v)
{
	t_vec3 p;

	p.x = u->x + v->x;
	p.y = u->y + v->y;
	p.z = u->z + v->z;
	return (p);
}

t_vec3	ft_sub_vec3(t_vec3 *u, t_vec3 *v)
{
	t_vec3 p;

	p.x = u->x - v->x;
	p.y = u->y - v->y;
	p.z = u->z - v->z;
	return (p);
}

void	ft_rot_vec3(t_vec3 *u, t_vec3 *dir)
{
	u->x *= dir->x;
	u->y *= dir->y;
	u->z *= dir->z;
}

void	ft_multby_vec3(t_vec3 *u, float mult)
{
	u->x *= mult;
	u->y *= mult;
	u->z *= mult;
}

void	ft_normalize(t_vec3 *vec)
{
	float norm;

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
	t_vec3	p;

	p = vec;
	ft_normalize(&p);
	return (p);
}

double	ft_get_dist(t_vec3 u, t_vec3 v)
{
	return (sqrt(pow(v.x - u.x, 2) +
		pow(v.y - u.y, 2) + pow(v.z - u.z, 2)));
}
