/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:27:00 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 11:50:41 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		multiply_by_matrix(t_vec3 u, t_matrix m)
{
	t_vec3 v;

	v.x = u.x * m.d[0][0] + u.y * m.d[1][0] + u.z * m.d[2][0] + m.d[3][0];
	v.y = u.x * m.d[0][1] + u.y * m.d[1][1] + u.z * m.d[2][1] + m.d[3][1];
	v.z = u.x * m.d[0][2] + u.y * m.d[1][2] + u.z * m.d[2][2] + m.d[3][2];
	return (v);
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
