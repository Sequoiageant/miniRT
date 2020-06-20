/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_func3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 11:56:19 by julnolle          #+#    #+#             */
/*   Updated: 2020/06/20 11:56:26 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	norm_vec3_2(t_vec3 *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

double	norm_vec3(t_vec3 *vec)
{
	return (sqrt(norm_vec3_2(vec)));
}

void	ft_normalize(t_vec3 *vec)
{
	double norm;

	norm = norm_vec3(vec);
	if (norm != 1 && norm != 0)
	{
		vec->x /= norm;
		vec->y /= norm;
		vec->z /= norm;
	}
}

t_vec3	get_normalized(t_vec3 vec)
{
	ft_normalize(&vec);
	return (vec);
}
