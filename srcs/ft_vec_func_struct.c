/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_func_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:57:34 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/21 10:16:15 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ft_norm_vec3(t_vec3 *vec)
{
	float	norm;

	norm = 0.0;
	norm += vec->x * vec->x;
	norm += vec->y * vec->y;
	norm += vec->z * vec->z;
	return (sqrt(norm));
}

float	ft_norm_vec3_2(t_vec3 *vec)
{
	float	norm;

	norm = 0.0;
	norm += vec->x * vec->x;
	norm += vec->y * vec->y;
	norm += vec->z * vec->z;
	return (norm);
}

float 	ft_dot_product3(t_vec3 *u, t_vec3 *v)
{
	float	result;

	result = 0.0;
	result += u->x * v->x;
	result += u->y * v->y;
	result += u->z * v->z;
	return (result);
}

void	ft_cross_product3(t_vec3 *u, t_vec3 *v, t_vec3 *p)
{
	p->x = v->z * u->y - v->y * u->z;
	p->y = v->x * u->z - v->z * u->x;
	p->z = v->y * u->x - v->x * u->y;
}

void	ft_add_vec3(t_vec3 *u, t_vec3 *v, t_vec3 *p)
{
	p->x = u->x + v->x;
	p->y = u->y + v->y;
	p->z = u->z + v->z;
}

void	ft_sub_vec3(t_vec3 *u, t_vec3 *v, t_vec3 *p)
{
	p->x = u->x - v->x;
	p->y = u->y - v->y;
	p->z = u->z - v->z;
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
