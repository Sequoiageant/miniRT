/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 12:00:31 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/16 12:18:36 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


double		get_rot_angle(t_vec3 ray, t_vec3 dir)
{
	double	teta;

	teta = acos(ft_dot_product3(ray, dir) / (ft_norm_vec3(&ray) * ft_norm_vec3(&dir)));
	teta = rad_to_deg(teta);
	return (teta);
}


int main(void)
{
	t_vec3	ray;
	t_vec3	dir;

	ray.x = 0.5; ray.y = -0.20; ray.z = 0;
	dir.x = -0.3; dir.y = 0.2; dir.z = 0.5;
	printf("%f\n", get_rot_angle(ray, dir));
	return (0);
}