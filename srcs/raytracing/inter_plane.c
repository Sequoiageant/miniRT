/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:11:12 by julien            #+#    #+#             */
/*   Updated: 2020/05/02 18:52:14 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 sign_normal(t_vec3 normal, t_vec3 ori, t_vec3 pos)
{
	if ((pos.x > ori.x && normal.x > 0) || (pos.x < ori.x && normal.x < 0))
		normal.x = -normal.x;
	if ((pos.y > ori.y && normal.y > 0) || (pos.y < ori.y && normal.y < 0))
		normal.y = -normal.y;
	if ((pos.z > ori.z && normal.z > 0) || (pos.z < ori.z && normal.z < 0))
		normal.z = -normal.z;
	return (normal);
}

int		rt_pl(t_vec3 *ray, t_obj *objlst, t_inter *inter)
{
	t_vec3		origin;
	t_vec3		p0;
	double		denom;

	p0 = objlst->u_obj.pl.pos;
	origin = inter->origin;
	inter->normal = sign_normal(objlst->u_obj.pl.normal, origin, p0);
	denom = dot_product3(*ray, inter->normal);
	if (fabs(denom) > EPSILON)
	{	
		inter->t = dot_product3(sub_vec3(p0, origin), inter->normal) / denom;
		inter->pos = add_vec3(origin, multby_vec3(ray, inter->t));
		if (inter->t >= 0.0 && inter->t < INFINITY)
			return (TRUE);
	} 
	return (FALSE);
}
