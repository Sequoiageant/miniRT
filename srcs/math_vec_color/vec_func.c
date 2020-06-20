/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:57:34 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 12:00:07 by julnolle         ###   ########.fr       */
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
