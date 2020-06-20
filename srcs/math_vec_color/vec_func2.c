/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_func2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 11:54:36 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 11:59:59 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot_product3(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	cross_product3(t_vec3 *u, t_vec3 *v)
{
	t_vec3 p;

	p.x = v->z * u->y - v->y * u->z;
	p.y = v->x * u->z - v->z * u->x;
	p.z = v->y * u->x - v->x * u->y;
	return (p);
}

t_vec3	add_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3 p;

	p.x = u.x + v.x;
	p.y = u.y + v.y;
	p.z = u.z + v.z;
	return (p);
}

t_vec3	sub_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3 p;

	p.x = u.x - v.x;
	p.y = u.y - v.y;
	p.z = u.z - v.z;
	return (p);
}

t_vec3	multby_vec3(t_vec3 *u, double mult)
{
	t_vec3 p;

	p.x = u->x * mult;
	p.y = u->y * mult;
	p.z = u->z * mult;
	return (p);
}
