/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:06:06 by julnolle          #+#    #+#             */
/*   Updated: 2020/02/19 14:23:33 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_vec3 u;
	t_vec3 v;

	u.x = -1;
	u.y = 1;
	u.z = 1;
	v = ft_get_normalized(u);
	ft_normalize(&u);
	printf("%f  %f  %f\n", u.x, u.y, u.z);
	printf("%f  %f  %f\n", v.x, v.y, v.z);
	return (0);
}
