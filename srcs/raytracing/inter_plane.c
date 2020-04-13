/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:11:12 by julien            #+#    #+#             */
/*   Updated: 2020/03/24 21:11:57 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rt_pl(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3		origin;
	t_vec3		p0;
	double		denom;

	p0 = objlst->u_obj.pl.pos;
	origin = inter->origin;
	inter->normal = objlst->u_obj.pl.normal;
	denom = ft_dot_product3(*ray, inter->normal);
	if (fabs(denom) > EPSILON)
	{	
		inter->t = ft_dot_product3(ft_sub_vec3(p0, origin), inter->normal) / denom; 
		inter->pos = ft_add_vec3(origin, ft_multby_vec3(ray, inter->t));
		if (inter->t >= 0.0 && inter->t < INFINITY)
			return (TRUE);
	} 
	return (FALSE);
}
